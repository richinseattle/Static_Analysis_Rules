static tvbuff_t *
dissect_pft_fec_detailed(tvbuff_t * tvb, packet_info * pinfo, proto_tree * tree,
  guint32 findex _U_,
  guint32 fcount,
  guint16 seq,
  gint offset,
  guint16 plen,
  gboolean fec _U_,
  guint16 rsk,
  guint16 rsz,
  fragment_data *fdx
)
{
  guint16 decoded_size;
  guint32 c_max;
  guint32 rx_min;
  tvbuff_t *new_tvb=NULL;

  if (fcount > MAX_FRAGMENTS) {
    if (tree)
      proto_tree_add_text(tree, tvb , 0, -1, "[Reassembly of %d fragments not attempted]", fcount);
    return NULL;
  }

  decoded_size = fcount*plen;
  c_max = fcount*plen/(rsk+PFT_RS_P);  /
  rx_min = fcount - (c_max*PFT_RS_P/plen);
  if (fdx)
    new_tvb = process_reassembled_data (tvb, offset, pinfo,
                                        "Reassembled DCP (ETSI)",
                                        fdx, &dcp_frag_items,
                                        NULL, tree);
  else {
    guint fragments=0;
    guint32 *got;
    fragment_data *fd;
    fragment_data *fd_head;

    if(tree)
      proto_tree_add_text (tree, tvb, 0, -1, "want %d, got %d need %d",
                           fcount, fragments, rx_min
        );
    got = (guint32 *)ep_alloc(fcount*sizeof(guint32));

    /
    fd = fragment_get(&dcp_reassembly_table, pinfo, seq, NULL);
    for (fd_head = fd; fd_head != NULL && fragments < fcount; fd_head = fd_head->next) {
      if(fd_head->data) {
        got[fragments++] = fd_head->offset; /
      }
    }
    /
    if(fragments>=rx_min) { /
      guint i,current_findex;
      fragment_data *frag=NULL;
      guint8 *dummy_data = (guint8*) ep_alloc0 (plen);
      tvbuff_t *dummytvb = tvb_new_real_data(dummy_data, plen, plen);
      /
      if(tree)
          proto_tree_add_text (tree, tvb, 0, -1, "want %d, got %d need %d",
                               fcount, fragments, rx_min
            );
      /
      current_findex = 0;
      for(i=0; i<fragments; i++) {
        guint next_fragment_we_have = got[i];
        if (next_fragment_we_have > MAX_FRAGMENTS) {
          proto_tree_add_text(tree, tvb , 0, -1, "[Reassembly of %d fragments not attempted]", next_fragment_we_have);
          return NULL;
        }
        if (next_fragment_we_have-current_findex > MAX_FRAG_GAP) {
          proto_tree_add_text(tree, tvb , 0, -1,
              "[Missing %d consecutive packets. Don't attempt reassembly]",
              next_fragment_we_have-current_findex);
          return NULL;
        }
        for(; current_findex<next_fragment_we_have; current_findex++) {
          frag = fragment_add_seq_check (&dcp_reassembly_table,
                                         dummytvb, 0, pinfo, seq, NULL,
                                         current_findex, plen, (current_findex+1!=fcount));
        }
        current_findex++; /
      }
      tvb_free(dummytvb);

      if(frag)
        new_tvb = process_reassembled_data (tvb, offset, pinfo,
                                            "Reassembled DCP (ETSI)",
                                            frag, &dcp_frag_items,
                                            NULL, tree);
    }
  }
  if(new_tvb) {
    gboolean decoded = TRUE;
    tvbuff_t *dtvb = NULL;
    const guint8 *input = tvb_get_ptr(new_tvb, 0, -1);
    guint16 reassembled_size = tvb_length(new_tvb);
    guint8 *deinterleaved = (guint8*) g_malloc (reassembled_size);
    guint8 *output = (guint8*) g_malloc (decoded_size);
    rs_deinterleave(input, deinterleaved, plen, fcount);

    dtvb = tvb_new_child_real_data(tvb, deinterleaved, reassembled_size, reassembled_size);
    add_new_data_source(pinfo, dtvb, "Deinterleaved");
    tvb_set_free_cb(dtvb, g_free);

    decoded = rs_correct_data(deinterleaved, output, c_max, rsk, rsz);
    if(tree)
      proto_tree_add_boolean (tree, hf_edcp_rs_ok, tvb, offset, 2, decoded);

    new_tvb = tvb_new_child_real_data(dtvb, output, decoded_size, decoded_size);
    add_new_data_source(pinfo, new_tvb, "RS Error Corrected Data");
    tvb_set_free_cb(new_tvb, g_free);
  }
  return new_tvb;
}
