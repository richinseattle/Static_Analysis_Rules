static void
dissect_amqp_0_10_session(tvbuff_t *tvb,
                          packet_info *pinfo,
                          proto_tree *tree,
                          int offset, guint16 length)
{
    proto_item  *args_tree;
    proto_item  *ti;
    proto_item  *flags_item;
    guint8       method;
    guint8       flag1, flag2;
    guint16      size;
    guint32      array_size;
    int          flags_offset;
    const gchar *method_name;

    method = tvb_get_guint8(tvb, offset+1);
    method_name = val_to_str_const(method, amqp_0_10_session_methods,
                                   "<invalid session method>");
    col_append_str(pinfo->cinfo, COL_INFO, method_name);
    col_append_str(pinfo->cinfo, COL_INFO, " ");
    col_set_fence(pinfo->cinfo, COL_INFO);

    proto_tree_add_item(tree, hf_amqp_0_10_session_method,
                        tvb, offset+1, 1, ENC_BIG_ENDIAN);
    AMQP_INCREMENT(offset, 2, length);

    ti = proto_tree_add_item(tree, hf_amqp_method_arguments,
                             tvb, offset, length - 2, ENC_NA);
    args_tree = proto_item_add_subtree(ti, ett_args);
    /
    flags_offset = offset;
    flag1 = tvb_get_guint8(tvb, offset);
    flag2 = tvb_get_guint8(tvb, offset+1);
    flags_item = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_argument_packing_flags,
                                     tvb, offset, 2, ENC_BIG_ENDIAN);
    AMQP_INCREMENT(offset, 2, length);
    switch (method) {
    case AMQP_0_10_METHOD_SESSION_ATTACH:
        if ((flag1 & ~0x03) || ((flag2 != 0)))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            AMQP_INCREMENT(offset, 2, length);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_session_attach_name,
                                tvb, offset, size, ENC_NA);
            AMQP_INCREMENT(offset, size, length);
        }
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_session_attach_force,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        break;

    case AMQP_0_10_METHOD_SESSION_ATTACHED:
    case AMQP_0_10_METHOD_SESSION_DETACH:
        if ((flag1 != 0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            AMQP_INCREMENT(offset, 2, length);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_session_attach_name,
                                tvb, offset, size, ENC_NA);
            AMQP_INCREMENT(offset, size, length);
        }
        break;

    case AMQP_0_10_METHOD_SESSION_DETACHED:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            AMQP_INCREMENT(offset, 2, length);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_session_attach_name,
                                tvb, offset, size, ENC_NA);
            AMQP_INCREMENT(offset, size, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_session_detached_code,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        break;

    case AMQP_0_10_METHOD_SESSION_REQUEST_TIMEOUT:
    case AMQP_0_10_METHOD_SESSION_TIMEOUT:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_session_timeout,
                                tvb, offset, 4, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 4, length);
        }
        break;

    case AMQP_0_10_METHOD_SESSION_COMMAND_POINT:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_session_command_point_id,
                                tvb, offset, 4, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 4, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_session_command_point_offset,
                                tvb, offset, 8, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 8, length);
        }
        break;

    case AMQP_0_10_METHOD_SESSION_EXPECTED:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            if ((offset + 2 + size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_session_commands,
                                     tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size + 2, length);
        }
        if (flag1 & 0x02) {
            /
            array_size = tvb_get_ntohl(tvb, offset);
            if ((offset + 4 + array_size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_session_fragments,
                                     tvb, offset, array_size + 4, ENC_NA);
            AMQP_INCREMENT(offset, 4, length);
            dissect_amqp_0_10_array(tvb,
                                    pinfo,
                                    offset,
                                    offset + array_size,
                                    length,
                                    ti);
            AMQP_INCREMENT(offset, array_size, length);
        }
        break;

    case AMQP_0_10_METHOD_SESSION_CONFIRMED:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            if ((offset + 2 + size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_session_commands,
                                     tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size + 2, length);
        }
        if (flag1 & 0x02) {
            /
            array_size = tvb_get_ntohl(tvb, offset);
            if ((offset + 4 + array_size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_session_fragments,
                                     tvb, offset, array_size + 4, ENC_NA);
            AMQP_INCREMENT(offset, 4, length);
            dissect_amqp_0_10_array(tvb,
                                    pinfo,
                                    offset,
                                    offset + array_size,
                                    length,
                                    ti);
            AMQP_INCREMENT(offset, array_size, length);
        }
        break;

    case AMQP_0_10_METHOD_SESSION_COMPLETED:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            if ((offset + 2 + size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_session_commands,
                                     tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size, length);
        }
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_session_completed_timely,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        break;

    case AMQP_0_10_METHOD_SESSION_KNOWN_COMPLETED:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            if ((offset + 2 + size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_session_commands,
                                     tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size, length);
        }
        break;

    case AMQP_0_10_METHOD_SESSION_FLUSH:
        if ((flag1 & ~0x07) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_session_flush_expected,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_session_flush_confirmed,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_session_flush_completed,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        break;

    case AMQP_0_10_METHOD_SESSION_GAP:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            if ((offset + 2 + size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_session_commands,
                                     tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size + 2, length);
        }
        break;

    }
}
