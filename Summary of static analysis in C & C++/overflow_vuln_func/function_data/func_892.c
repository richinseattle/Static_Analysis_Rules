static void
dissect_amqp_0_10_connection(tvbuff_t *tvb,
                             packet_info *pinfo,
                             proto_tree *tree,
                             int offset, guint16 length)
{
    proto_item  *args_tree;
    proto_item  *ti;
    proto_item  *flags_item;
    guint8       method;
    guint8       flag1, flag2;  /
    guint32      arg_length;
    int          flags_offset;
    const gchar *method_name;

    method = tvb_get_guint8(tvb, offset+1);
    method_name = val_to_str_const(method, amqp_0_10_connection_methods,
                                   "<invalid connection method>");
    col_append_str(pinfo->cinfo, COL_INFO, method_name);
    col_append_str(pinfo->cinfo, COL_INFO, " ");
    col_set_fence(pinfo->cinfo,  COL_INFO);

    proto_tree_add_item(tree, hf_amqp_0_10_connection_method,
                        tvb, offset+1, 1, ENC_BIG_ENDIAN);
    ti = proto_tree_add_item(tree, hf_amqp_method_arguments,
                             tvb, offset + 2, length - 2, ENC_NA);
    args_tree = proto_item_add_subtree(ti, ett_args);
    AMQP_INCREMENT(offset, 2, length);
    /
    flags_offset = offset;
    flag1 = tvb_get_guint8(tvb, offset);
    flag2 = tvb_get_guint8(tvb, offset+1);
    flags_item = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_argument_packing_flags,
                                     tvb, offset, 2, ENC_BIG_ENDIAN);
    AMQP_INCREMENT(offset, 2, length);
    switch (method) {
    case AMQP_0_10_METHOD_CONNECTION_START:
        if ((flag1 & ~0x07) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            arg_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_method_connection_start_server_properties,
                                     tvb,
                                     offset,
                                     arg_length, ENC_NA);
            dissect_amqp_0_10_map (tvb,
                                   offset,
                                   offset + arg_length,
                                   arg_length,
                                   ti);
            AMQP_INCREMENT(offset, arg_length, length);
        }
        if (flag1 & 0x02) {
            /
            arg_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_connection_start_mechanisms,
                                     tvb,
                                     offset,
                                     arg_length, ENC_NA);
            dissect_amqp_0_10_array (tvb,
                                     pinfo,
                                     offset,
                                     offset + arg_length,
                                     arg_length,
                                     ti);
            AMQP_INCREMENT(offset, arg_length, length);
        }
        if (flag1 & 0x04) {
            /
            arg_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_connection_start_locales,
                                     tvb,
                                     offset,
                                     arg_length, ENC_NA);
            dissect_amqp_0_10_array (tvb,
                                     pinfo,
                                     offset,
                                     offset + arg_length,
                                     arg_length,
                                     ti);
            AMQP_INCREMENT(offset, arg_length, length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_START_OK:
        if ((flag1 & ~0x0f) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            arg_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_method_connection_start_ok_client_properties,
                                     tvb,
                                     offset,
                                     arg_length, ENC_NA);
            dissect_amqp_0_10_map (tvb,
                                   offset,
                                   offset + arg_length,
                                   arg_length,
                                   ti);
            AMQP_INCREMENT(offset, arg_length, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_start_ok_mechanism,
                                tvb, offset + 1, tvb_get_guint8(tvb, offset),
                                ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + tvb_get_guint8(tvb, offset), length);
        }
        if (flag1 & 0x04) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_start_ok_response,
                                tvb, offset + 4, tvb_get_ntohl(tvb, offset),
                                ENC_NA);
            AMQP_INCREMENT(offset, 4 + tvb_get_ntohl(tvb, offset), length);
        }
        if (flag1 & 0x08) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_start_ok_locale,
                                tvb, offset + 1, tvb_get_guint8(tvb, offset),
                                ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + tvb_get_guint8(tvb, offset), length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_SECURE:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_secure_challenge,
                                tvb, offset + 4, tvb_get_ntohl(tvb, offset),
                                ENC_NA);
            AMQP_INCREMENT(offset, 4 + tvb_get_ntohl(tvb, offset), length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_SECURE_OK:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_secure_ok_response,
                                tvb, offset + 4, tvb_get_ntohl(tvb, offset),
                                ENC_NA);
            AMQP_INCREMENT(offset, 4 + tvb_get_ntohl(tvb, offset), length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_TUNE:
        if ((flag1 & ~0x0f) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_tune_channel_max,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_connection_tune_frame_max,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x04) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_connection_tune_heartbeat_min,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x08) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_connection_tune_heartbeat_max,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_TUNE_OK:
        if ((flag1 & ~0x07) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_tune_ok_channel_max,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_connection_tune_ok_frame_max,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x04) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_tune_ok_heartbeat,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_OPEN:
        if ((flag1 & ~0x07) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                     hf_amqp_method_connection_open_virtual_host,
                                     tvb,
                                     offset + 1,
                                     tvb_get_guint8(tvb, offset), ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, tvb_get_guint8(tvb, offset) + 1, length);
        }
        if (flag1 & 0x02) {
            /
            arg_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_connection_open_capabilities,
                                     tvb,
                                     offset,
                                     arg_length, ENC_NA);
            dissect_amqp_0_10_array (tvb,
                                     pinfo,
                                     offset,
                                     offset + arg_length,
                                     arg_length,
                                     ti);
            AMQP_INCREMENT(offset, arg_length, length);
        }
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_connection_open_insist,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        break;

    case AMQP_0_10_METHOD_CONNECTION_OPEN_OK:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            arg_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_connection_open_ok_known_hosts,
                                     tvb,
                                     offset,
                                     arg_length, ENC_NA);
            dissect_amqp_0_10_array (tvb,
                                     pinfo,
                                     offset,
                                     offset + arg_length,
                                     arg_length,
                                     ti);
            AMQP_INCREMENT(offset, arg_length, length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_REDIRECT:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_redirect_host,
                                tvb, offset + 2, tvb_get_ntohs(tvb, offset),
                                ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 2 + tvb_get_ntohs(tvb, offset), length);
        }
        if (flag1 & 0x02) {
            /
            arg_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_connection_redirect_known_hosts,
                                     tvb,
                                     offset,
                                     arg_length, ENC_NA);
            dissect_amqp_0_10_array (tvb,
                                     pinfo,
                                     offset,
                                     offset + arg_length,
                                     arg_length,
                                     ti);
            AMQP_INCREMENT(offset, arg_length, length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_HEARTBEAT:
        break;

    case AMQP_0_10_METHOD_CONNECTION_CLOSE:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_connection_close_reply_code,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_method_connection_close_reply_text,
                                tvb, offset + 1, tvb_get_guint8(tvb, offset),
                                ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + tvb_get_guint8(tvb, offset), length);
        }
        break;

    case AMQP_0_10_METHOD_CONNECTION_CLOSE_OK:
        break;
    }
}
