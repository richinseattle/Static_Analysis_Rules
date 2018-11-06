static void
dissect_amqp_0_10_xid (tvbuff_t *tvb,
                       int offset,
                       guint16 xid_length,
                       proto_item *ti)
{
    proto_item *xid_tree;
    guint8      flag1/;
    guint8      len8;
    int         max_length;

    max_length = offset + xid_length;
    xid_tree = proto_item_add_subtree(ti, ett_args);
    flag1 = tvb_get_guint8(tvb, offset);
    /
    proto_tree_add_item(xid_tree, hf_amqp_0_10_argument_packing_flags,
                        tvb, offset, 2, ENC_BIG_ENDIAN);
    AMQP_INCREMENT(offset, 2, max_length);
    if (flag1 & 0x01) {
        /
        proto_tree_add_item(xid_tree,
                            hf_amqp_0_10_dtx_xid_format,
                            tvb, offset, 4, ENC_BIG_ENDIAN);
        AMQP_INCREMENT(offset, 4, max_length);
    }
    if (flag1 & 0x02) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        if ((offset + 1 + len8) > max_length)
            THROW(ReportedBoundsError);
        proto_tree_add_item(xid_tree,
                            hf_amqp_0_10_dtx_xid_global_id,
                            tvb, offset + 1, len8, ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
    if (flag1 & 0x04) {
        /
        len8 = tvb_get_guint8(tvb, offset);
        if ((offset + 1 + len8) > max_length)
            THROW(ReportedBoundsError);
        proto_tree_add_item(xid_tree,
                            hf_amqp_0_10_dtx_xid_branch_id,
                            tvb, offset + 1, len8, ENC_NA);
        AMQP_INCREMENT(offset, (1 + len8), max_length);
    }
}
