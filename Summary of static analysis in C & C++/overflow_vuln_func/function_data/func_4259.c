int ff_hevc_parse_sps(HEVCSPS *sps, GetBitContext *gb, unsigned int *sps_id,
                      int apply_defdispwin, AVBufferRef **vps_list, AVCodecContext *avctx)
{
    HEVCWindow *ow;
    int ret = 0;
    int log2_diff_max_min_transform_block_size;
    int bit_depth_chroma, start, vui_present, sublayer_ordering_info;
    int i;

    // Coded parameters

    sps->vps_id = get_bits(gb, 4);
    if (sps->vps_id >= HEVC_MAX_VPS_COUNT) {
        av_log(avctx, AV_LOG_ERROR, "VPS id out of range: %d\n", sps->vps_id);
        return AVERROR_INVALIDDATA;
    }

    if (vps_list && !vps_list[sps->vps_id]) {
        av_log(avctx, AV_LOG_ERROR, "VPS %d does not exist\n",
               sps->vps_id);
        return AVERROR_INVALIDDATA;
    }

    sps->max_sub_layers = get_bits(gb, 3) + 1;
    if (sps->max_sub_layers > HEVC_MAX_SUB_LAYERS) {
        av_log(avctx, AV_LOG_ERROR, "sps_max_sub_layers out of range: %d\n",
               sps->max_sub_layers);
        return AVERROR_INVALIDDATA;
    }

    skip_bits1(gb); // temporal_id_nesting_flag

    if ((ret = parse_ptl(gb, avctx, &sps->ptl, sps->max_sub_layers)) < 0)
        return ret;

    *sps_id = get_ue_golomb_long(gb);
    if (*sps_id >= HEVC_MAX_SPS_COUNT) {
        av_log(avctx, AV_LOG_ERROR, "SPS id out of range: %d\n", *sps_id);
        return AVERROR_INVALIDDATA;
    }

    sps->chroma_format_idc = get_ue_golomb_long(gb);
    if (sps->chroma_format_idc > 3U) {
        av_log(avctx, AV_LOG_ERROR, "chroma_format_idc %d is invalid\n", sps->chroma_format_idc);
        return AVERROR_INVALIDDATA;
    }

    if (sps->chroma_format_idc == 3)
        sps->separate_colour_plane_flag = get_bits1(gb);

    if (sps->separate_colour_plane_flag)
        sps->chroma_format_idc = 0;

    sps->width  = get_ue_golomb_long(gb);
    sps->height = get_ue_golomb_long(gb);
    if ((ret = av_image_check_size(sps->width,
                                   sps->height, 0, avctx)) < 0)
        return ret;

    if (get_bits1(gb)) { // pic_conformance_flag
        int vert_mult  = 1 + (sps->chroma_format_idc < 2);
        int horiz_mult = 1 + (sps->chroma_format_idc < 3);
        sps->pic_conf_win.left_offset   = get_ue_golomb_long(gb) * horiz_mult;
        sps->pic_conf_win.right_offset  = get_ue_golomb_long(gb) * horiz_mult;
        sps->pic_conf_win.top_offset    = get_ue_golomb_long(gb) *  vert_mult;
        sps->pic_conf_win.bottom_offset = get_ue_golomb_long(gb) *  vert_mult;

        if (avctx->flags2 & AV_CODEC_FLAG2_IGNORE_CROP) {
            av_log(avctx, AV_LOG_DEBUG,
                   "discarding sps conformance window, "
                   "original values are l:%u r:%u t:%u b:%u\n",
                   sps->pic_conf_win.left_offset,
                   sps->pic_conf_win.right_offset,
                   sps->pic_conf_win.top_offset,
                   sps->pic_conf_win.bottom_offset);

            sps->pic_conf_win.left_offset   =
            sps->pic_conf_win.right_offset  =
            sps->pic_conf_win.top_offset    =
            sps->pic_conf_win.bottom_offset = 0;
        }
        sps->output_window = sps->pic_conf_win;
    }

    sps->bit_depth   = get_ue_golomb_long(gb) + 8;
    bit_depth_chroma = get_ue_golomb_long(gb) + 8;
    if (sps->chroma_format_idc && bit_depth_chroma != sps->bit_depth) {
        av_log(avctx, AV_LOG_ERROR,
               "Luma bit depth (%d) is different from chroma bit depth (%d), "
               "this is unsupported.\n",
               sps->bit_depth, bit_depth_chroma);
        return AVERROR_INVALIDDATA;
    }

    ret = map_pixel_format(avctx, sps);
    if (ret < 0)
        return ret;

    sps->log2_max_poc_lsb = get_ue_golomb_long(gb) + 4;
    if (sps->log2_max_poc_lsb > 16) {
        av_log(avctx, AV_LOG_ERROR, "log2_max_pic_order_cnt_lsb_minus4 out range: %d\n",
               sps->log2_max_poc_lsb - 4);
        return AVERROR_INVALIDDATA;
    }

    sublayer_ordering_info = get_bits1(gb);
    start = sublayer_ordering_info ? 0 : sps->max_sub_layers - 1;
    for (i = start; i < sps->max_sub_layers; i++) {
        sps->temporal_layer[i].max_dec_pic_buffering = get_ue_golomb_long(gb) + 1;
        sps->temporal_layer[i].num_reorder_pics      = get_ue_golomb_long(gb);
        sps->temporal_layer[i].max_latency_increase  = get_ue_golomb_long(gb) - 1;
        if (sps->temporal_layer[i].max_dec_pic_buffering > HEVC_MAX_DPB_SIZE) {
            av_log(avctx, AV_LOG_ERROR, "sps_max_dec_pic_buffering_minus1 out of range: %d\n",
                   sps->temporal_layer[i].max_dec_pic_buffering - 1);
            return AVERROR_INVALIDDATA;
        }
        if (sps->temporal_layer[i].num_reorder_pics > sps->temporal_layer[i].max_dec_pic_buffering - 1) {
            av_log(avctx, AV_LOG_WARNING, "sps_max_num_reorder_pics out of range: %d\n",
                   sps->temporal_layer[i].num_reorder_pics);
            if (avctx->err_recognition & AV_EF_EXPLODE ||
                sps->temporal_layer[i].num_reorder_pics > HEVC_MAX_DPB_SIZE - 1) {
                return AVERROR_INVALIDDATA;
            }
            sps->temporal_layer[i].max_dec_pic_buffering = sps->temporal_layer[i].num_reorder_pics + 1;
        }
    }

    if (!sublayer_ordering_info) {
        for (i = 0; i < start; i++) {
            sps->temporal_layer[i].max_dec_pic_buffering = sps->temporal_layer[start].max_dec_pic_buffering;
            sps->temporal_layer[i].num_reorder_pics      = sps->temporal_layer[start].num_reorder_pics;
            sps->temporal_layer[i].max_latency_increase  = sps->temporal_layer[start].max_latency_increase;
        }
    }

    sps->log2_min_cb_size                    = get_ue_golomb_long(gb) + 3;
    sps->log2_diff_max_min_coding_block_size = get_ue_golomb_long(gb);
    sps->log2_min_tb_size                    = get_ue_golomb_long(gb) + 2;
    log2_diff_max_min_transform_block_size   = get_ue_golomb_long(gb);
    sps->log2_max_trafo_size                 = log2_diff_max_min_transform_block_size +
                                               sps->log2_min_tb_size;

    if (sps->log2_min_cb_size < 3 || sps->log2_min_cb_size > 30) {
        av_log(avctx, AV_LOG_ERROR, "Invalid value %d for log2_min_cb_size", sps->log2_min_cb_size);
        return AVERROR_INVALIDDATA;
    }

    if (sps->log2_diff_max_min_coding_block_size > 30) {
        av_log(avctx, AV_LOG_ERROR, "Invalid value %d for log2_diff_max_min_coding_block_size", sps->log2_diff_max_min_coding_block_size);
        return AVERROR_INVALIDDATA;
    }

    if (sps->log2_min_tb_size >= sps->log2_min_cb_size || sps->log2_min_tb_size < 2) {
        av_log(avctx, AV_LOG_ERROR, "Invalid value for log2_min_tb_size");
        return AVERROR_INVALIDDATA;
    }

    if (log2_diff_max_min_transform_block_size < 0 || log2_diff_max_min_transform_block_size > 30) {
        av_log(avctx, AV_LOG_ERROR, "Invalid value %d for log2_diff_max_min_transform_block_size", log2_diff_max_min_transform_block_size);
        return AVERROR_INVALIDDATA;
    }

    sps->max_transform_hierarchy_depth_inter = get_ue_golomb_long(gb);
    sps->max_transform_hierarchy_depth_intra = get_ue_golomb_long(gb);

    sps->scaling_list_enable_flag = get_bits1(gb);
    if (sps->scaling_list_enable_flag) {
        set_default_scaling_list_data(&sps->scaling_list);

        if (get_bits1(gb)) {
            ret = scaling_list_data(gb, avctx, &sps->scaling_list, sps);
            if (ret < 0)
                return ret;
        }
    }

    sps->amp_enabled_flag = get_bits1(gb);
    sps->sao_enabled      = get_bits1(gb);

    sps->pcm_enabled_flag = get_bits1(gb);
    if (sps->pcm_enabled_flag) {
        sps->pcm.bit_depth   = get_bits(gb, 4) + 1;
        sps->pcm.bit_depth_chroma = get_bits(gb, 4) + 1;
        sps->pcm.log2_min_pcm_cb_size = get_ue_golomb_long(gb) + 3;
        sps->pcm.log2_max_pcm_cb_size = sps->pcm.log2_min_pcm_cb_size +
                                        get_ue_golomb_long(gb);
        if (sps->pcm.bit_depth > sps->bit_depth) {
            av_log(avctx, AV_LOG_ERROR,
                   "PCM bit depth (%d) is greater than normal bit depth (%d)\n",
                   sps->pcm.bit_depth, sps->bit_depth);
            return AVERROR_INVALIDDATA;
        }

        sps->pcm.loop_filter_disable_flag = get_bits1(gb);
    }

    sps->nb_st_rps = get_ue_golomb_long(gb);
    if (sps->nb_st_rps > HEVC_MAX_SHORT_TERM_RPS_COUNT) {
        av_log(avctx, AV_LOG_ERROR, "Too many short term RPS: %d.\n",
               sps->nb_st_rps);
        return AVERROR_INVALIDDATA;
    }
    for (i = 0; i < sps->nb_st_rps; i++) {
        if ((ret = ff_hevc_decode_short_term_rps(gb, avctx, &sps->st_rps[i],
                                                 sps, 0)) < 0)
            return ret;
    }

    sps->long_term_ref_pics_present_flag = get_bits1(gb);
    if (sps->long_term_ref_pics_present_flag) {
        sps->num_long_term_ref_pics_sps = get_ue_golomb_long(gb);
        if (sps->num_long_term_ref_pics_sps > 31U) {
            av_log(avctx, AV_LOG_ERROR, "num_long_term_ref_pics_sps %d is out of range.\n",
                   sps->num_long_term_ref_pics_sps);
            return AVERROR_INVALIDDATA;
        }
        for (i = 0; i < sps->num_long_term_ref_pics_sps; i++) {
            sps->lt_ref_pic_poc_lsb_sps[i]       = get_bits(gb, sps->log2_max_poc_lsb);
            sps->used_by_curr_pic_lt_sps_flag[i] = get_bits1(gb);
        }
    }

    sps->sps_temporal_mvp_enabled_flag          = get_bits1(gb);
    sps->sps_strong_intra_smoothing_enable_flag = get_bits1(gb);
    sps->vui.sar = (AVRational){0, 1};
    vui_present = get_bits1(gb);
    if (vui_present)
        decode_vui(gb, avctx, apply_defdispwin, sps);

    if (get_bits1(gb)) { // sps_extension_flag
        int sps_extension_flag[1];
        for (i = 0; i < 1; i++)
            sps_extension_flag[i] = get_bits1(gb);
        skip_bits(gb, 7); //sps_extension_7bits = get_bits(gb, 7);
        if (sps_extension_flag[0]) {
            int extended_precision_processing_flag;
            int high_precision_offsets_enabled_flag;
            int cabac_bypass_alignment_enabled_flag;

            sps->transform_skip_rotation_enabled_flag = get_bits1(gb);
            sps->transform_skip_context_enabled_flag  = get_bits1(gb);
            sps->implicit_rdpcm_enabled_flag = get_bits1(gb);

            sps->explicit_rdpcm_enabled_flag = get_bits1(gb);

            extended_precision_processing_flag = get_bits1(gb);
            if (extended_precision_processing_flag)
                av_log(avctx, AV_LOG_WARNING,
                   "extended_precision_processing_flag not yet implemented\n");

            sps->intra_smoothing_disabled_flag       = get_bits1(gb);
            high_precision_offsets_enabled_flag  = get_bits1(gb);
            if (high_precision_offsets_enabled_flag)
                av_log(avctx, AV_LOG_WARNING,
                   "high_precision_offsets_enabled_flag not yet implemented\n");

            sps->persistent_rice_adaptation_enabled_flag = get_bits1(gb);

            cabac_bypass_alignment_enabled_flag  = get_bits1(gb);
            if (cabac_bypass_alignment_enabled_flag)
                av_log(avctx, AV_LOG_WARNING,
                   "cabac_bypass_alignment_enabled_flag not yet implemented\n");
        }
    }
    if (apply_defdispwin) {
        sps->output_window.left_offset   += sps->vui.def_disp_win.left_offset;
        sps->output_window.right_offset  += sps->vui.def_disp_win.right_offset;
        sps->output_window.top_offset    += sps->vui.def_disp_win.top_offset;
        sps->output_window.bottom_offset += sps->vui.def_disp_win.bottom_offset;
    }

    ow = &sps->output_window;
    if (ow->left_offset >= INT_MAX - ow->right_offset     ||
        ow->top_offset  >= INT_MAX - ow->bottom_offset    ||
        ow->left_offset + ow->right_offset  >= sps->width ||
        ow->top_offset  + ow->bottom_offset >= sps->height) {
        av_log(avctx, AV_LOG_WARNING, "Invalid cropping offsets: %u/%u/%u/%u\n",
               ow->left_offset, ow->right_offset, ow->top_offset, ow->bottom_offset);
        if (avctx->err_recognition & AV_EF_EXPLODE) {
            return AVERROR_INVALIDDATA;
        }
        av_log(avctx, AV_LOG_WARNING,
               "Displaying the whole video surface.\n");
        memset(ow, 0, sizeof(*ow));
        memset(&sps->pic_conf_win, 0, sizeof(sps->pic_conf_win));
    }

    // Inferred parameters
    sps->log2_ctb_size = sps->log2_min_cb_size +
                         sps->log2_diff_max_min_coding_block_size;
    sps->log2_min_pu_size = sps->log2_min_cb_size - 1;

    if (sps->log2_ctb_size > HEVC_MAX_LOG2_CTB_SIZE) {
        av_log(avctx, AV_LOG_ERROR, "CTB size out of range: 2^%d\n", sps->log2_ctb_size);
        return AVERROR_INVALIDDATA;
    }
    if (sps->log2_ctb_size < 4) {
        av_log(avctx,
               AV_LOG_ERROR,
               "log2_ctb_size %d differs from the bounds of any known profile\n",
               sps->log2_ctb_size);
        avpriv_request_sample(avctx, "log2_ctb_size %d", sps->log2_ctb_size);
        return AVERROR_INVALIDDATA;
    }

    sps->ctb_width  = (sps->width  + (1 << sps->log2_ctb_size) - 1) >> sps->log2_ctb_size;
    sps->ctb_height = (sps->height + (1 << sps->log2_ctb_size) - 1) >> sps->log2_ctb_size;
    sps->ctb_size   = sps->ctb_width * sps->ctb_height;

    sps->min_cb_width  = sps->width  >> sps->log2_min_cb_size;
    sps->min_cb_height = sps->height >> sps->log2_min_cb_size;
    sps->min_tb_width  = sps->width  >> sps->log2_min_tb_size;
    sps->min_tb_height = sps->height >> sps->log2_min_tb_size;
    sps->min_pu_width  = sps->width  >> sps->log2_min_pu_size;
    sps->min_pu_height = sps->height >> sps->log2_min_pu_size;
    sps->tb_mask       = (1 << (sps->log2_ctb_size - sps->log2_min_tb_size)) - 1;

    sps->qp_bd_offset = 6 * (sps->bit_depth - 8);

    if (av_mod_uintp2(sps->width, sps->log2_min_cb_size) ||
        av_mod_uintp2(sps->height, sps->log2_min_cb_size)) {
        av_log(avctx, AV_LOG_ERROR, "Invalid coded frame dimensions.\n");
        return AVERROR_INVALIDDATA;
    }

    if (sps->max_transform_hierarchy_depth_inter > sps->log2_ctb_size - sps->log2_min_tb_size) {
        av_log(avctx, AV_LOG_ERROR, "max_transform_hierarchy_depth_inter out of range: %d\n",
               sps->max_transform_hierarchy_depth_inter);
        return AVERROR_INVALIDDATA;
    }
    if (sps->max_transform_hierarchy_depth_intra > sps->log2_ctb_size - sps->log2_min_tb_size) {
        av_log(avctx, AV_LOG_ERROR, "max_transform_hierarchy_depth_intra out of range: %d\n",
               sps->max_transform_hierarchy_depth_intra);
        return AVERROR_INVALIDDATA;
    }
    if (sps->log2_max_trafo_size > FFMIN(sps->log2_ctb_size, 5)) {
        av_log(avctx, AV_LOG_ERROR,
               "max transform block size out of range: %d\n",
               sps->log2_max_trafo_size);
        return AVERROR_INVALIDDATA;
    }

    if (get_bits_left(gb) < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "Overread SPS by %d bits\n", -get_bits_left(gb));
        return AVERROR_INVALIDDATA;
    }

    return 0;
}
