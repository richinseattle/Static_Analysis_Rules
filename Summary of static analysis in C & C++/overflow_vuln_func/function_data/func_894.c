static void
dissect_amqp_0_10_execution(tvbuff_t *tvb,
                            packet_info *pinfo,
                            proto_tree *tree,
                            int offset, guint16 length)
{
    proto_item  *args_tree;
    proto_item  *ti;
    proto_item  *flags_item;
    guint8       amqp_class = 0, method;
    guint8       flag1, flag2;
    guint16      size;
    guint32      struct_size;
    int          class_hf;
    const gchar *method_name;

    method = tvb_get_guint8(tvb, offset+1);
    method_name = val_to_str_const(method, amqp_0_10_execution_methods,
                                   "<invalid execution method>");
    col_append_str(pinfo->cinfo, COL_INFO, method_name);
    col_append_str(pinfo->cinfo, COL_INFO, " ");
    col_set_fence(pinfo->cinfo, COL_INFO);

    proto_tree_add_item(tree, hf_amqp_0_10_execution_method,
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
    flag1 = tvb_get_guint8(tvb, offset);
    flag2 = tvb_get_guint8(tvb, offset+1);
    flags_item = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_argument_packing_flags,
                                     tvb, offset, 2, ENC_BIG_ENDIAN);
    AMQP_INCREMENT(offset, 2, length);
    switch (method) {
    case AMQP_0_10_METHOD_EXECUTION_SYNC:
        if ((flag1 != 0) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        break;

    case AMQP_0_10_METHOD_EXECUTION_RESULT:
        if ((flag1 & ~0x03) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_execution_command_id,
                                tvb, offset, 4, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 4, length);
        }
        if (flag1 & 0x02) {
            /
            struct_size = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            if ((offset + struct_size) > length)
                THROW(ReportedBoundsError);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_undissected_struct32,
                                     tvb, offset, struct_size, ENC_NA);
            dissect_amqp_0_10_struct32(tvb, pinfo, ti, offset, struct_size);
            AMQP_INCREMENT(offset, struct_size, length);
        }
        break;

    case AMQP_0_10_METHOD_EXECUTION_EXCEPTION:
        if ((flag1 & ~0x7f) || (flag2 != 0))
            expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
        if (flag1 & 0x01) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_execution_exception_error,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 2, length);
        }
        if (flag1 & 0x02) {
            /
            proto_tree_add_item(args_tree,
                                hf_amqp_0_10_method_execution_command_id,
                                tvb, offset, 4, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 4, length);
        }
        if (flag1 & 0x04) {
            /
            amqp_class = tvb_get_guint8(tvb, offset);
            proto_tree_add_item(args_tree, hf_amqp_0_10_class,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        if (flag1 & 0x08) {
            /
            switch(amqp_class) {
            case AMQP_0_10_CLASS_CONNECTION:
                class_hf = hf_amqp_0_10_connection_method;
                break;
            case AMQP_0_10_CLASS_SESSION:
                class_hf = hf_amqp_0_10_session_method;
                break;
            case AMQP_0_10_CLASS_EXECUTION:
                class_hf = hf_amqp_0_10_execution_method;
                break;
            case AMQP_0_10_CLASS_MESSAGE:
                class_hf = hf_amqp_0_10_message_method;
                break;
            case AMQP_0_10_CLASS_TX:
                class_hf = hf_amqp_0_10_tx_method;
                break;
            case AMQP_0_10_CLASS_DTX:
                class_hf = hf_amqp_0_10_dtx_method;
                break;
            case AMQP_0_10_CLASS_EXCHANGE:
                class_hf = hf_amqp_0_10_exchange_method;
                break;
            case AMQP_0_10_CLASS_QUEUE:
                class_hf = hf_amqp_0_10_queue_method;
                break;
            case AMQP_0_10_CLASS_FILE:
                class_hf = hf_amqp_0_10_file_method;
                break;
            case AMQP_0_10_CLASS_STREAM:
                class_hf = hf_amqp_0_10_stream_method;
                break;
            default:
                class_hf = -1;
                break;
            }
            if (class_hf != -1)
                proto_tree_add_item(args_tree, class_hf,
                                    tvb, offset, 1, ENC_BIG_ENDIAN);
            else
                expert_add_info_format(pinfo, args_tree, &ei_amqp_invalid_class_code, "Invalid class code %x", amqp_class);
            AMQP_INCREMENT(offset, 1, length);
        }
        if (flag1 & 0x10) {
            /
            proto_tree_add_item(args_tree, hf_amqp_0_10_method_execution_field_index,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(offset, 1, length);
        }
        if (flag1 & 0x20) {
            /
            size = tvb_get_ntohs(tvb, offset);
            if ((offset + 2 + size) > length)
                THROW(ReportedBoundsError);
            proto_tree_add_item(args_tree, hf_amqp_0_10_method_execution_description,
                                tvb, offset + 2, size, ENC_ASCII|ENC_NA);
            AMQP_INCREMENT(offset, (2 + size), length);
        }
        if (flag1 & 0x40) {
            /
            struct_size = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(offset, 4, length);
            ti = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_method_execution_error_info,
                                     tvb,
                                     offset,
                                     struct_size, ENC_NA);
            dissect_amqp_0_10_map (tvb,
                                   offset,
                                   offset + struct_size,
                                   struct_size,
                                   ti);
            AMQP_INCREMENT(offset, struct_size, length);
        }
        break;
    }
}
