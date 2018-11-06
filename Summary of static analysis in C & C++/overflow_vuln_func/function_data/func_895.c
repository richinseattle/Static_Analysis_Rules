static void
dissect_amqp_0_10_message(tvbuff_t *tvb,
                          packet_info *pinfo,
                          proto_tree *tree,
                          int offset, guint16 length)
{
    proto_item  *args_tree;
    proto_item  *ti;
    proto_item  *flags_item;
    guint8       method, str_size;
    guint8       flag1, flag2;
    guint16      size;
    guint32      map_size;
    int          flags_offset;
    const gchar *method_name;

    method = tvb_get_guint8(tvb, offset+1);
    method_name = val_to_str_const(method, amqp_0_10_message_methods,
                                   "<invalid message method>");
    col_append_str(pinfo->cinfo, COL_INFO, method_name);
    col_append_str(pinfo->cinfo, COL_INFO, " ");
    col_set_fence(pinfo->cinfo, COL_INFO);

    proto_tree_add_item(tree, hf_amqp_0_10_message_method,
                        tvb, offset+1, 1, ENC_BIG_ENDIAN);
    AMQP_INCREMENT(offset, 2, length);
    /
    flag1 = tvb_get_guint8(tvb, offset);
    flag2 = tvb_get_guint8(tvb, offset+1);
    ti = proto_tree_add_item(tree, hf_amqp_0_10_session_header, tvb, offset, 2, ENC_BIG_ENDIAN);
    if ((flag1 != 1) || ((flag2 & 0xfe) != 0))
        proto_item_append_text(ti, " (Invalid)");
    else
        proto_tree_add_item(tree, hf_amqp_0_10_session_header_sync,
                            tvb, offset + 1, 1, ENC_BIG_ENDIAN);
    AMQP_INCREMENT(offset, 2, length);

    ti = proto_tree_add_item(tree, hf_amqp_method_arguments,
                             tvb, offset, length - 4, ENC_NA);
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
    case AMQP_0_10_METHOD_MESSAGE_TRANSFER:
        if ((flag1 & ~0x07) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {     /
            str_size = tvb_get_guint8(tvb, offset);
            if ((offset + 1 + str_size) > length)
                THROW(ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_transfer_destination,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, (1 + str_size), length);
        }
        if (flag1 & 0x02) {     /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_transfer_accept_mode,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        if (flag1 & 0x04) {     /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_transfer_acquire_mode,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_ACCEPT:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            if ((offset + 2 + size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_message_accept_transfers,
                                     tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_REJECT:
        if ((flag1 & ~0x07) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            THROW_ON(((offset + 2 + size) > length), ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_message_accept_transfers,
                                     tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size, length);
        }
        if (flag1 & 0x02) {     /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_transfer_reject_code,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x04) {     /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_reject_text,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, (1 + str_size), length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_RELEASE:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            THROW_ON(((offset + 2 + size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_accept_transfers,
                                tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size, length);
        }
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_message_release_set_redelivered,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        break;

    case AMQP_0_10_METHOD_MESSAGE_ACQUIRE:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            size = tvb_get_ntohs(tvb, offset);
            THROW_ON(((offset + 2 + size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_accept_transfers,
                                tvb, offset, size + 2, ENC_NA);
            AMQP_INCREMENT(offset, 2, length);
            format_amqp_0_10_sequence_set(tvb, offset, size, ti);
            AMQP_INCREMENT(offset, size, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_RESUME:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_dest,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        if (flag1 & 0x02) {
            /
            size = tvb_get_ntohs(tvb, offset);
            THROW_ON(((offset + 2 + size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_resume_id,
                                tvb, offset + 2, size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 2 + size, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_SUBSCRIBE:
        if (flag2 != 0)
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_subscribe_queue,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        if (flag1 & 0x02) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_dest,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        if (flag1 & 0x04) {     /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_transfer_accept_mode,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        if (flag1 & 0x08) {     /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_transfer_acquire_mode,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_message_subscribe_exclusive,
                            tvb, flags_offset, 1, ENC_BIG_ENDIAN);
        if (flag1 & 0x20) {
            /
            size = tvb_get_ntohs(tvb, offset);
            THROW_ON(((offset + 2 + size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_resume_id,
                                tvb, offset, 2 + size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 2 + size, length);
        }
        if (flag1 & 0x40) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_subscribe_resume_ttl,
                                tvb, offset, 8, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 8, length);
        }
        if (flag1 & 0x80) {
            /
            map_size = tvb_get_ntohl(tvb, offset);
            THROW_ON(((offset + 4 + map_size) > length), ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_message_subscribe_args,
                                     tvb,
                                     offset,
                                     4 + map_size, ENC_NA);
            dissect_amqp_0_10_map (tvb,
                                   offset + 4,
                                   offset + 4 + map_size,
                                   map_size,
                                   ti);
            AMQP_INCREMENT(offset, 4 + map_size, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_CANCEL:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_dest,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_SET_FLOW_MODE:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_dest,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_flow_mode,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_FLOW:
        if ((flag1 & ~0x07) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_dest,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_credit_unit,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        if (flag1 & 0x04) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_credit_value,
                                tvb, offset, 4, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 4, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_FLUSH:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_dest,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        break;

    case AMQP_0_10_METHOD_MESSAGE_STOP:
        if ((flag1 & ~0x01) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            str_size = tvb_get_guint8(tvb, offset);
            THROW_ON(((offset + 1 + str_size) > length), ReportedBoundsError);
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_message_dest,
                                tvb, offset + 1, str_size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, 1 + str_size, length);
        }
        break;
    }
}