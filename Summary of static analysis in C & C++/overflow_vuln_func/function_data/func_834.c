static void
fReadPropertyConditional (tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, guint *offset)
{
	guint8 offs, tag_no, class_tag;
	guint32 lvt;

	if ((*offset) >= tvb_reported_length(tvb))
		return;

	offs = fTagHeader (tvb, offset, &tag_no, &class_tag, &lvt);

	switch (tag_no) {
	case 0:	/
		fObjectSelectionCriteria (tvb, pinfo, tree, offset);
		break;
	case 1:	/
		(*offset) += offs; /
		if ((lvt == 6) && (offs == 0)) {   /
			proto_tree_add_text(tree, tvb, (*offset)++, max(offs,1), "list of PropertyReferences {");
		}
		fPropertyReference (tvb, pinfo, tree, offset);

		if (((lvt == 7) && (offs == 0))) {   /
			proto_tree_add_text(tree, tvb, (*offset)++, 1, "}");
			return;
		}
		break;
	default:
		return;
	}
	fReadPropertyConditional (tvb, pinfo, tree, offset);
}
