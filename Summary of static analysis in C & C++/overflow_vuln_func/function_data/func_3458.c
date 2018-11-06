static int wv_get_value(WavpackFrameContext *ctx, GetBitContext *gb,
                        int channel, int *last)
{
    int t, t2;
    int sign, base, add, ret;
    WvChannel *c = &ctx->ch[channel];

    *last = 0;

    if ((ctx->ch[0].median[0] < 2U) && (ctx->ch[1].median[0] < 2U) &&
        !ctx->zero && !ctx->one) {
        if (ctx->zeroes) {
            ctx->zeroes--;
            if (ctx->zeroes) {
                c->slow_level -= LEVEL_DECAY(c->slow_level);
                return 0;
            }
        } else {
            t = get_unary_0_33(gb);
            if (t >= 2) {
                if (t >= 32 || get_bits_left(gb) < t - 1)
                    goto error;
                t = get_bits_long(gb, t - 1) | (1 << (t - 1));
            } else {
                if (get_bits_left(gb) < 0)
                    goto error;
            }
            ctx->zeroes = t;
            if (ctx->zeroes) {
                memset(ctx->ch[0].median, 0, sizeof(ctx->ch[0].median));
                memset(ctx->ch[1].median, 0, sizeof(ctx->ch[1].median));
                c->slow_level -= LEVEL_DECAY(c->slow_level);
                return 0;
            }
        }
    }

    if (ctx->zero) {
        t         = 0;
        ctx->zero = 0;
    } else {
        t = get_unary_0_33(gb);
        if (get_bits_left(gb) < 0)
            goto error;
        if (t == 16) {
            t2 = get_unary_0_33(gb);
            if (t2 < 2) {
                if (get_bits_left(gb) < 0)
                    goto error;
                t += t2;
            } else {
                if (get_bits_left(gb) < t2 - 1)
                    goto error;
                t += get_bits_long(gb, t2 - 1) | (1 << (t2 - 1));
            }
        }

        if (ctx->one) {
            ctx->one = t & 1;
            t        = (t >> 1) + 1;
        } else {
            ctx->one = t & 1;
            t      >>= 1;
        }
        ctx->zero = !ctx->one;
    }

    if (ctx->hybrid && !channel) {
        if (update_error_limit(ctx) < 0)
            goto error;
    }

    if (!t) {
        base = 0;
        add  = GET_MED(0) - 1;
        DEC_MED(0);
    } else if (t == 1) {
        base = GET_MED(0);
        add  = GET_MED(1) - 1;
        INC_MED(0);
        DEC_MED(1);
    } else if (t == 2) {
        base = GET_MED(0) + GET_MED(1);
        add  = GET_MED(2) - 1;
        INC_MED(0);
        INC_MED(1);
        DEC_MED(2);
    } else {
        base = GET_MED(0) + GET_MED(1) + GET_MED(2) * (t - 2);
        add  = GET_MED(2) - 1;
        INC_MED(0);
        INC_MED(1);
        INC_MED(2);
    }
    if (!c->error_limit) {
        if (add >= 0x2000000U) {
            av_log(ctx->avctx, AV_LOG_ERROR, "k %d is too large\n", add);
            goto error;
        }
        ret = base + get_tail(gb, add);
        if (get_bits_left(gb) <= 0)
            goto error;
    } else {
        int mid = (base * 2 + add + 1) >> 1;
        while (add > c->error_limit) {
            if (get_bits_left(gb) <= 0)
                goto error;
            if (get_bits1(gb)) {
                add -= (mid - base);
                base = mid;
            } else
                add = mid - base - 1;
            mid = (base * 2 + add + 1) >> 1;
        }
        ret = mid;
    }
    sign = get_bits1(gb);
    if (ctx->hybrid_bitrate)
        c->slow_level += wp_log2(ret) - LEVEL_DECAY(c->slow_level);
    return sign ? ~ret : ret;

error:
    ret = get_bits_left(gb);
    if (ret <= 0) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Too few bits (%d) left\n", ret);
    }
    *last = 1;
    return 0;
}
