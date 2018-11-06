av_cold int ff_ivi_init_planes(IVIPlaneDesc *planes, const IVIPicConfig *cfg,
                               int is_indeo4)
{
    int p, b;
    uint32_t b_width, b_height, align_fac, width_aligned,
             height_aligned, buf_size;
    IVIBandDesc *band;

    ivi_free_buffers(planes);

    if (cfg->pic_width < 1 || cfg->pic_height < 1 ||
        cfg->luma_bands < 1 || cfg->chroma_bands < 1)
        return AVERROR_INVALIDDATA;

    /
    planes[0].width     = cfg->pic_width;
    planes[0].height    = cfg->pic_height;
    planes[0].num_bands = cfg->luma_bands;

    /
    planes[1].width     = planes[2].width     = (cfg->pic_width  + 3) >> 2;
    planes[1].height    = planes[2].height    = (cfg->pic_height + 3) >> 2;
    planes[1].num_bands = planes[2].num_bands = cfg->chroma_bands;

    for (p = 0; p < 3; p++) {
        planes[p].bands = av_mallocz_array(planes[p].num_bands, sizeof(IVIBandDesc));
        if (!planes[p].bands)
            return AVERROR(ENOMEM);

        /
        b_width  = planes[p].num_bands == 1 ? planes[p].width
                                            : (planes[p].width  + 1) >> 1;
        b_height = planes[p].num_bands == 1 ? planes[p].height
                                            : (planes[p].height + 1) >> 1;

        /
        /
        align_fac       = p ? 8 : 16;
        width_aligned   = FFALIGN(b_width , align_fac);
        height_aligned  = FFALIGN(b_height, align_fac);
        buf_size        = width_aligned * height_aligned * sizeof(int16_t);

        for (b = 0; b < planes[p].num_bands; b++) {
            band = &planes[p].bands[b]; /
            band->plane    = p;
            band->band_num = b;
            band->width    = b_width;
            band->height   = b_height;
            band->pitch    = width_aligned;
            band->aheight  = height_aligned;
            band->bufs[0]  = av_mallocz(buf_size);
            band->bufs[1]  = av_mallocz(buf_size);
            band->bufsize  = buf_size/2;
            if (!band->bufs[0] || !band->bufs[1])
                return AVERROR(ENOMEM);

            /
            if (cfg->luma_bands > 1) {
                band->bufs[2] = av_mallocz(buf_size);
                if (!band->bufs[2])
                    return AVERROR(ENOMEM);
            }
            if (is_indeo4) {
                band->bufs[3]  = av_mallocz(buf_size);
                if (!band->bufs[3])
                    return AVERROR(ENOMEM);
            }
            /
            planes[p].bands[0].blk_vlc.cust_desc.num_rows = 0;
        }
    }

    return 0;
}
