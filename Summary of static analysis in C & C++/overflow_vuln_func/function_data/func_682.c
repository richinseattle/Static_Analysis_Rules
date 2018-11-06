void
proto_register_qnet6(void)
{
  static hf_register_info hf[] = {
    {&hf_qnet6_l4_padding,
     {"Padding", "qnet6.l4.padding",
      FT_UINT16, BASE_HEX, NULL, 0,
      NULL, HFILL
     }
    },
    {&hf_qnet6_l4_ver,
     {"Version", "qnet6.l4.ver",
      FT_UINT8, BASE_DEC, VALS(qnet6_ver_vals), 0,
      "QNET6 L4 Packet Version", HFILL
     }
    },
    {&hf_qnet6_l4_type,
     {"Type", "qnet6.l4.type",
      FT_UINT8, BASE_HEX, VALS(qnet6_type_vals), 0,
      "QNET6 L4 Upper layer protocol type", HFILL}
    },
    {&hf_qnet6_l4_flags,
     {"Flag", "qnet6.l4.flags",
      FT_UINT8, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_l4_flags_first,
     {"First Fragment", "qnet6.l4.flags.first",
      FT_BOOLEAN, 8, TFS(&tfs_yes_no), QNET_L4_FLAGS_FIRST,
      "QNET6 L4 Packet first fragment", HFILL}
    },
    {&hf_qnet6_l4_flags_last,
     {"Last Fragment", "qnet6.l4.flags.last",
      FT_BOOLEAN, 8, TFS(&tfs_yes_no), QNET_L4_FLAGS_LAST,
      "QNET6 L4 Packet last fragment", HFILL}
    },
    {&hf_qnet6_l4_flags_crc,
     {"CRC", "qnet6.l4.flags.crc",
      FT_BOOLEAN, 8, TFS(&tfs_used_notused), QNET_L4_FLAGS_CRC,
      "QNET6 L4 Packet crc used", HFILL}
    },

    {&hf_qnet6_l4_layer,
     {"Layer", "qnet6.l4.layer",
      FT_UINT8, BASE_DEC, VALS(qnet6_layer_vals), 0,
      "QNET6 L4 Packet layer", HFILL}
    },
    /
    /
    {&hf_qnet6_l4_qos_info,
     {"Qos info", "qnet6.qos.qos_info",
      FT_NONE, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_l4_qos_src_nd_for_dst,
     {"Src_nd_for_dst", "qnet6.qos.src_nd_for_dst",
      FT_UINT16, BASE_DEC, NULL, 0,
      "QNET6 source node id for destination node", HFILL}
    },
    {&hf_qnet6_l4_qos_dst_nd_for_src,
     {"Dst_nd_for_src", "qnet6.qos.dst_nd_for_src",
      FT_UINT16, BASE_DEC, NULL, 0,
      "QNET6 destination node id for source node", HFILL}
    },
    /
    {&hf_qnet6_l4_qos_src_conn_id,
     {"Sconn", "qnet6.qos.sconn",
      FT_UINT32, BASE_HEX, NULL, 0,
      "QNET6 source node's connection id", HFILL}
    },
    {&hf_qnet6_l4_qos_dst_conn_id,
     {"Dconn", "qnet6.qos.dconn",
      FT_UINT32, BASE_HEX, NULL, 0,
      "QNET6 destination node's connection id", HFILL}
    },
    {&hf_qnet6_l4_qos_src_seq_num,
     {"Seq", "qnet6.qos.seq",
      FT_UINT32, BASE_DEC, NULL, 0,
      "QNET6 connection sequence number", HFILL}
    },
    {&hf_qnet6_l4_qos_qos_type,
     {"Sos_type", "qnet6.qos.qos_type",
      FT_UINT16, BASE_DEC, VALS(qnet6_qos_type_vals), 0,
      "QNET6 qos type", HFILL}
    },
    {&hf_qnet6_l4_qos_src_qos_idx,
     {"Src_qos_idx", "qnet6.qos.src_qos_idx",
      FT_UINT16, BASE_DEC, NULL, 0,
      "QNET6 source node qos index", HFILL}
    },

    /
    {&hf_qnet6_l4_offset,
     {"Offset", "qnet6.l4.offset",
      FT_UINT32, BASE_DEC, NULL, 0,
      "QNET6 Packet offset in stream", HFILL}
    },
    {&hf_qnet6_l4_length,
     {"Length", "qnet6.l4.length",
      FT_UINT32, BASE_DEC, NULL, 0,
      "QNET6 Packet payload length", HFILL}
    },
    {&hf_qnet6_l4_crc,
     {"Crc", "qnet6.l4.crc",
      FT_UINT32, BASE_HEX, NULL, 0,
      "QNET6 Packet cksum of header and payload", HFILL}
    }

  };
  static hf_register_info hf_qos[] = {
    {&hf_qnet6_qos_tcs_src_name_off,
     {"Src_name_off", "qnet6.qos.src_name_off",
      FT_UINT16, BASE_DEC, NULL, 0,
      "Source name offset", HFILL}
    },
    {&hf_qnet6_qos_tcs_src_name_generated,
     {"Src_name", "qnet6.qos.src_name",
      FT_STRING, BASE_NONE, NULL, 0,
      "Source name", HFILL}
    },
    {&hf_qnet6_qos_tcs_src_domain_off,
     {"Src_domain_off", "qnet6.qos.src_domain_off",
      FT_UINT16, BASE_DEC, NULL, 0,
      "Source domain name offset", HFILL}
    },
    {&hf_qnet6_qos_tcs_src_domain_generated,
     {"Src_domain", "qnet6.qos.src_domain",
      FT_STRING, BASE_NONE, NULL, 0,
      "Source domain name", HFILL}
    },
    {&hf_qnet6_qos_tcs_dst_name_off,
     {"Dst_name_off", "qnet6.qos.dst_name_off",
      FT_UINT16, BASE_DEC, NULL, 0,
      "Destination name offset", HFILL}
    },
    {&hf_qnet6_qos_tcs_dst_name_generated,
     {"Dst_name", "qnet6.qos.dst_name",
      FT_STRING, BASE_NONE, NULL, 0,
      "Destination name", HFILL}
    },
    {&hf_qnet6_qos_tcs_dst_domain_off,
     {"Dst_domain_off", "qnet6.qos.dst_domain_off",
      FT_UINT16, BASE_DEC, NULL, 0,
      "Destination domain name offset", HFILL}
    },
    {&hf_qnet6_qos_tcs_dst_domain_generated,
     {"Dst_domain", "qnet6.qos.dst_domain",
      FT_STRING, BASE_NONE, NULL, 0,
      "Destination domain name", HFILL}
    }
  };
  static hf_register_info hf_nr[] = {
    /
    {&hf_qnet6_nr_type,
     {"Type", "qnet6.nr.type",
      FT_UINT8, BASE_DEC, VALS(qnet6_nr_type_vals), 0,
      "Network Resolver Message Type", HFILL}
    },
    {&hf_qnet6_nr_remote_req_len,
     {"Req_len", "qnet6.nr.req_len",
      FT_UINT8, BASE_DEC, NULL, 0,
      "Network Resolver remote request length", HFILL}
    },
    {&hf_qnet6_nr_remote_req_id,
     {"Req_id", "qnet6.nr.req_id",
      FT_UINT16, BASE_HEX_DEC, NULL, 0,
      "Network Resolver remote request id", HFILL}
    },
    {&hf_qnet6_nr_remote_req_name,
     {"Req_name", "qnet6.nr.req_name",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      "Network Resolver remote request name", HFILL}
    },
    {&hf_qnet6_nr_remote_rep_spare,
     {"Rep_spare", "qnet6.nr.rep_spare",
      FT_UINT8, BASE_HEX, NULL, 0,
      "Network Resolver remote answer pad byte", HFILL}
    },
    {&hf_qnet6_nr_remote_rep_id,
     {"Rep_id", "qnet6.nr.rep_id",
      FT_UINT16, BASE_HEX, NULL, 0,
      "Network Resolver remote answer id", HFILL}
    },
    {&hf_qnet6_nr_remote_rep_nd,
     {"Rep_nd", "qnet6.nr.rep_nd",
      FT_UINT32, BASE_HEX, NULL, 0,
      "Network Resolver remote answer node id", HFILL}
    },
    {&hf_qnet6_nr_remote_rep_status,
     {"Rep_status", "qnet6.nr.rep_status",
      FT_UINT32, BASE_HEX, NULL, 0,
      "Network Resolver remote answer error status", HFILL}
    }
  };

  static hf_register_info hf_lr[] = {
    /
    {&hf_qnet6_lr_ver,
     {"Version", "qnet6.lr.ver",
      FT_UINT8, BASE_DEC, VALS(qnet6_lr_ver_vals), 0,
      "Lan Resolver Version", HFILL}
    },
    {&hf_qnet6_lr_type,
     {"Type", "qnet6.lr.type",
      FT_UINT8, BASE_HEX, VALS(qnet6_lr_type_vals), 0,
      "Lan Resolver Message Type", HFILL}
    },
    {&hf_qnet6_lr_total_len,
     {"Length", "qnet6.lr.length",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message total length(include header + payload)", HFILL}
    },
    {&hf_qnet6_lr_src,
     {"Source", "qnet6.lr.src",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message source node", HFILL}
    },

    {&hf_qnet6_lr_src_name_off,
     {"Offset", "qnet6.lr.src.name.off",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message source name offset", HFILL}
    },
    {&hf_qnet6_lr_src_name_len,
     {"Length", "qnet6.lr.src.name.len",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message source name length", HFILL}
    },
    {&hf_qnet6_lr_src_name_generated,
     {"Name", "qnet6.lr.src.name.name",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message source name", HFILL}
    },
    {&hf_qnet6_lr_src_domain_off,
     {"Offset", "qnet6.lr.src.domain.off",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message source domain name offset", HFILL}
    },
    {&hf_qnet6_lr_src_domain_len,
     {"Length", "qnet6.lr.src.domain.len",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message source domain name length", HFILL}
    },
    {&hf_qnet6_lr_src_domain_generated,
     {"Domain", "qnet6.lr.src.domain",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message source domain name", HFILL}
    },
    {&hf_qnet6_lr_src_addr_off,
     {"Offset", "qnet6.lr.src.addr.off",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message source address offset", HFILL}
    },
    {&hf_qnet6_lr_src_addr_len,
     {"Length", "qnet6.lr.src.addr.len",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message source address length", HFILL}
    },
    {&hf_qnet6_lr_src_addr_generated,
     {"Address", "qnet6.lr.src.addr",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message source address", HFILL}
    },
    {&hf_qnet6_lr_dst,
     {"Destination", "qnet6.lr.dst",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message destination node", HFILL}
    },
    {&hf_qnet6_lr_dst_name_off,
     {"Offset", "qnet6.lr.dst.name.off",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message destination name offset", HFILL}
    },
    {&hf_qnet6_lr_dst_name_len,
     {"Length", "qnet6.lr.dst.name.len",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message destination name length", HFILL}
    },
    {&hf_qnet6_lr_dst_name_generated,
     {"Name", "qnet6.lr.dst.name",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message destination name", HFILL}
    },
    {&hf_qnet6_lr_dst_domain_off,
     {"Offset", "qnet6.lr.dst.domain.off",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message destination domain name offset", HFILL}
    },
    {&hf_qnet6_lr_dst_domain_len,
     {"Length", "qnet6.lr.dst_domain_len",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message destination domain name length", HFILL}
    },
    {&hf_qnet6_lr_dst_domain_generated,
     {"Domain", "qnet6.lr.dst.domain",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message destination domain name", HFILL}
    },
    {&hf_qnet6_lr_dst_addr_off,
     {"Offset", "qnet6.lr.dst.addr.off",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message destination address offset", HFILL}
    },
    {&hf_qnet6_lr_dst_addr_len,
     {"Length", "qnet6.lr.dst.addr.len",
      FT_UINT32, BASE_DEC, NULL, 0,
      "LR Message destination address length", HFILL}
    },
    {&hf_qnet6_lr_dst_addr_generated,
     {"Address", "qnet6.lr.dst.addr",
      FT_STRING, BASE_NONE, NULL, 0,
      "LR Message destination address", HFILL}
    }

  };

  static hf_register_info hf_kif[] = {
    /
    {&hf_qnet6_kif_msgtype,
     {"Type", "qnet6.kif.type",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgtype_vals), QNET_KIF_MSGTYPE_MASK,
      "Kernel Interface Message Type", HFILL}
    },
    {&hf_qnet6_kif_size,
     {"Size", "qnet6.kif.size",
      FT_UINT16, BASE_HEX, NULL, 0,
      "Kernel Interface Message header size", HFILL}
    },
    /
    {&hf_qnet6_kif_version,
     {"Version", "qnet6.kif.version",
      FT_UINT32, BASE_HEX, NULL, 0,
      "Kernel Interface Message version", HFILL}
    },
    /
    {&hf_qnet6_kif_connect,
     {"Connect", "qnet6.kif.connect",
      FT_STRING, BASE_NONE, NULL, 0,
      "Connect Message", HFILL}
    },
    {&hf_qnet6_kif_msgsend,
     {"Msgsend", "qnet6.kif.msgsend",
      FT_STRING, BASE_NONE, NULL, 0,
      "Msgsend Message", HFILL}
    },
    {&hf_qnet6_kif_connect_server_pid,
     {"Server_pid", "qnet6.kif.connect.server_pid",
      FT_UINT32, BASE_DEC, NULL, 0,
      "Kernel Interface Message Server Pid", HFILL}
    },
    {&hf_qnet6_kif_connect_server_chid,
     {"Server_chid", "qnet6.kif.connect.server_chid",
      FT_UINT32, BASE_HEX_DEC, NULL, 0,
      "Kernel Interface Message Server channel id", HFILL}
    },
    {&hf_qnet6_kif_connect_client_id,
     {"Client_id", "qnet6.kif.connect.client_id",
      FT_UINT32, BASE_HEX_DEC, NULL, 0,
      "Kernel Interface Message client id", HFILL}
    },
    {&hf_qnet6_kif_connect_client_pid,
     {"Client_pid", "qnet6.kif.connect.client_pid",
      FT_UINT32, BASE_DEC, NULL, 0,
      "Kernel Interface Message Client Pid", HFILL}
    },
    /
    {&hf_qnet6_kif_connects_client_id,
     {"Client_id", "qnet6.kif.connect_success.client_id",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface Message client id", HFILL}
    },
    {&hf_qnet6_kif_connects_server_id,
     {"Server_id", "qnet6.kif.connect_success.server_id",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface Message Server id", HFILL}
    },
    {&hf_qnet6_kif_connects_scoid,
     {"Scoid", "qnet6.kif.connect_success.scoid",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface Message server connection id", HFILL}
    },
    {&hf_qnet6_kif_connects_nbytes,
     {"Nbytes", "qnet6.kif.connect_success.nbytes",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "Kernel Interface Message limit for msgsend", HFILL}
    },
    /
    {&hf_qnet6_kif_connectf_client_id,
     {"Client_id", "qnet6.kif.connect_fail.client_id",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface Connect Fail Message client id", HFILL}
    },
    {&hf_qnet6_kif_connectf_status,
     {"Status", "qnet6.kif.connect_fail.status",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface Connect Fail Message Status", HFILL}
    },
    /
    {&hf_qnet6_kif_connectd_client_id,
     {"Client_id", "qnet6.kif.connect_death.client_id",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface Connect Death Message client id", HFILL}
    },

    /
    {&hf_qnet6_kif_msgsend_server_id,
     {"Server_id", "qnet6.kif.msgsend.server_id",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface MsgSend Message Server id", HFILL}
    },
    {&hf_qnet6_kif_msgsend_client_handle,
     {"Client_handle", "qnet6.kif.msgsend.client_handle",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgSend Message client handle", HFILL}
    },
    /
    {&hf_qnet6_kif_msgsend_vinfo,
     {"Vinfo", "qnet6.kif.msgsend.vinfo",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      "Kernel Interface MsgSend Message virtual thread information", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_tid,
     {"Vtid", "qnet6.kif.msgsend.vtid_info.tid",
      FT_INT32, BASE_DEC, NULL, 0,
      "essage virtual thread information thread id", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_coid,
     {"Coid", "qnet6.kif.msgsend.vtid_info.coid",
      FT_INT32, BASE_DEC, NULL, 0,
      "Kernel Interface MsgSend Message virtual thread connection id", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_priority,
     {"Priority", "qnet6.kif.msgsend.vtid_info.priority",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgSend Message virtual thread priority", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_srcmsglen,
     {"Srcmsglen", "qnet6.kif.msgsend.vtid_info.srcmsglen",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgSend Message virtual thread source message length", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_keydata,
     {"Keydata", "qnet6.kif.msgsend.vtid_info.keydata",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgSend Message virtual thread keydata", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_srcnd,
     {"Srcnd", "qnet6.kif.msgsend.vtid_info.srcnd",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgSend Message virtual thread source node id", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_dstmsglen,
     {"Dstmsglen", "qnet6.kif.msgsend.vtid_info.dstmsglen",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgSend Message virtual thread destination message length", HFILL}
    },
    {&hf_qnet6_kif_vtid_info_zero,
     {"Zero", "qnet6.kif.msgsend.vtid_info.zero",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgSend Message virtual thread reserved part", HFILL}
    },
    {&hf_qnet6_kif_msgsend_nbytes,
     {"Nbytes", "qnet6.kif.msgsend.nbytes",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "Kernel Interface MsgSend Message limit for msgsend", HFILL}
    },
    {&hf_qnet6_kif_msgread_msgread_handle,
     {"Msgread_handle", "qnet6.kif.msgread.msgread_handle",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgRead Message handle", HFILL}
    },
    {&hf_qnet6_kif_msgread_client_handle,
     {"Client_handle", "qnet6.kif.msgread.client_handle",
      FT_INT32, BASE_DEC, NULL, 0,
      "MsgRead Message client handle", HFILL}
    },
    {&hf_qnet6_kif_msgread_offset,
     {"Offset", "qnet6.kif.msgread.offset",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "MsgRead Message limit for msgread", HFILL}
    },
    {&hf_qnet6_kif_msgread_nbytes,
     {"Nbytes", "qnet6.kif.msgread.nbytes",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "MsgRead Message limit for msgread", HFILL}
    },
    /
    {&hf_qnet6_kif_msgwrite_status,
     {"Status", "qnet6.kif.msgwrite.status",
      FT_INT32, BASE_DEC, NULL, 0,
      "Msgwrite Message client handle", HFILL}
    },
    {&hf_qnet6_kif_msgwrite_handle,
     {"Handle", "qnet6.kif.msgwrite.handle",
      FT_INT32, BASE_DEC, NULL, 0,
      "Msgwrite Message client handle", HFILL}
    },
    {&hf_qnet6_kif_msgwrite_offset,
     {"Offset", "qnet6.kif.msgwrite.offset",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "Msgwrite Message limit for msgwrite", HFILL}
    },
    {&hf_qnet6_kif_msgwrite_nbytes,
     {"Nbytes", "qnet6.kif.msgwrite.nbytes",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "Msgwrite Message limit for msgwrite", HFILL}
    },
    {&hf_qnet6_kif_msgwrite_data,
     {"Data", "qnet6.kif.msgwrite.data",
      FT_BYTES, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    /
    {&hf_qnet6_kif_unblock_server_id,
     {"Server_id", "qnet6.kif.unblock.server_id",
      FT_INT32, BASE_DEC, NULL, 0,
      "Unblock Message Server id", HFILL}
    },
    {&hf_qnet6_kif_unblock_client_handle,
     {"Client_handle", "qnet6.kif.unblock.client_handle",
      FT_INT32, BASE_DEC, NULL, 0,
      "Unblock Message client handle", HFILL}
    },
    {&hf_qnet6_kif_unblock_tid,
     {"Tid", "qnet6.kif.unblock.tid",
      FT_INT32, BASE_DEC, NULL, 0,
      "thread information thread id", HFILL}
    },
    /
    {&hf_qnet6_kif_event_client_handle,
     {"Client_handle", "qnet6.kif.event.client_handle",
      FT_INT32, BASE_DEC, NULL, 0,
      "Event Message client handle", HFILL}
    },
    /
    {&hf_qnet6_kif_event_event,
     {"Sigevent", "qnet6.kif.event.event",
      FT_NONE, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_event_notify,
     {"Sigevent_notify", "qnet6.kif.event.sigevent_notify",
      FT_INT32, BASE_DEC, NULL, 0,
      "Event Message sigevent notify", HFILL}
    },
    {&hf_qnet6_kif_event_union1,
     {"Sigevent_union1", "qnet6.kif.event.sigevent_union1",
      FT_INT32, BASE_DEC, NULL, 0,
      "Event Message sigevent union1", HFILL}
    },
    {&hf_qnet6_kif_event_value,
     {"Sigevent_sigvalue", "qnet6.kif.event.sigevent_sigvalue",
      FT_INT32, BASE_DEC, NULL, 0,
      "Event Message sigevent sigvalue", HFILL}
    },
    {&hf_qnet6_kif_event_union2,
     {"Sigevent_union2", "qnet6.kif.event.sigevent_union2",
      FT_INT32, BASE_DEC, NULL, 0,
      "Event Message sigevent union2", HFILL}
    },
    /
    /
    {&hf_qnet6_kif_pulse_pulse,
     {"Pulse", "qnet6.kif.pulse",
      FT_STRING, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_pulse_pulse_type,
     {"Type", "qnet6.kif.pulse.pulse.type",
      FT_UINT16, BASE_HEX_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_pulse_pulse_subtype,
     {"Subtype", "qnet6.kif.pulse.pulse.subtype",
      FT_UINT16, BASE_HEX_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_pulse_pulse_code,
     {"Code", "qnet6.kif.pulse.pulse.code",
      FT_INT8, BASE_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_pulse_pulse_reserved,
     {"Reserved", "qnet6.kif.pulse.pulse.reserved",
      FT_UINT24, BASE_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_pulse_pulse_value,
     {"Value", "qnet6.kif.pulse.pulse.value",
      FT_UINT32, BASE_HEX_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_pulse_pulse_scoid,
     {"Scoid", "qnet6.kif.pulse.pulse.scoid",
      FT_INT32, BASE_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_pulse_priority,
     {"Priority", "qnet6.kif.pulse.priority",
      FT_INT32, BASE_DEC, NULL, 0,
      NULL, HFILL}
    },
    /
    {&hf_qnet6_kif_signal_client_handle,
     {"Client_handle", "qnet6.kif.signal.client_handle",
      FT_INT32, BASE_DEC, NULL, 0,
      "Signal Message client handle", HFILL}
    },
    {&hf_qnet6_kif_signal_pid,
     {"Pid", "qnet6.kif.signal.pid",
      FT_INT32, BASE_DEC, NULL, 0,
      "Signal Message from this pid", HFILL}
    },
    {&hf_qnet6_kif_signal_tid,
     {"Tid", "qnet6.kif.signal.tid",
      FT_INT32, BASE_DEC, NULL, 0,
      "Signal Message from this tid", HFILL}
    },
    {&hf_qnet6_kif_signal_signo,
     {"Signo", "qnet6.kif.signal.signo",
      FT_INT32, BASE_DEC, NULL, 0,
      "Signal number delivered to remote", HFILL}
    },
    {&hf_qnet6_kif_signal_code,
     {"Code", "qnet6.kif.signal.code",
      FT_INT32, BASE_DEC, NULL, 0,
      "Signal code delivered to remote", HFILL}
    },
    {&hf_qnet6_kif_signal_value,
     {"Value", "qnet6.kif.signal.value",
      FT_INT32, BASE_DEC, NULL, 0,
      "Signal value delivered to remote", HFILL}
    },
    /
    {&hf_qnet6_kif_disconnect_server_id,
     {"Server_id", "qnet6.kif.disconnect.server_id",
      FT_INT32, BASE_DEC, NULL, 0,
      "disconnect message server id from connect success message", HFILL}
    },
    /
    {&hf_qnet6_kif_msg,
     {"Message", "qnet6.kif.msgsend.msg",
      FT_STRING, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_type,
     {"Type", "qnet6.kif.msgsend.msg.type",
      FT_UINT16, BASE_HEX|BASE_EXT_STRING, &qnet6_kif_msgsend_msgtype_vals_ext, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_subtype,
     {"Subtype", "qnet6.kif.msgsend.msg.connect.subtype",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgsend_msg_connect_subtype_vals), 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_filetype,
     {"File_type", "qnet6.kif.msgsend.msg.connect.file_type",
      FT_UINT32, BASE_HEX, VALS(qnet6_kif_msgsend_msg_connect_filetype_vals), 0,
      "file type", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_replymax,
     {"Reply_max", "qnet6.kif.msgsend.msg.connect.reply_max",
      FT_UINT16, BASE_HEX_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_entrymax,
     {"Entry_max", "qnet6.kif.msgsend.msg.connect.entry_max",
      FT_UINT16, BASE_HEX_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_key,
     {"Key", "qnet6.kif.msgsend.msg.connect.key",
      FT_UINT32, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_handle,
     {"Handle", "qnet6.kif.msgsend.msg.connect.handle",
      FT_UINT32, BASE_HEX_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag,
     {"Ioflag", "qnet6.kif.msgsend.msg.connect.ioflag",
      FT_UINT32, BASE_OCT, NULL, 0,
      "file io flag", HFILL}
    },
    /

    {&hf_qnet6_kif_msg_connect_ioflag_access,
     {"access", "qnet6.kif.msgsend.msg.connect.ioflag.access",
      FT_UINT32, BASE_DEC, VALS(qnet6_kif_msgsend_msg_connect_ioflag_vals), 03,
      "access mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_append,
     {"append", "qnet6.kif.msgsend.msg.connect.ioflag.append",
      FT_BOOLEAN, 32, NULL, 010,
      "append mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_dsync,
     {"dsync", "qnet6.kif.msgsend.msg.connect.ioflag.dsync",
      FT_BOOLEAN, 32, NULL, 020,
      "data sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_sync,
     {"sync", "qnet6.kif.msgsend.msg.connect.ioflag.sync",
      FT_BOOLEAN, 32, NULL, 040,
      "file sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_rsync,
     {"rsync", "qnet6.kif.msgsend.msg.connect.ioflag.rsync",
      FT_BOOLEAN, 32, NULL, 0100,
      "alias for data sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_nonblock,
     {"nonblock", "qnet6.kif.msgsend.msg.connect.ioflag.nonblock",
      FT_BOOLEAN, 32, NULL, 0200,
      "alias for data sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_creat,
     {"creat", "qnet6.kif.msgsend.msg.connect.ioflag.creat",
      FT_BOOLEAN, 32, NULL, 0400,
      "creat mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_truncate,
     {"truncate", "qnet6.kif.msgsend.msg.connect.ioflag.truncate",
      FT_BOOLEAN, 32, NULL, 01000,
      "truncate mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_exclusive,
     {"exclusive", "qnet6.kif.msgsend.msg.connect.ioflag.exclusive",
      FT_BOOLEAN, 32, NULL, 02000,
      "exclusive mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_noctrltty,
     {"noctrltty", "qnet6.kif.msgsend.msg.connect.ioflag.noctrltty",
      FT_BOOLEAN, 32, NULL, 04000,
      "noctrltty mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_closexec,
     {"closexec", "qnet6.kif.msgsend.msg.connect.ioflag.closexec",
      FT_BOOLEAN, 32, NULL, 010000,
      "closexec mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_realids,
     {"realids", "qnet6.kif.msgsend.msg.connect.ioflag.realids",
      FT_BOOLEAN, 32, NULL, 020000,
      "realids mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_largefile,
     {"largefile", "qnet6.kif.msgsend.msg.connect.ioflag.largefile",
      FT_BOOLEAN, 32, NULL, 0100000,
      "largefile mode", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_ioflag_async,
     {"async", "qnet6.kif.msgsend.msg.connect.ioflag.async",
      FT_BOOLEAN, 32, NULL, 0200000,
      "async mode", HFILL}
    },

    {&hf_qnet6_kif_msg_connect_mode,
     {"Mode", "qnet6.kif.msgsend.msg.connect.mode",
      FT_UINT32, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_other_exe,
     {"Oexec", "qnet6.kif.msgsend.msg.connect.mode.other.exec",
      FT_BOOLEAN, 32, NULL, 01,
      "others exec permission", HFILL}
    },

    {&hf_qnet6_kif_msg_connect_mode_other_write,
     {"Owrite", "qnet6.kif.msgsend.msg.connect.mode.other.write",
      FT_BOOLEAN, 32, NULL, 02,
      "others write permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_other_read,
     {"Oread", "qnet6.kif.msgsend.msg.connect.mode.other.read",
      FT_BOOLEAN, 32, NULL, 04,
      "others read permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_group_exe,
     {"Gexec", "qnet6.kif.msgsend.msg.connect.mode.group.exec",
      FT_BOOLEAN, 32, NULL, 010,
      "group exec permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_group_write,
     {"Gwrite", "qnet6.kif.msgsend.msg.connect.mode.group.write",
      FT_BOOLEAN, 32, NULL, 020,
      "group write permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_group_read,
     {"Gread", "qnet6.kif.msgsend.msg.connect.mode.group.read",
      FT_BOOLEAN, 32, NULL, 040,
      "group read permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_owner_exe,
     {"Uexec", "qnet6.kif.msgsend.msg.connect.mode.owner.exec",
      FT_BOOLEAN, 32, NULL, 0100,
      "owner exec permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_owner_write,
     {"Uwrite", "qnet6.kif.msgsend.msg.connect.mode.owner.write",
      FT_BOOLEAN, 32, NULL, 0200,
      "owner write permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_owner_read,
     {"Uread", "qnet6.kif.msgsend.msg.connect.mode.owner.read",
      FT_BOOLEAN, 32, NULL, 0400,
      "owner read permission", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_sticky,
     {"sticky", "qnet6.kif.msgsend.msg.connect.mode.sticky",
      FT_BOOLEAN, 32, NULL, 01000,
      "sticky bit", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_setgid,
     {"setgid", "qnet6.kif.msgsend.msg.connect.mode.setgid",
      FT_BOOLEAN, 32, NULL, 02000,
      "set gid when execution", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_mode_setuid,
     {"setuid", "qnet6.kif.msgsend.msg.connect.mode.setuid",
      FT_BOOLEAN, 32, NULL, 04000,
      "set uid when execution", HFILL}
    },

    {&hf_qnet6_kif_msg_connect_mode_format,
     {"format", "qnet6.kif.msgsend.msg.connect.mode.format",
      FT_UINT32, BASE_HEX, VALS(qnet6_kif_msgsend_msg_connect_mode_vals), 0xf000,
      "file format", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_sflag,
     {"Sflag", "qnet6.kif.msgsend.msg.connect.sflag",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgsend_msg_connect_sflag_vals), 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_access,
     {"Access", "qnet6.kif.msgsend.msg.connect.access",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgsend_msg_connect_access_vals), 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_zero,
     {"Zero", "qnet6.kif.msgsend.msg.connect.zero",
      FT_UINT16, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_pathlen,
     {"Path_len", "qnet6.kif.msgsend.msg.connect.path_len",
      FT_UINT16, BASE_HEX, NULL, 0,
      "path length", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_eflag,
     {"Eflag", "qnet6.kif.msgsend.msg.connect.eflag",
      FT_UINT8, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_eflag_dir,
     {"dir", "qnet6.kif.msgsend.msg.connect.eflag.dir",
      FT_BOOLEAN, 8, NULL, 1,
      "path referenced a directory", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_eflag_dot,
     {"dot", "qnet6.kif.msgsend.msg.connect.eflag.dot",
      FT_BOOLEAN, 8, NULL, 2,
      "Last component was . or ..", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_eflag_dotdot,
     {"dotdot", "qnet6.kif.msgsend.msg.connect.eflag.dotdot",
      FT_BOOLEAN, 8, NULL, 4,
      "Last component was ..", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_extratype,
     {"Extra_type", "qnet6.kif.msgsend.msg.connect.extra_type",
      FT_UINT8, BASE_HEX, VALS(qnet6_kif_msgsend_msg_connect_extratype_vals), 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_extralen,
     {"Extra_len", "qnet6.kif.msgsend.msg.connect.extra_len",
      FT_UINT16, BASE_HEX_DEC, NULL, 0,
      "extra data length", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_path,
     {"Path", "qnet6.kif.msgsend.msg.connect.path",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      "path name", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_pad_data,
     {"Pad data", "qnet6.kif.msgsend.msg.pad_data",
      FT_BYTES, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_extra_link_ocb,
     {"Ocb", "qnet6.kif.msgsend.msg.connect.extra.link.ocb",
      FT_UINT32, BASE_HEX, NULL, 0,
      "Ocb pointer value", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_extra_symlink_path,
     {"Path", "qnet6.kif.msgsend.msg.connect.extra.symlink.path",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      "Symlink new path name", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_extra_rename_path,
     {"Path", "qnet6.kif.msgsend.msg.connect.extra.rename.path",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      "Rename old path name", HFILL}
    },
    {&hf_qnet6_kif_msg_connect_extra_mount,
     {"Mount", "qnet6.kif.msgsend.msg.connect.extra.mount",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_connect_extra_data,
     {"Extra Data", "qnet6.kif.msgsend.msg.connect.extra.data",
      FT_BYTES, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },

    /
    {&hf_qnet6_kif_msg_io_combine_len,
     {"Combine_len", "qnet6.kif.msgsend.msg.combine_len",
      FT_UINT16, BASE_HEX, NULL, 0,
      "combine length", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_devctl_dcmd,
     {"Dcmd", "qnet6.kif.msgsend.msg.dcmd",
      FT_UINT32, BASE_HEX, NULL, 0,
      "Devctl Command and Direction", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_devctl_dcmd_ccmd,
     {"Ccmd", "qnet6.kif.msgsend.msg.dcmd.ccmd",
      FT_UINT32, BASE_HEX_DEC|BASE_EXT_STRING, &qnet6_kif_msg_devctl_cmd_class_vals_ext, 0xffff,
      "Devctl Class+Command", HFILL}
    },
    {&hf_qnet6_kif_msg_devctl_dcmd_cmd,
     {"Cmd", "qnet6.kif.msgsend.msg.dcmd.cmd",
      FT_UINT32, BASE_HEX_DEC, NULL, 0xff,
      "Devctl Command", HFILL}
    },
    {&hf_qnet6_kif_msg_devctl_dcmd_class,
     {"Class", "qnet6.kif.msgsend.msg.dcmd.class",
      FT_UINT32, BASE_HEX|BASE_EXT_STRING, &qnet6_kif_msgsend_msg_devctl_cmd_class_vals_ext, 0xff00,
      "Devctl Command", HFILL}
    },
    {&hf_qnet6_kif_msg_devctl_dcmd_size,
     {"Size", "qnet6.kif.msgsend.msg.dcmd.size",
      FT_UINT32, BASE_HEX, NULL, 0x3fff0000,
      "Devctl Command", HFILL}
    },
    {&hf_qnet6_kif_msg_devctl_dcmd_from,
     {"From", "qnet6.kif.msgsend.msg.dcmd.from",
      FT_UINT32, BASE_HEX, NULL, 0x40000000,
      "Devctl Direction has from", HFILL}
    },
    {&hf_qnet6_kif_msg_devctl_dcmd_to,
     {"To", "qnet6.kif.msgsend.msg.dcmd.to",
      FT_UINT32, BASE_HEX, NULL, 0x80000000,
      "Devctl Direction has to", HFILL}
    },
    {&hf_qnet6_kif_msg_devctl_nbytes,
     {"Nbytes", "qnet6.kif.msgsend.msg.nbytes",
      FT_INT32, BASE_DEC, NULL, 0,
      "payload length", HFILL}
    },
    {&hf_qnet6_kif_msg_devctl_zero,
     {"Zero", "qnet6.kif.msgsend.msg.zero",
      FT_INT32, BASE_DEC, NULL, 0,
      "pad", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_read_nbytes,
     {"Nbytes", "qnet6.kif.msgsend.msg.read.nbytes",
      FT_INT32, BASE_DEC, NULL, 0,
      "read buffer size", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_xtypes,
     {"Xtypes", "qnet6.kif.msgsend.msg.read.xtypes",
      FT_UINT32, BASE_HEX, NULL, 0,
      "Extended types for io message", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_xtypes_0_7,
     {"Xtype", "qnet6.kif.msgsend.msg.read.xtypes0-7",
      FT_UINT32, BASE_HEX, VALS(qnet6_kif_msgsend_msg_io_read_xtypes_vals), 0xff,
      "Extended types 0-7 bits", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_xtypes_8,
     {"DirExtraHint", "qnet6.kif.msgsend.msg.read.xtypes8",
      FT_UINT32, BASE_HEX, NULL, 0x100,
      "_IO_XFLAG_DIR_EXTRA_HINT", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_xtypes_14,
     {"Nonblock", "qnet6.kif.msgsend.msg.read.xtypes0-7",
      FT_UINT32, BASE_HEX, NULL, 0x4000,
      "_IO_XFLAG_NONBLOCK", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_xtypes_15,
     {"Block", "qnet6.kif.msgsend.msg.read.xtypes0-7",
      FT_UINT32, BASE_HEX, NULL, 0x8000,
      "_IO_XFLAG_BLOCK", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_xoffset,
     {"Xoffset", "qnet6.kif.msgsend.msg.read.xoffset",
      FT_INT64, BASE_DEC, NULL, 0,
      "Extended offset in io message", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_cond_min,
     {"Min", "qnet6.kif.msgsend.msg.read.readcond.min",
      FT_INT32, BASE_DEC, NULL, 0,
      "Extended attribute minimum characters for readcond", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_cond_time,
     {"Time", "qnet6.kif.msgsend.msg.read.readcond.time",
      FT_INT32, BASE_DEC, NULL, 0,
      "Extended attribute for readcond in 1/10 second", HFILL}
    },
    {&hf_qnet6_kif_msg_io_read_cond_timeout,
     {"Timeout", "qnet6.kif.msgsend.msg.read.readcond.timeout",
      FT_INT32, BASE_DEC, NULL, 0,
      "Extended attribute timeout for readcond in 1/10 second", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_write_data,
     {"Write Data", "qnet6.kif.msgsend.msg.write.data",
      FT_BYTES, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_io_write_nbytes,
     {"Nbytes", "qnet6.kif.msgsend.msg.write.nbytes",
      FT_INT32, BASE_DEC, NULL, 0,
      "write buffer size", HFILL}
    },
    {&hf_qnet6_kif_msg_io_write_xtypes,
     {"Xtypes", "qnet6.kif.msgsend.msg.write.xtypes",
      FT_UINT32, BASE_HEX, NULL, 0,
      "Extended types for io message", HFILL}
    },
    {&hf_qnet6_kif_msg_io_write_xtypes_0_7,
     {"Xtype", "qnet6.kif.msgsend.msg.write.xtypes0-7",
      FT_UINT32, BASE_HEX, VALS(qnet6_kif_msgsend_msg_io_read_xtypes_vals), 0xff,
      "Extended types 0-7 bits", HFILL}
    },
    {&hf_qnet6_kif_msg_io_write_xtypes_8,
     {"DirExtraHint", "qnet6.kif.msgsend.msg.write.xtypes8",
      FT_UINT32, BASE_HEX, NULL, 0x100,
      "_IO_XFLAG_DIR_EXTRA_HINT", HFILL}
    },
    {&hf_qnet6_kif_msg_io_write_xtypes_14,
     {"Nonblock", "qnet6.kif.msgsend.msg.write.xtypes0-7",
      FT_UINT32, BASE_HEX, NULL, 0x4000,
      "_IO_XFLAG_NONBLOCK", HFILL}
    },
    {&hf_qnet6_kif_msg_io_write_xtypes_15,
     {"Block", "qnet6.kif.msgsend.msg.write.xtypes0-7",
      FT_UINT32, BASE_HEX, NULL, 0x8000,
      "_IO_XFLAG_BLOCK", HFILL}
    },
    {&hf_qnet6_kif_msg_io_write_xoffset,
     {"Xoffset", "qnet6.kif.msgsend.msg.write.xoffset",
      FT_INT64, BASE_DEC, NULL, 0,
      "Extended offset in io message", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_seek_whence,
     {"Whence", "qnet6.kif.msgsend.msg.lseek.whence",
      FT_INT16, BASE_DEC, VALS(qnet6_kif_msgsend_msg_io_seek_whence_vals), 0,
      "whence in file", HFILL}
    },
    {&hf_qnet6_kif_msg_seek_offset,
     {"Offset", "qnet6.kif.msgsend.msg.lseek.offset",
      FT_UINT64, BASE_DEC_HEX, NULL, 0,
      "offset according to whence in file", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_pathconf_name,
     {"name", "qnet6.kif.msgsend.msg.pathconf.name",
      FT_INT16, BASE_DEC|BASE_EXT_STRING, &qnet6_kif_msgsend_msg_io_pathconf_name_vals_ext, 0,
      "pathconf(name)", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_chmod,
     {"mode", "qnet6.kif.msgsend.msg.chmod.mode",
      FT_UINT32, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_other_exe,
     {"Oexec", "qnet6.kif.msgsend.msg.chmod.other.exec",
      FT_BOOLEAN, 32, NULL, 01,
      "others exec permission", HFILL}
    },

    {&hf_qnet6_kif_msg_io_chmod_other_write,
     {"Owrite", "qnet6.kif.msgsend.msg.chmod.other.write",
      FT_BOOLEAN, 32, NULL, 02,
      "others write permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_other_read,
     {"Oread", "qnet6.kif.msgsend.msg.chmod.other.read",
      FT_BOOLEAN, 32, NULL, 04,
      "others read permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_group_exe,
     {"Gexec", "qnet6.kif.msgsend.msg.chmod.group.exec",
      FT_BOOLEAN, 32, NULL, 010,
      "group exec permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_group_write,
     {"Gwrite", "qnet6.kif.msgsend.msg.chmod.group.write",
      FT_BOOLEAN, 32, NULL, 020,
      "group write permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_group_read,
     {"Gread", "qnet6.kif.msgsend.msg.chmod.group.read",
      FT_BOOLEAN, 32, NULL, 040,
      "group read permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_owner_exe,
     {"Uexec", "qnet6.kif.msgsend.msg.chmod.owner.exec",
      FT_BOOLEAN, 32, NULL, 0100,
      "owner exec permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_owner_write,
     {"Uwrite", "qnet6.kif.msgsend.msg.chmod.owner.write",
      FT_BOOLEAN, 32, NULL, 0200,
      "owner write permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_owner_read,
     {"Uread", "qnet6.kif.msgsend.msg.chmod.owner.read",
      FT_BOOLEAN, 32, NULL, 0400,
      "owner read permission", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_sticky,
     {"sticky", "qnet6.kif.msgsend.msg.chmod.sticky",
      FT_BOOLEAN, 32, NULL, 01000,
      "sticky bit", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_setgid,
     {"setgid", "qnet6.kif.msgsend.msg.chmod.setgid",
      FT_BOOLEAN, 32, NULL, 02000,
      "set gid when execution", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chmod_setuid,
     {"setuid", "qnet6.kif.msgsend.msg.chmod.setuid",
      FT_BOOLEAN, 32, NULL, 04000,
      "set uid when execution", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_chown_gid,
     {"gid", "qnet6.kif.msgsend.msg.chown.gid",
      FT_UINT32, BASE_HEX, NULL, 0,
      "chown gid", HFILL}
    },
    {&hf_qnet6_kif_msg_io_chown_uid,
     {"uid", "qnet6.kif.msgsend.msg.chown.uid",
      FT_UINT32, BASE_HEX, NULL, 0,
      "chown uid", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_sync,
     {"sync", "qnet6.kif.msgsend.msg.sync",
      FT_UINT32, BASE_HEX, NULL, 0,
      "io sync command", HFILL}
    },
    {&hf_qnet6_kif_msg_syncflag_dsync,
     {"dsync", "qnet6.kif.msgsend.msg.sync.flag.dsync",
      FT_BOOLEAN, 32, NULL, 020,
      "data sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_syncflag_sync,
     {"sync", "qnet6.kif.msgsend.msg.sync.flag.sync",
      FT_BOOLEAN, 32, NULL, 040,
      "file sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_syncflag_rsync,
     {"rsync", "qnet6.kif.msgsend.msg.sync.flag.rsync",
      FT_BOOLEAN, 32, NULL, 0100,
      "alias for data sync mode", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_utime_curflag,
     {"curflag", "qnet6.kif.msgsend.msg.utime.curflag",
      FT_BOOLEAN, 32, TFS(&tfs_set_notset), 0,
      "whether use current time", HFILL}
    },
    {&hf_qnet6_kif_msg_io_utime_actime,
     {"actime", "qnet6.kif.msgsend.msg.utime.actime",
      FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0,
      "access time in seconds since the Epoch", HFILL}
    },
    {&hf_qnet6_kif_msg_io_utime_modtime,
     {"modtime", "qnet6.kif.msgsend.msg.utime.modtime",
      FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0,
      "modification time in seconds since the Epoch", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_fdinfo_flags,
     {"flags", "qnet6.kif.msgsend.msg.fdinfo.flags",
      FT_BOOLEAN, 32, TFS(&tfs_set_notset), 0,
      "_FDINFO_FLAG_LOCALPATH", HFILL}
    },
    {&hf_qnet6_kif_msg_io_fdinfo_path_len,
     {"pathlen", "qnet6.kif.msgsend.msg.fdinfo.pathlen",
      FT_UINT32, BASE_HEX, NULL, 0,
      "returned path buffer's length", HFILL}
    },
    {&hf_qnet6_kif_msg_io_fdinfo_reserved,
     {"reserved", "qnet6.kif.msgsend.msg.fdinfo.reserved",
      FT_UINT32, BASE_HEX, NULL, 0,
      "reserved fields", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_lock_subtype,
     {"subtype", "qnet6.kif.msgsend.msg.lock.subtype",
      FT_UINT32, BASE_HEX, NULL, 0,
      "io lock subytpe", HFILL}
    },
    {&hf_qnet6_kif_msg_io_lock_nbytes,
     {"nbytes", "qnet6.kif.msgsend.msg.lock.nbytes",
      FT_UINT32, BASE_HEX, NULL, 0,
      "io lock nbytes", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_space_subtype,
     {"subtype", "qnet6.kif.msgsend.msg.space.subtype",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgsend_msg_io_space_subtype_vals), 0,
      "io space subytpe", HFILL}
    },
    {&hf_qnet6_kif_msg_io_space_whence,
     {"whence", "qnet6.kif.msgsend.msg.space.whence",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgsend_msg_io_seek_whence_vals), 0,
      "io space whence", HFILL}
    },
    {&hf_qnet6_kif_msg_io_space_start,
     {"start", "qnet6.kif.msgsend.msg.space.start",
      FT_UINT64, BASE_HEX, NULL, 0,
      "io space start", HFILL}
    },
    {&hf_qnet6_kif_msg_io_space_len,
     {"len", "qnet6.kif.msgsend.msg.space.len",
      FT_UINT64, BASE_HEX, NULL, 0,
      "io space len", HFILL}
    },
    {&hf_qnet6_kif_msgsend_extra,
     {"Extra", "qnet6.kif.msgsend.extra",
      FT_STRING, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },

    /
    {&hf_qnet6_kif_msg_msginfo_nd,
     {"Node", "qnet6.kif.msgsend.msg_info.nd",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "node id", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_srcnd,
     {"Srcnode", "qnet6.kif.msgsend.msg_info.srcnd",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "source node id", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_pid,
     {"Pid", "qnet6.kif.msgsend.msg_info.pid",
      FT_INT32, BASE_DEC, NULL, 0,
      "process id", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_tid,
     {"Tid", "qnet6.kif.msgsend.msg_info.tid",
      FT_INT32, BASE_DEC, NULL, 0,
      "thread id", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_chid,
     {"Chid", "qnet6.kif.msgsend.msg_info.chid",
      FT_INT32, BASE_DEC, NULL, 0,
      "channel id", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_scoid,
     {"Scoid", "qnet6.kif.msgsend.msg_info.scoid",
      FT_INT32, BASE_DEC, NULL, 0,
      "server connection id", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_coid,
     {"Coid", "qnet6.kif.msgsend.msg_info.coid",
      FT_INT32, BASE_DEC, NULL, 0,
      "connection id", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_msglen,
     {"Msglen", "qnet6.kif.msgsend.msg_info.msglen",
      FT_INT32, BASE_DEC, NULL, 0,
      "message length", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_srcmsglen,
     {"Srcmsglen", "qnet6.kif.msgsend.msg_info.srcmsglen",
      FT_INT32, BASE_DEC, NULL, 0,
      "source message length", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_dstmsglen,
     {"Dstmsglen", "qnet6.kif.msgsend.msg_info.dstmsglen",
      FT_INT32, BASE_DEC, NULL, 0,
      "destination message length", HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_priority,
     {"Priority", "qnet6.kif.msgsend.msg_info.priority",
      FT_INT16, BASE_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_flags,
     {"Flags", "qnet6.kif.msgsend.msg_info.flags",
      FT_INT16, BASE_DEC, NULL, 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_msginfo_reserved,
     {"Reserved", "qnet6.kif.msgsend.msg_info.reserved",
      FT_UINT32, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    /

    {&hf_qnet6_kif_msg_openfd_ioflag,
     {"Ioflag", "qnet6.kif.msgsend.msg.openfd.ioflag",
      FT_UINT32, BASE_OCT, NULL, 0,
      "file io flag", HFILL}
    },
    /

    {&hf_qnet6_kif_msg_openfd_ioflag_access,
     {"access", "qnet6.kif.msgsend.msg.openfd.ioflag.access",
      FT_UINT32, BASE_DEC, VALS(qnet6_kif_msgsend_msg_connect_ioflag_vals), 03,
      "access mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_append,
     {"append", "qnet6.kif.msgsend.msg.openfd.ioflag.append",
      FT_BOOLEAN, 32, NULL, 010,
      "append mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_dsync,
     {"dsync", "qnet6.kif.msgsend.msg.openfd.ioflag.dsync",
      FT_BOOLEAN, 32, NULL, 020,
      "data sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_sync,
     {"sync", "qnet6.kif.msgsend.msg.openfd.ioflag.sync",
      FT_BOOLEAN, 32, NULL, 040,
      "file sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_rsync,
     {"rsync", "qnet6.kif.msgsend.msg.openfd.ioflag.rsync",
      FT_BOOLEAN, 32, NULL, 0100,
      "alias for data sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_nonblock,
     {"nonblock", "qnet6.kif.msgsend.msg.openfd.ioflag.nonblock",
      FT_BOOLEAN, 32, NULL, 0200,
      "alias for data sync mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_creat,
     {"creat", "qnet6.kif.msgsend.msg.openfd.ioflag.creat",
      FT_BOOLEAN, 32, NULL, 0400,
      "creat mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_truncate,
     {"truncate", "qnet6.kif.msgsend.msg.openfd.ioflag.truncate",
      FT_BOOLEAN, 32, NULL, 01000,
      "truncate mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_exclusive,
     {"exclusive", "qnet6.kif.msgsend.msg.openfd.ioflag.exclusive",
      FT_BOOLEAN, 32, NULL, 02000,
      "exclusive mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_noctrltty,
     {"noctrltty", "qnet6.kif.msgsend.msg.openfd.ioflag.noctrltty",
      FT_BOOLEAN, 32, NULL, 04000,
      "noctrltty mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_closexec,
     {"closexec", "qnet6.kif.msgsend.msg.openfd.ioflag.closexec",
      FT_BOOLEAN, 32, NULL, 010000,
      "closexec mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_realids,
     {"realids", "qnet6.kif.msgsend.msg.openfd.ioflag.realids",
      FT_BOOLEAN, 32, NULL, 020000,
      "realids mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_largefile,
     {"largefile", "qnet6.kif.msgsend.msg.openfd.ioflag.largefile",
      FT_BOOLEAN, 32, NULL, 0100000,
      "largefile mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_ioflag_async,
     {"async", "qnet6.kif.msgsend.msg.openfd.ioflag.async",
      FT_BOOLEAN, 32, NULL, 0200000,
      "async mode", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_sflag,
     {"Sflag", "qnet6.kif.msgsend.msg.openfd.sflag",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgsend_msg_connect_sflag_vals), 0,
      NULL, HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_xtype,
     {"Xtype", "qnet6.kif.msgsend.msg.openfd.xtype",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_msgsend_msg_openfd_xtypes_vals), 0,
      "openfd xtype", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_reserved,
     {"Reserved", "qnet6.kif.msgsend.msg.openfd.reserved",
      FT_UINT32, BASE_HEX, NULL, 0,
      "openfd reserved fields", HFILL}
    },
    {&hf_qnet6_kif_msg_openfd_key,
     {"Key", "qnet6.kif.msgsend.msg.openfd.key",
      FT_UINT32, BASE_HEX, NULL, 0,
      "openfd key", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_mmap_prot,
     {"Prot", "qnet6.kif.msgsend.msg.mmap.prot",
      FT_UINT32, BASE_HEX, NULL, 0,
      "protection field of mmap", HFILL}
    },
    {&hf_qnet6_kif_msg_io_mmap_prot_read,
     {"Read", "qnet6.kif.msgsend.msg.mmap.prot.read",
      FT_BOOLEAN, 32, NULL, 0x100,
      "protection field of mmap", HFILL}
    },
    {&hf_qnet6_kif_msg_io_mmap_prot_write,
     {"Write", "qnet6.kif.msgsend.msg.mmap.prot.write",
      FT_BOOLEAN, 32, NULL, 0x200,
      "protection field of mmap", HFILL}
    },
    {&hf_qnet6_kif_msg_io_mmap_prot_exec,
     {"Exec", "qnet6.kif.msgsend.msg.mmap.prot.exec",
      FT_BOOLEAN, 32, NULL, 0x400,
      "protection field of mmap", HFILL}
    },
    {&hf_qnet6_kif_msg_io_mmap_offset,
     {"Offset", "qnet6.kif.msgsend.msg.mmap.offset",
      FT_UINT64, BASE_HEX, NULL, 0,
      "offset of object", HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_notify_action,
     {"Action", "qnet6.kif.msgsend.msg.notify.action",
      FT_UINT32, BASE_HEX, VALS(qnet6_kif_msgsend_msg_io_notify_action_vals), 0,
      "action of notify", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_flags,
     {"Action", "qnet6.kif.msgsend.msg.notify.action",
      FT_UINT32, BASE_HEX, NULL, 0,
      "flags of notify", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_flags_31,
     {"Exten", "qnet6.kif.msgsend.msg.notify.flags.exten",
      FT_BOOLEAN, 32, NULL, 0x80000000,
      "exten flag of notify", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_flags_30,
     {"Oband", "qnet6.kif.msgsend.msg.notify.flags.oband",
      FT_BOOLEAN, 32, NULL, 0x40000000,
      "outband flag of notify", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_flags_29,
     {"Output", "qnet6.kif.msgsend.msg.notify.flags.output",
      FT_BOOLEAN, 32, NULL, 0x20000000,
      "output flag of notify", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_flags_28,
     {"Input", "qnet6.kif.msgsend.msg.notify.flags.input",
      FT_BOOLEAN, 32, NULL, 0x10000000,
      "input flag of notify", HFILL}
    },

    {&hf_qnet6_kif_msg_io_notify_mgr,
     {"Manager", "qnet6.kif.msgsend.msg.notify.mgr",
      FT_UINT64, BASE_HEX, NULL, 0,
      "managers of notify", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_flags_extra_mask,
     {"FlagsExtraMask", "qnet6.kif.msgsend.msg.notify.flags_extra_mask",
      FT_UINT32, BASE_HEX, NULL, 0,
      "extra mask of flags", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_flags_exten,
     {"FlagsExten", "qnet6.kif.msgsend.msg.notify.flags_exten",
      FT_UINT32, BASE_HEX, NULL, 0,
      "glags exten", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_nfds,
     {"Nfds", "qnet6.kif.msgsend.msg.notify.nfds",
      FT_UINT32, BASE_HEX, NULL, 0,
      "number of fds", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_fd_first,
     {"Firstfd", "qnet6.kif.msgsend.msg.notify.fd_first",
      FT_UINT32, BASE_HEX, NULL, 0,
      "first fd in nfds array", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_nfds_ready,
     {"Ready", "qnet6.kif.msgsend.msg.notify.nfds_ready",
      FT_UINT32, BASE_HEX, NULL, 0,
      "number of ready fds", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_timo,
     {"Timeout", "qnet6.kif.msgsend.msg.notify.timeo",
      FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0,
      "notify timeout", HFILL}
    },
    {&hf_qnet6_kif_msg_io_notify_fds,
     {"FDS", "qnet6.kif.msgsend.msg.notify.fds",
      FT_STRING, BASE_NONE, NULL, 0,
      NULL, HFILL}
    },

    /
    {&hf_qnet6_kif_msg_io_msg_mgrid,
     {"Mgrid", "qnet6.kif.msgsend.msg.iomsg.mgrid",
      FT_UINT16, BASE_HEX, VALS(qnet6_kif_mgr_types_vals), 0,
      "manager id", HFILL}
    },
    {&hf_qnet6_kif_msg_io_msg_subtype,
     {"subtype", "qnet6.kif.msgsend.msg.iomsg.subtype",
      FT_UINT16, BASE_HEX, NULL, 0,
      NULL, HFILL}
    },
    /
    {&hf_qnet6_kif_msg_io_dup_reserved,
     {"Reserved", "qnet6.kif.msgsend.msg.dup.reserved",
      FT_UINT32, BASE_HEX, NULL, 0,
      "dup message reserved fields", HFILL}
    },
    {&hf_qnet6_kif_msg_io_dup_key,
     {"Key", "qnet6.kif.msgsend.msg.dup.key",
      FT_UINT32, BASE_HEX, NULL, 0,
      "dup message key", HFILL}
    },

    /
    {&hf_qnet6_kif_client_info,
     {"Client_info", "qnet6.kif.client_info",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      "client information", HFILL}
    },
    {&hf_qnet6_kif_zero,
     {"Zero", "qnet6.kif.zero",
      FT_BYTES, BASE_NONE, NULL, 0,
      "All bytes should be zero", HFILL}
    },
    {&hf_qnet6_kif_client_info_nd,
     {"Nd", "qnet6.kif.client_info.nd",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "node id", HFILL}
    },
    {&hf_qnet6_kif_client_info_pid,
     {"Pid", "qnet6.kif.client_info.pid",
      FT_INT32, BASE_DEC, NULL, 0,
      "process id", HFILL}
    },
    {&hf_qnet6_kif_client_info_sid,
     {"Sid", "qnet6.kif.client_info.sid",
      FT_INT32, BASE_DEC, NULL, 0,
      "server connection id", HFILL}
    },
    {&hf_qnet6_kif_client_info_flags,
     {"Flags", "qnet6.kif.client_info.flags",
      FT_UINT32, BASE_HEX, NULL, 0,
      "connection flags", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred,
     {"Cred", "qnet6.kif.client_info.cred",
      FT_STRINGZ, BASE_NONE, NULL, 0,
      "client credential information", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_ruid,
     {"Ruid", "qnet6.kif.client_info.cred.ruid",
      FT_INT32, BASE_DEC, NULL, 0,
      "client real uid", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_euid,
     {"Euid", "qnet6.kif.client_info.cred.euid",
      FT_INT32, BASE_DEC, NULL, 0,
      "client effective uid", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_suid,
     {"Suid", "qnet6.kif.client_info.cred.suid",
      FT_INT32, BASE_DEC, NULL, 0,
      "client saved uid", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_rgid,
     {"Rgid", "qnet6.kif.client_info.cred.rgid",
      FT_INT32, BASE_DEC, NULL, 0,
      "client real gid", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_egid,
     {"Egid", "qnet6.kif.client_info.cred.egid",
      FT_INT32, BASE_DEC, NULL, 0,
      "client effective gid", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_sgid,
     {"Sgid", "qnet6.kif.client_info.cred.sgid",
      FT_INT32, BASE_DEC, NULL, 0,
      "client saved gid", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_ngroups,
     {"Ngroups", "qnet6.kif.client_info.cred.ngroups",
      FT_UINT32, BASE_DEC_HEX, NULL, 0,
      "number of groups client belongs to", HFILL}
    },
    {&hf_qnet6_kif_client_info_cred_grouplist,
     {"Grouplist", "qnet6.kif.client_info.cred.grouplist",
      FT_UINT32, BASE_DEC, NULL, 0,
      "groups client belongs to", HFILL}
    }
  };

  /
  static gint *ett[] = {
    &ett_qnet6_l4,
    &ett_qnet6_flags,
    &ett_qnet6_qos_info
  };
  static gint *ett_lr[] = {
    &ett_qnet6_lr,
    &ett_qnet6_lr_src,
    &ett_qnet6_lr_src_name_subtree,
    &ett_qnet6_lr_src_domain_subtree,
    &ett_qnet6_lr_src_addr_subtree,
    &ett_qnet6_lr_dst,
    &ett_qnet6_lr_dst_name_subtree,
    &ett_qnet6_lr_dst_domain_subtree,
    &ett_qnet6_lr_dst_addr_subtree
  };

  static gint *ett_kif[] = {
    &ett_qnet6_kif,
    &ett_qnet6_kif_vinfo,
    &ett_qnet6_kif_pulse,
    &ett_qnet6_kif_event,
    &ett_qnet6_kif_msg,
    &ett_qnet6_kif_msg_ioflag,
    &ett_qnet6_kif_msg_mode,
    &ett_qnet6_kif_msg_eflag,
    &ett_qnet6_kif_connect,
    &ett_qnet6_kif_msgsend,
    &ett_qnet6_kif_client_info,
    &ett_qnet6_kif_client_info_cred,
    &ett_qnet6_kif_client_info_cred_group,
    &ett_qnet6_kif_msg_devctl_dcmd,
    &ett_qnet6_kif_msg_read_xtypes,
    &ett_qnet6_kif_msg_write_xtypes,
    &ett_qnet6_kif_chmod_mode,
    &ett_qnet6_kif_msg_sync,
    &ett_qnet6_kif_msg_msginfo,
    &ett_qnet6_kif_msg_openfd_ioflag,
    &ett_qnet6_kif_msg_prot,
    &ett_qnet6_kif_msg_notify_flags,
    &ett_qnet6_kif_msg_notify_fds
  };
  static gint *ett_nr[] = {
    &ett_qnet6_nr
  };
  static gint *ett_qos[] = {
    &ett_qnet6_qos
  };
  module_t *qnet6_module;

  /
  proto_qnet6_l4 = proto_register_protocol("QNX6 QNET LWL4 protocol", "LWL4", "lwl4");

  proto_qnet6_qos = proto_register_protocol("QNX6 QNET QOS protocol", "QOS", "qos");

  proto_qnet6_lr = proto_register_protocol("QNX6 QNET LR protocol", "LR", "lr");

  proto_qnet6_kif = proto_register_protocol("QNX6 QNET KIF protocol", "KIF", "kif");

  proto_qnet6_nr =  proto_register_protocol("QNX6 QNET Network Resolver protocol", "NR", "nr");

  /
  proto_register_field_array(proto_qnet6_l4, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));

  proto_register_field_array(proto_qnet6_qos, hf_qos, array_length(hf_qos));
  proto_register_subtree_array(ett_qos, array_length(ett_qos));

  proto_register_field_array(proto_qnet6_lr, hf_lr, array_length(hf_lr));
  proto_register_subtree_array(ett_lr, array_length(ett_lr));

  proto_register_field_array(proto_qnet6_kif, hf_kif, array_length(hf_kif));
  proto_register_subtree_array(ett_kif, array_length(ett_kif));

  proto_register_field_array(proto_qnet6_nr, hf_nr, array_length(hf_nr));
  proto_register_subtree_array(ett_nr, array_length(ett_nr));

  qnet6_module = prefs_register_protocol(proto_qnet6_l4, NULL);
  prefs_register_bool_preference(qnet6_module, "check_crc",
                                  "Validate the LWL4 crc even crc bit is not set",
                                  "Whether to validate the LWL4 crc when crc bit is not set",
                                  &qnet6_lwl4_check_crc);

}
