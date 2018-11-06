static guint
fDeviceObjectPropertyReference (tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, guint offset)
{
    guint   lastoffset = 0;
    guint8  tag_no, tag_info;
    guint32 lvt;

    while (tvb_reported_length_remaining(tvb, offset) > 0) {
        lastoffset = offset;
        /
        fTagHeader (tvb, offset, &tag_no, &tag_info, &lvt);
        if (tag_is_closing(tag_info)) {
            return offset;
        }
        switch (tag_no) {
        case 0: /
            offset = fObjectIdentifier (tvb, pinfo, tree, offset);
            break;
        case 1: /
            offset = fPropertyIdentifier (tvb, pinfo, tree, offset);
            break;
        case 2: /
            offset = fUnsignedTag (tvb, tree, offset,
                "arrayIndex: ");
            break;
        case 3: /
            offset = fObjectIdentifier (tvb, pinfo, tree, offset);
            break;
        default:
            return offset;
        }
        if (offset == lastoffset) break;     /
    }
    return offset;
}
