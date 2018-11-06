static int decode_block(AVCodecContext *avctx, void *tdata,
                        int jobnr, int threadnr)
{
    EXRContext *s = avctx->priv_data;
    AVFrame *const p = s->picture;
    EXRThreadData *td = &s->thread_data[threadnr];
    const uint8_t *channel_buffer[4] = { 0 };
    const uint8_t *buf = s->buf;
    uint64_t line_offset, uncompressed_size;
    uint32_t xdelta = s->xdelta;
    uint16_t *ptr_x;
    uint8_t *ptr;
    uint32_t data_size, line, col = 0;
    uint32_t tileX, tileY, tileLevelX, tileLevelY;
    int channelLineSize, indexSrc, tX, tY, tCh;
    const uint8_t *src;
    int axmax = (avctx->width - (s->xmax + 1)) * 2 * s->desc->nb_components; /
    int bxmin = s->xmin * 2 * s->desc->nb_components; /
    int i, x, buf_size = s->buf_size;
    float one_gamma = 1.0f / s->gamma;
    avpriv_trc_function trc_func = avpriv_get_trc_function_from_trc(s->apply_trc_type);
    int ret;

    line_offset = AV_RL64(s->gb.buffer + jobnr * 8);

    if (s->is_tile) {
        if (line_offset > buf_size - 20)
            return AVERROR_INVALIDDATA;

        src  = buf + line_offset + 20;

        tileX = AV_RL32(src - 20);
        tileY = AV_RL32(src - 16);
        tileLevelX = AV_RL32(src - 12);
        tileLevelY = AV_RL32(src - 8);

        data_size = AV_RL32(src - 4);
        if (data_size <= 0 || data_size > buf_size)
            return AVERROR_INVALIDDATA;

        if (tileLevelX || tileLevelY) { /
            avpriv_report_missing_feature(s->avctx, "Subres tile before full res tile");
            return AVERROR_PATCHWELCOME;
        }

        line = s->tile_attr.ySize * tileY;
        col = s->tile_attr.xSize * tileX;

        td->ysize = FFMIN(s->tile_attr.ySize, s->ydelta - tileY * s->tile_attr.ySize);
        td->xsize = FFMIN(s->tile_attr.xSize, s->xdelta - tileX * s->tile_attr.xSize);
        uncompressed_size = s->current_channel_offset * td->ysize * td->xsize;

        if (col) { /
            bxmin = 0; axmax = 0; /
        }

        if ((col + td->xsize) != s->xdelta)/
            axmax = 0; /
    } else {
        if (line_offset > buf_size - 8)
            return AVERROR_INVALIDDATA;

        src  = buf + line_offset + 8;
        line = AV_RL32(src - 8);

        if (line < s->ymin || line > s->ymax)
            return AVERROR_INVALIDDATA;

        data_size = AV_RL32(src - 4);
        if (data_size <= 0 || data_size > buf_size)
            return AVERROR_INVALIDDATA;

        td->ysize          = FFMIN(s->scan_lines_per_block, s->ymax - line + 1); /
        td->xsize          = s->xdelta;
        uncompressed_size = s->scan_line_size * td->ysize;
        if ((s->compression == EXR_RAW && (data_size != uncompressed_size ||
                                           line_offset > buf_size - uncompressed_size)) ||
            (s->compression != EXR_RAW && (data_size > uncompressed_size ||
                                           line_offset > buf_size - data_size))) {
            return AVERROR_INVALIDDATA;
        }
    }

    if (data_size < uncompressed_size || s->is_tile) { /
        av_fast_padded_malloc(&td->tmp, &td->tmp_size, uncompressed_size);
        if (!td->tmp)
            return AVERROR(ENOMEM);
    }

    if (data_size < uncompressed_size) {
        av_fast_padded_malloc(&td->uncompressed_data,
                              &td->uncompressed_size, uncompressed_size);

        if (!td->uncompressed_data)
            return AVERROR(ENOMEM);

        ret = AVERROR_INVALIDDATA;
        switch (s->compression) {
        case EXR_ZIP1:
        case EXR_ZIP16:
            ret = zip_uncompress(src, data_size, uncompressed_size, td);
            break;
        case EXR_PIZ:
            ret = piz_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        case EXR_PXR24:
            ret = pxr24_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        case EXR_RLE:
            ret = rle_uncompress(src, data_size, uncompressed_size, td);
            break;
        case EXR_B44:
        case EXR_B44A:
            ret = b44_uncompress(s, src, data_size, uncompressed_size, td);
            break;
        }
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "decode_block() failed.\n");
            return ret;
        }
        src = td->uncompressed_data;
    }

    if (s->is_tile) {
        indexSrc = 0;
        channelLineSize = td->xsize * 2;
        if (s->pixel_type == EXR_FLOAT)
            channelLineSize *= 2;

        /
        for (tY = 0; tY < td->ysize; tY ++) {
            for (tCh = 0; tCh < s->nb_channels; tCh++) {
                for (tX = 0; tX < channelLineSize; tX++) {
                    td->tmp[tCh * channelLineSize * td->ysize + tY * channelLineSize + tX] = src[indexSrc];
                    indexSrc++;
                }
            }
        }

        channel_buffer[0] = td->tmp + td->xsize * s->channel_offsets[0]  * td->ysize;
        channel_buffer[1] = td->tmp + td->xsize * s->channel_offsets[1]  * td->ysize;
        channel_buffer[2] = td->tmp + td->xsize * s->channel_offsets[2]  * td->ysize;
        if (s->channel_offsets[3] >= 0)
            channel_buffer[3] = td->tmp + td->xsize * s->channel_offsets[3];
    } else {
        channel_buffer[0] = src + xdelta * s->channel_offsets[0];
        channel_buffer[1] = src + xdelta * s->channel_offsets[1];
        channel_buffer[2] = src + xdelta * s->channel_offsets[2];
        if (s->channel_offsets[3] >= 0)
            channel_buffer[3] = src + xdelta * s->channel_offsets[3];
    }

    ptr = p->data[0] + line * p->linesize[0] + (col * s->desc->nb_components * 2);

    for (i = 0;
         i < td->ysize; i++, ptr += p->linesize[0]) {

        const uint8_t *r, *g, *b, *a;

        r = channel_buffer[0];
        g = channel_buffer[1];
        b = channel_buffer[2];
        if (channel_buffer[3])
            a = channel_buffer[3];

        ptr_x = (uint16_t *) ptr;

        // Zero out the start if xmin is not 0
        memset(ptr_x, 0, bxmin);
        ptr_x += s->xmin * s->desc->nb_components;

        if (s->pixel_type == EXR_FLOAT) {
            // 32-bit
            if (trc_func) {
                for (x = 0; x < td->xsize; x++) {
                    union av_intfloat32 t;
                    t.i = bytestream_get_le32(&r);
                    t.f = trc_func(t.f);
                    *ptr_x++ = exr_flt2uint(t.i);

                    t.i = bytestream_get_le32(&g);
                    t.f = trc_func(t.f);
                    *ptr_x++ = exr_flt2uint(t.i);

                    t.i = bytestream_get_le32(&b);
                    t.f = trc_func(t.f);
                    *ptr_x++ = exr_flt2uint(t.i);
                    if (channel_buffer[3])
                        *ptr_x++ = exr_flt2uint(bytestream_get_le32(&a));
                }
            } else {
                for (x = 0; x < td->xsize; x++) {
                    union av_intfloat32 t;
                    t.i = bytestream_get_le32(&r);
                    if (t.f > 0.0f)  /
                        t.f = powf(t.f, one_gamma);
                    *ptr_x++ = exr_flt2uint(t.i);

                    t.i = bytestream_get_le32(&g);
                    if (t.f > 0.0f)
                        t.f = powf(t.f, one_gamma);
                    *ptr_x++ = exr_flt2uint(t.i);

                    t.i = bytestream_get_le32(&b);
                    if (t.f > 0.0f)
                        t.f = powf(t.f, one_gamma);
                    *ptr_x++ = exr_flt2uint(t.i);
                    if (channel_buffer[3])
                        *ptr_x++ = exr_flt2uint(bytestream_get_le32(&a));
                }
            }
        } else {
            // 16-bit
            for (x = 0; x < td->xsize; x++) {
                *ptr_x++ = s->gamma_table[bytestream_get_le16(&r)];
                *ptr_x++ = s->gamma_table[bytestream_get_le16(&g)];
                *ptr_x++ = s->gamma_table[bytestream_get_le16(&b)];
                if (channel_buffer[3])
                    *ptr_x++ = exr_halflt2uint(bytestream_get_le16(&a));
            }
        }

        // Zero out the end if xmax+1 is not w
        memset(ptr_x, 0, axmax);

        if (s->is_tile) {
            channel_buffer[0] += channelLineSize;
            channel_buffer[1] += channelLineSize;
            channel_buffer[2] += channelLineSize;
            if (channel_buffer[3])
                channel_buffer[3] += channelLineSize;
        } else {
            channel_buffer[0] += s->scan_line_size;
            channel_buffer[1] += s->scan_line_size;
            channel_buffer[2] += s->scan_line_size;
            if (channel_buffer[3])
                channel_buffer[3] += s->scan_line_size;
        }
    }

    return 0;
}
