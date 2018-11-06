static void
dissect_amqp_0_10_struct_delivery_properties(tvbuff_t *tvb,
                                             packet_info *pinfo,
                                             proto_tree *tree,
                                             int offset,
                                             guint32 struct_length)
{
    proto_item *args_tree;
    proto_item *flags_item;
    guint8      flag1, flag2;
    guint8      len8;
    guint16     len16;
    guint64     timestamp;
    int         flags_offset;
    int         max_length;
    nstime_t    tv;

    max_length = offset + struct_length;
    args_tree = proto_item_add_subtree(tree, ett_args);
    AMQP_INCREMENT(offset, 2, max_length);  /
    flags_offset = offset;
    flag1 = tvb_get_guint8(tvb, offset);
    flag2 = tvb_get_guint8(tvb, offset+1);
    flags_item = proto_tree_add_item(args_tree,
                                     hf_amqp_0_10_argument_packing_flags,
                                     tvb, offset, 2, ENC_BIG_ENDIAN);
    if (flag2 & ~0x0f)
        expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
    AMQP_INCREMENT(offset, 2, max_length);

    /
    proto_tree_add_item(args_tree,
                        hf_amqp_0_10_struct_delivery_properties_discard_unroutable,
                        tvb, flags_offset, 1, ENC_BIG_ENDIAN);
    proto_tree_add_item(args_tree,
                        hf_amqp_0_10_struct_delivery_properties_immediate,
                        tvb, flags_offset, 1, ENC_BIG_ENDIAN);
    proto_tree_add_item(args_tree,
                        hf_amqp_0_10_struct_delivery_properties_redelivered,
                        tvb, flags_offset, 1, ENC_BIG_ENDIAN);
    if (flag1 & 0x08) {
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_priority,
                            tvb, offset, 1, ENC_BIG_ENDIAN);
        AMQP_INCREMENT(offset, 1, max_length);
    }
    if (flag1 & 0x10) {
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_mode,
                            tvb, offset, 1, ENC_BIG_ENDIAN);
        AMQP_INCREMENT(offset, 1, max_length);
    }
    if (flag1 & 0x20) {
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_ttl,
                            tvb, offset, 8, ENC_BIG_ENDIAN);
        AMQP_INCREMENT(offset, 8, max_length);
    }
    if (flag1 & 0x40) {
        /
        timestamp = tvb_get_ntoh64(tvb, offset);
        tv.secs = (time_t)timestamp;
        tv.nsecs = 0;
        proto_tree_add_time(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_timestamp,
                            tvb, offset, 8, &tv);
        AMQP_INCREMENT(offset, 8, max_length);
    }
    if (flag1 & 0x80) {
        /
        timestamp = tvb_get_ntoh64(tvb, offset);
        tv.secs = (time_t)timestamp;
        tv.nsecs = 0;
        proto_tree_add_time(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_expiration,
                            tvb, offset, 8, &tv);
        AMQP_INCREMENT(offset, 8, max_length);
    }
    if (flag2 & 0x01) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_exchange,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag2 & 0x02) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_routing_key,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag2 & 0x04) {
        /
        len16 = tvb_get_ntohs(tvb, offset);
        THROW_ON(((offset + 2 + len16) > max_length), ReportedBoundsError);
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_method_message_resume_id,
                            tvb, offset + 2, len16, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (2 + len16), max_length);
    }
    if (flag2 & 0x08) {
        /
        proto_tree_add_item(args_tree,
                            hf_amqp_0_10_struct_delivery_properties_resume_ttl,
                            tvb, offset, 8, ENC_BIG_ENDIAN);
        AMQP_INCREMENT(offset, 8, max_length);
    }
}
