static void
dissect_amqp_0_10_struct32(tvbuff_t *tvb,
                           packet_info *pinfo,
                           proto_tree *tree,
                           int offset,
                           guint32 struct_length)
{
    guint8      class_code;
    guint8      struct_code;
    guint8      flag1;
    guint16     size;
    guint16     value;
    guint32     array_length;
    guint32     consumed;
    proto_tree *ti;
    proto_tree *result;

    consumed    = 0;
    class_code  = tvb_get_guint8(tvb, offset);
    struct_code = tvb_get_guint8(tvb, offset + 1);

    switch(class_code) {
    case AMQP_0_10_CLASS_MESSAGE:
        switch (struct_code) {
        case AMQP_0_10_STRUCT_MESSAGE_DELIVERY_PROPERTIES:
            proto_item_set_text(tree, "message.delivery-properties");
            dissect_amqp_0_10_struct_delivery_properties(tvb,
                                                         pinfo,
                                                         tree,
                                                         offset,
                                                         struct_length);
            break;
        case AMQP_0_10_STRUCT_MESSAGE_FRAGMENT_PROPERTIES:
            proto_item_set_text(tree, "message.fragment-properties");
            dissect_amqp_0_10_struct_fragment_properties(tvb,
                                                         pinfo,
                                                         tree,
                                                         offset,
                                                         struct_length);
            break;
        case AMQP_0_10_STRUCT_MESSAGE_MESSAGE_PROPERTIES:
            proto_item_set_text(tree, "message.message-properties");
            dissect_amqp_0_10_struct_message_properties(tvb,
                                                        pinfo,
                                                        tree,
                                                        offset,
                                                        struct_length);
            break;
        case AMQP_0_10_STRUCT_MESSAGE_ACQUIRED:
            proto_item_set_text(tree, "message.acquired");
            result = proto_item_add_subtree(tree, ett_args);
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            offset += 2;
            flag1 = tvb_get_guint8(tvb, offset);
            proto_tree_add_item(result, hf_amqp_0_10_argument_packing_flags,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(consumed, 2, struct_length);
            offset += 2;
            if (flag1 & 0x01) {
                /
                size = tvb_get_ntohs(tvb, offset);
                THROW_ON(((consumed + size) > struct_length), ReportedBoundsError);
                ti = proto_tree_add_item(result,
                                         hf_amqp_0_10_struct_acquired_transfers,
                                         tvb, offset, size + 2, ENC_NA);
                format_amqp_0_10_sequence_set(tvb, offset + 2, size, ti);
            }
            break;
        case AMQP_0_10_STRUCT_MESSAGE_RESUME_RESULT:
            proto_item_set_text(tree, "message.resume-result");
            result = proto_item_add_subtree(tree, ett_args);
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            offset += 2;
            flag1 = tvb_get_guint8(tvb, offset);
            proto_tree_add_item(result, hf_amqp_0_10_argument_packing_flags,
                                tvb, offset, 2, ENC_BIG_ENDIAN);
            AMQP_INCREMENT(consumed, 2, struct_length);
            offset += 2;
            if (flag1 & 0x01) {
                /
                proto_tree_add_item(result,
                                    hf_amqp_0_10_struct_resume_result_offset,
                                    tvb, offset, 8, ENC_BIG_ENDIAN);
            }
            break;
        }
        break;

    case AMQP_0_10_CLASS_DTX:
        switch (struct_code) {
        case AMQP_0_10_STRUCT_DTX_XA_RESULT:
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            offset += 2;
            /
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            offset += 2;
            value = tvb_get_ntohs(tvb, offset);
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            /
            proto_item_set_text(tree, "dtx.xa-status: %s",
                                val_to_str(value,
                                           amqp_0_10_xa_status,
                                           "Invalid xa-status %d"));
            break;

        case AMQP_0_10_STRUCT_DTX_RECOVER_RESULT:
            proto_item_set_text(tree, "dtx.recover-result");
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            offset += 2;
            /
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            offset += 2;
            array_length = tvb_get_ntohl(tvb, offset);
            AMQP_INCREMENT(consumed, 4, struct_length);
            offset += 4;
            dissect_amqp_0_10_array(tvb,
                                    pinfo,
                                    offset,
                                    offset + array_length,
                                    array_length,
                                    tree);
            break;
        }
        break;

    case AMQP_0_10_CLASS_EXCHANGE:
        switch (struct_code) {
        case AMQP_0_10_STRUCT_EXCHANGE_QUERY_RESULT:
            proto_item_set_text(tree, "exchange.exchange-query-result");
            dissect_amqp_0_10_struct_exchange_query_result(tvb,
                                                           pinfo,
                                                           tree,
                                                           offset,
                                                           struct_length);
            break;

        case AMQP_0_10_STRUCT_EXCHANGE_BOUND_RESULT:
            proto_item_set_text(tree, "exchange.exchange-bound-result");
            result = proto_item_add_subtree(tree, ett_args);
            AMQP_INCREMENT(consumed, 2, struct_length);  /
            offset += 2;
            proto_tree_add_item(result,
                                hf_amqp_0_10_struct_exchange_bound_result_exchange_not_found,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            proto_tree_add_item(result,
                                hf_amqp_0_10_struct_exchange_bound_result_queue_not_found,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            proto_tree_add_item(result,
                                hf_amqp_0_10_struct_exchange_bound_result_queue_not_matched,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            proto_tree_add_item(result,
                                hf_amqp_0_10_struct_exchange_bound_result_key_not_matched,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            proto_tree_add_item(result,
                                hf_amqp_0_10_struct_exchange_bound_result_args_not_matched,
                                tvb, offset, 1, ENC_BIG_ENDIAN);
            break;
        }
        break;

    case AMQP_0_10_CLASS_QUEUE:
        switch (struct_code) {
        case AMQP_0_10_STRUCT_QUEUE_QUERY_RESULT:
            proto_item_set_text(tree, "queue.queue-query-result");
            dissect_amqp_0_10_struct_queue_query_result(tvb,
                                                        pinfo,
                                                        tree,
                                                        offset,
                                                        struct_length);
            break;
        }
        break;

    case AMQP_0_10_CLASS_FILE:
        switch (struct_code) {
        case AMQP_0_10_STRUCT_FILE_PROPERTIES:
            proto_item_set_text(tree, "file.file-properties");
            dissect_amqp_0_10_struct_file_properties(tvb,
                                                     pinfo,
                                                     tree,
                                                     offset,
                                                     struct_length);
            break;
        }
        break;

    case AMQP_0_10_CLASS_STREAM:
        switch (struct_code) {
        case AMQP_0_10_STRUCT_STREAM_PROPERTIES:
            proto_item_set_text(tree, "stream.stream-properties");
            dissect_amqp_0_10_struct_stream_properties(tvb,
                                                       pinfo,
                                                       tree,
                                                       offset,
                                                       struct_length);
            break;
        }
        break;
    }
}
