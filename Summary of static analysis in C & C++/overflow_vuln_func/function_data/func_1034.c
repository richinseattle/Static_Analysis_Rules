int
dissect_ber_set(gboolean implicit_tag, asn1_ctx_t *actx, proto_tree *parent_tree, tvbuff_t *tvb, int offset, const ber_sequence_t *set, gint hf_id, gint ett_id) {
    gint8       classx;
    gboolean    pcx, ind = 0, ind_field, imp_tag = FALSE;
    gint32      tagx;
    guint32     lenx;
    proto_tree *tree     = parent_tree;
    proto_item *item     = NULL;
    proto_item *cause;
    int         end_offset, s_offset;
    int         hoffset;
    gint        length_remaining;
    tvbuff_t   *next_tvb;
    guint32     mandatory_fields = 0;
    guint8      set_idx;
    gboolean    first_pass;
    const ber_sequence_t *cset = NULL;

#define MAX_SET_ELEMENTS 32

    s_offset = offset;

#ifdef DEBUG_BER
    {
const char *name;
header_field_info *hfinfo;
if (hf_id >= 0) {
hfinfo = proto_registrar_get_nth(hf_id);
name = hfinfo->name;
} else {
name = "unnamed";
}
if (tvb_length_remaining(tvb, offset) > 3) {
printf("SET dissect_ber_set(%s) entered offset:%d len:%d %02x:%02x:%02x\n", name, offset, tvb_length_remaining(tvb, offset), tvb_get_guint8(tvb, offset), tvb_get_guint8(tvb, offset+1), tvb_get_guint8(tvb, offset+2));
} else {
printf("SET dissect_ber_set(%s) entered\n", name);
}
}
#endif

    if (!implicit_tag) {
        hoffset = offset;
        /
        offset = dissect_ber_identifier(actx->pinfo, tree, tvb, offset, &classx, &pcx, &tagx);
        offset = dissect_ber_length(actx->pinfo, tree, tvb, offset, &lenx, &ind);
        if (ind) {
        /
          end_offset = offset + lenx -2;
        } else {
          end_offset = offset + lenx;
        }

        /
        if ((classx != BER_CLASS_APP) && (classx != BER_CLASS_PRI)) {
            if (!pcx
             || (!implicit_tag && ((classx != BER_CLASS_UNI)
                                || (tagx != BER_UNI_TAG_SET)))) {
                tvb_ensure_bytes_exist(tvb, hoffset, 2);
                cause = proto_tree_add_string_format_value(
                    tree, hf_ber_error, tvb, offset, lenx, "set_expected",
                    "SET expected but class:%s(%d) %s tag:%d was found",
                    val_to_str_const(classx, ber_class_codes, "Unknown"),
                    classx,
                    pcx ? ber_pc_codes_short.true_string : ber_pc_codes_short.false_string,
                    tagx);
                expert_add_info(actx->pinfo, cause, &ei_ber_expected_set);
                if (decode_unexpected) {
                    proto_tree *unknown_tree = proto_item_add_subtree(cause, ett_ber_unknown);
                    dissect_unknown_ber(actx->pinfo, tvb, hoffset, unknown_tree);
                }
                return end_offset;
            }
        }
    } else {
        /
        lenx = tvb_length_remaining(tvb, offset);
        end_offset = offset+lenx;
    }

    /
    if (hf_id >= 0) {
        if (parent_tree) {
            item = proto_tree_add_item(parent_tree, hf_id, tvb, offset, lenx, ENC_BIG_ENDIAN);
            tree = proto_item_add_subtree(item, ett_id);
        }
    }

    /
    for (set_idx = 0; (cset = &set[set_idx])->func && (set_idx < MAX_SET_ELEMENTS); set_idx++) {

        if (!(cset->flags & BER_FLAGS_OPTIONAL))
            mandatory_fields |= 1 << set_idx;

    }

    /
    while (offset < end_offset) {
        gint8    ber_class;
        gboolean pc;
        gint32   tag;
        guint32  len;
        int      eoffset, count;

        /

            if ((tvb_get_guint8(tvb, offset) == 0) && (tvb_get_guint8(tvb, offset+1) == 0)) {
                if (show_internal_ber_fields) {
                    proto_tree_add_text(tree, tvb, s_offset, offset+2, "SEQ EOC");
                }
                return end_offset;
            }
        /
        hoffset = offset;
        /
        offset  = get_ber_identifier(tvb, offset, &ber_class, &pc, &tag);
        offset  = get_ber_length(tvb, offset, &len, &ind_field);
        eoffset = offset + len;

        /


        for (first_pass = TRUE, cset = set, set_idx = 0; cset->func || first_pass; cset++, set_idx++) {

            /
            if (!cset->func) {
                first_pass = FALSE;

                cset = set; /
                set_idx = 0;
            }

            if ((first_pass && ((cset->ber_class == ber_class) && (cset->tag == tag))) ||
                (!first_pass && ((cset->ber_class == BER_CLASS_ANY) && (cset->tag == -1))) ) /
            {
                if (!(cset->flags & BER_FLAGS_NOOWNTAG) ) {
                    /
                    hoffset = dissect_ber_identifier(actx->pinfo, tree, tvb, hoffset, NULL, NULL, NULL);
                    hoffset = dissect_ber_length(actx->pinfo, tree, tvb, hoffset, NULL, NULL);
                    length_remaining = tvb_length_remaining(tvb, hoffset);
                    if (length_remaining > (eoffset - hoffset - (2 * ind_field)))
                        length_remaining = eoffset - hoffset - (2 * ind_field);
                    next_tvb = tvb_new_subset(tvb, hoffset, length_remaining, eoffset - hoffset - (2 * ind_field));
                } else {
                    length_remaining = tvb_length_remaining(tvb, hoffset);
                    if (length_remaining > (eoffset - hoffset))
                        length_remaining = eoffset - hoffset;
                    next_tvb = tvb_new_subset(tvb, hoffset, length_remaining, eoffset - hoffset);
                }


#if 0
                /
                if    ((eoffset-hoffset)>length_remaining) {
                    /                     * length) of if the tvb is short, then just
                     * give it all of the tvb and hope for the best.
                     */
                    next_tvb = tvb_new_subset_remaining(tvb, hoffset);
                } else {

                }
#endif

#ifdef DEBUG_BER
{
const char *name;
header_field_info *hfinfo;
if (hf_id >= 0) {
hfinfo = proto_registrar_get_nth(hf_id);
name = hfinfo->name;
} else {
name = "unnamed";
}
if (tvb_length_remaining(next_tvb, 0) > 3) {
printf("SET dissect_ber_set(%s) calling subdissector offset:%d len:%d %02x:%02x:%02x\n", name, offset, tvb_length_remaining(next_tvb, 0), tvb_get_guint8(next_tvb, 0), tvb_get_guint8(next_tvb, 1), tvb_get_guint8(next_tvb, 2));
} else {
printf("SET dissect_ber_set(%s) calling subdissector\n", name);
}
}
#endif
                if (next_tvb == NULL) {
                    /
                    THROW(ReportedBoundsError);
                }
                imp_tag = FALSE;
                if ((cset->flags & BER_FLAGS_IMPLTAG))
                    imp_tag = TRUE;
                count = cset->func(imp_tag, next_tvb, 0, actx, tree, *cset->p_id);

                /
                if (count || (first_pass && ((len == 0) || ((ind_field == 1) && (len == 2))))) {
                    /
                    if (set_idx < MAX_SET_ELEMENTS)
                        mandatory_fields &= ~(1 << set_idx);

                    offset = eoffset;

                    if (!(cset->flags & BER_FLAGS_NOOWNTAG) ) {
                        /
                        if (ind_field == 1) {
                            /
                            if (show_internal_ber_fields) {
                                proto_tree_add_text(tree, tvb, offset, count, "SET FIELD EOC");
                            }
                        }
                    }
                    break;
                }
            }
        }

        if (!cset->func) {
            /
            cause = proto_tree_add_string_format_value(
                tree, hf_ber_error, tvb, offset, len, "unknown_field",
                "Unknown field in SET class:%s(%d) tag:%d",
                val_to_str_const(ber_class, ber_class_codes, "Unknown"),
                ber_class,
                tag);
            expert_add_info(actx->pinfo, cause, &ei_ber_unknown_field_set);
            if (decode_unexpected) {
                proto_tree *unknown_tree = proto_item_add_subtree(cause, ett_ber_unknown);
                dissect_unknown_ber(actx->pinfo, tvb, hoffset, unknown_tree);
            }
            offset = eoffset;
        }
    }

    if (mandatory_fields) {

        /

        for (set_idx = 0;  (cset = &set[set_idx])->func && (set_idx < MAX_SET_ELEMENTS); set_idx++) {
            if (mandatory_fields & (1 << set_idx)) {
                /
                cause = proto_tree_add_string_format_value(
                    tree, hf_ber_error, tvb, offset, lenx, "missing_field",
                    "Missing field in SET class:%s(%d) tag:%d expected",
                    val_to_str_const(cset->ber_class, ber_class_codes, "Unknown"),
                    cset->ber_class,
                    cset->tag);
                expert_add_info(actx->pinfo, cause, &ei_ber_missing_field_set);

            }

        }
    }

    /
    if (offset != end_offset) {
        tvb_ensure_bytes_exist(tvb, offset-2, 2);
        cause = proto_tree_add_string_format_value(
            tree, hf_ber_error, tvb, offset-2, 2, "illegal_length",
            "SET ate %d too many bytes",
            offset - end_offset);
        expert_add_info_format(actx->pinfo, cause, &ei_ber_error_length,
            "BER Error: too many bytes in SET");
    }

    if (ind) {
        /
        end_offset += 2;
        if (show_internal_ber_fields) {
            proto_tree_add_text(tree, tvb, end_offset-2, 2 , "SET EOC");
        }
    }

    return end_offset;

}
