static int
dissect_lpp_T_utcWNot(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 8191U, NULL, FALSE);

#line 1061 "../../asn1/lpp/lpp.cnf"
  proto_item_append_text(actx->created_item, " weeks");


  return offset;
}
