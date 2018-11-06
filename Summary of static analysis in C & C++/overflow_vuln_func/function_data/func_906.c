static void
dissect_amqp_0_10_struct_file_properties(tvbuff_t *tvb,
                                         packet_info *pinfo,
                                         proto_tree *tree,
                                         int offset,
                                         guint32 struct_length)
{
    proto_item *ti;
    proto_item *props;
    proto_item *flags_item;
    guint8      flag1, flag2;
    guint8      len8;
    guint32     map_length;
    guint64     timestamp;
    int         max_length;
    nstime_t    tv;

    max_length = offset + struct_length;
    props = proto_item_add_subtree(tree, ett_args);
    AMQP_INCREMENT(offset, 2, max_length);  /
    flag1 = tvb_get_guint8(tvb, offset);
    flag2 = tvb_get_guint8(tvb, offset+1);
    flags_item = proto_tree_add_item(props,
                                     hf_amqp_0_10_argument_packing_flags,
                                     tvb, offset, 2, ENC_BIG_ENDIAN);
    if (flag2 & ~0x01)
        expert_add_info(pinfo, flags_item, &ei_amqp_bad_flag_value);
    AMQP_INCREMENT(offset, 2, max_length);
    if (flag1 & 0x01) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(props,
                            hf_amqp_0_10_struct_file_properties_content_type,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag1 & 0x02) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(props,
                            hf_amqp_0_10_struct_file_properties_content_encoding,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag1 & 0x04) {
        /
        map_length = tvb_get_ntohl(tvb, offset);
        AMQP_INCREMENT(offset, 4, max_length);
        ti = proto_tree_add_item(props,
                                 hf_amqp_0_10_struct_file_properties_headers,
                                 tvb,
                                 offset,
                                 map_length, ENC_NA);
        dissect_amqp_0_10_map (tvb,
                               offset,
                               offset + map_length,
                               map_length,
                               ti);
        AMQP_INCREMENT(offset, map_length, max_length);
    }
    if (flag1 & 0x08) {
        /
        proto_tree_add_item(props,
                            hf_amqp_0_10_struct_file_properties_priority,
                            tvb, offset, 1, ENC_BIG_ENDIAN);
        AMQP_INCREMENT(offset, 1, max_length);
    }
    if (flag1 & 0x10) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(props,
                            hf_amqp_0_10_struct_file_properties_reply_to,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag1 & 0x20) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(props,
                            hf_amqp_0_10_struct_file_properties_message_id,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag1 & 0x40) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(props,
                            hf_amqp_0_10_struct_file_properties_filename,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag1 & 0x80) {
        /
        timestamp = tvb_get_ntoh64(tvb, offset);
        tv.secs = (time_t)timestamp;
        tv.nsecs = 0;
        proto_tree_add_time(props,
                            hf_amqp_0_10_struct_file_properties_timestamp,
                            tvb, offset, 8, &tv);
        AMQP_INCREMENT(offset, 8, max_length);
    }
    if (flag2 & 0x01) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        proto_tree_add_item(props,
                            hf_amqp_0_10_struct_file_properties_cluster_id,
                            tvb, offset + 1, len8, ENC_ASCII|ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
}