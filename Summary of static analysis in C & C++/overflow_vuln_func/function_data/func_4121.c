static void vmd_decode(VmdVideoContext *s)
{
    int i;
    unsigned int *palette32;
    unsigned char r, g, b;

    /
    const unsigned char *p = s->buf + 16;
    const unsigned char *p_end = s->buf + s->size;

    const unsigned char *pb;
    const unsigned char *pb_end;
    unsigned char meth;
    unsigned char *dp;   /
    unsigned char *pp;   /
    unsigned char len;
    int ofs;

    int frame_x, frame_y;
    int frame_width, frame_height;

    frame_x = AV_RL16(&s->buf[6]);
    frame_y = AV_RL16(&s->buf[8]);
    frame_width = AV_RL16(&s->buf[10]) - frame_x + 1;
    frame_height = AV_RL16(&s->buf[12]) - frame_y + 1;
    if (frame_x < 0 || frame_width < 0 ||
        frame_x >= s->avctx->width ||
        frame_width > s->avctx->width ||
        frame_x + frame_width > s->avctx->width)
        return;
    if (frame_y < 0 || frame_height < 0 ||
        frame_y >= s->avctx->height ||
        frame_height > s->avctx->height ||
        frame_y + frame_height > s->avctx->height)
        return;

    if ((frame_width == s->avctx->width && frame_height == s->avctx->height) &&
        (frame_x || frame_y)) {

        s->x_off = frame_x;
        s->y_off = frame_y;
    }
    frame_x -= s->x_off;
    frame_y -= s->y_off;

    /
    if (s->prev_frame.data[0] &&
        (frame_x || frame_y || (frame_width != s->avctx->width) ||
        (frame_height != s->avctx->height))) {

        memcpy(s->frame.data[0], s->prev_frame.data[0],
            s->avctx->height * s->frame.linesize[0]);
    }

    /
    if (s->buf[15] & 0x02) {
        if (p_end - p < 2 + 3 * PALETTE_COUNT)
            return;
        p += 2;
        palette32 = (unsigned int *)s->palette;
        for (i = 0; i < PALETTE_COUNT; i++) {
            r = *p++ * 4;
            g = *p++ * 4;
            b = *p++ * 4;
            palette32[i] = (r << 16) | (g << 8) | (b);
        }
    }
    if (p < p_end) {
        /
        pb = p;
        pb_end = p_end;
        meth = *pb++;
        if (meth & 0x80) {
            lz_unpack(pb, p_end - pb, s->unpack_buffer, s->unpack_buffer_size);
            meth &= 0x7F;
            pb = s->unpack_buffer;
            pb_end = s->unpack_buffer + s->unpack_buffer_size;
        }

        dp = &s->frame.data[0][frame_y * s->frame.linesize[0] + frame_x];
        pp = &s->prev_frame.data[0][frame_y * s->prev_frame.linesize[0] + frame_x];
        switch (meth) {
        case 1:
            for (i = 0; i < frame_height; i++) {
                ofs = 0;
                do {
                    if (pb_end - pb < 1)
                        return;
                    len = *pb++;
                    if (len & 0x80) {
                        len = (len & 0x7F) + 1;
                        if (ofs + len > frame_width || pb_end - pb < len)
                            return;
                        memcpy(&dp[ofs], pb, len);
                        pb += len;
                        ofs += len;
                    } else {
                        /
                        if (ofs + len + 1 > frame_width || !s->prev_frame.data[0])
                            return;
                        memcpy(&dp[ofs], &pp[ofs], len + 1);
                        ofs += len + 1;
                    }
                } while (ofs < frame_width);
                if (ofs > frame_width) {
                    av_log(s->avctx, AV_LOG_ERROR, "VMD video: offset > width (%d > %d)\n",
                        ofs, frame_width);
                    break;
                }
                dp += s->frame.linesize[0];
                pp += s->prev_frame.linesize[0];
            }
            break;

        case 2:
            for (i = 0; i < frame_height; i++) {
                if (pb_end -pb < frame_width)
                    return;
                memcpy(dp, pb, frame_width);
                pb += frame_width;
                dp += s->frame.linesize[0];
                pp += s->prev_frame.linesize[0];
            }
            break;

        case 3:
            for (i = 0; i < frame_height; i++) {
                ofs = 0;
                do {
                    if (pb_end - pb < 1)
                        return;
                    len = *pb++;
                    if (len & 0x80) {
                        len = (len & 0x7F) + 1;
                        if (pb_end - pb < 1)
                            return;
                        if (*pb++ == 0xFF)
                            len = rle_unpack(pb, &dp[ofs], len, frame_width - ofs);
                        else {
                        if (pb_end - pb < len)
                            return;
                            memcpy(&dp[ofs], pb, len);
                        }
                        pb += len;
                        ofs += len;
                    } else {
                        /
                        if (ofs + len + 1 > frame_width || !s->prev_frame.data[0])
                            return;
                        memcpy(&dp[ofs], &pp[ofs], len + 1);
                        ofs += len + 1;
                    }
                } while (ofs < frame_width);
                if (ofs > frame_width) {
                    av_log(s->avctx, AV_LOG_ERROR, "VMD video: offset > width (%d > %d)\n",
                        ofs, frame_width);
                }
                dp += s->frame.linesize[0];
                pp += s->prev_frame.linesize[0];
            }
            break;
        }
    }
}
