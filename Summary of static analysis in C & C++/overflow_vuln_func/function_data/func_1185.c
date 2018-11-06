void proto_register_dmp (void)
{
  static hf_register_info hf[] = {
    /
    { &hf_dmp_id,
      { "DMP Identifier", "dmp.id", FT_UINT16, BASE_DEC,
        NULL, 0x0, NULL, HFILL}},

    /
    { &hf_mts_id,
      { "MTS Identifier", "dmp.mts", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_ipm_id,
      { "IPM Identifier", "dmp.ipm", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_envelope,
      { "Envelope", "dmp.envelope", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL}},

    /
    { &hf_envelope_protocol_id,
      { "Protocol Identifier", "dmp.protocol_id", FT_UINT8,
        BASE_HEX, NULL, 0xF8, NULL, HFILL}},
    { &hf_envelope_version,
      { "Protocol Version", "dmp.version", FT_UINT8, BASE_DEC,
        VALS(version_vals), 0x07, NULL, HFILL } },
    { &hf_envelope_version_value,
      { "Protocol Version", "dmp.version_value", FT_UINT8, BASE_DEC,
        VALS(version_vals), 0x07, NULL, HFILL } },

    /
    { &hf_envelope_hop_count,
      { "Hop Count", "dmp.hop_count", FT_UINT8, BASE_DEC,
        NULL, 0xE0, NULL, HFILL } },
    { &hf_envelope_hop_count_value,
      { "Hop Count", "dmp.hop_count_value", FT_UINT8, BASE_DEC,
        NULL, 0xE0, NULL, HFILL } },
    { &hf_envelope_rec_present,
      { "Recipient Present", "dmp.rec_present", FT_BOOLEAN, 8,
        TFS (&tfs_present_absent), 0x20, NULL, HFILL } },
    { &hf_envelope_addr_enc,
      { "Address Encoding", "dmp.addr_encoding", FT_BOOLEAN, 8,
        TFS (&addr_enc), 0x10, NULL, HFILL } },
    { &hf_envelope_checksum,
      { "Checksum", "dmp.checksum_used", FT_BOOLEAN, 8,
        TFS (&tfs_used_notused), 0x08, "Checksum Used", HFILL } },
    { &hf_envelope_type,
      { "Content Type", "dmp.content_type", FT_UINT8, BASE_DEC,
        VALS(type_vals), 0x07, NULL, HFILL } },

    /
    { &hf_envelope_extensions,
      { "Extensions", "dmp.extensions_used", FT_BOOLEAN, 8,
        TFS (&tfs_present_absent), 0x80, "Extensions Used", HFILL } },
    { &hf_envelope_msg_id_type,
      { "Message Identifier Type", "dmp.msg_id_type", FT_UINT8, BASE_DEC,
        VALS(msg_id_type_vals), 0x60, NULL, HFILL } },
    { &hf_envelope_msg_id_length,
      { "Message Identifier Length", "dmp.msg_id_short", FT_UINT8, BASE_DEC,
        VALS(msg_id_length_vals), 0x10, NULL, HFILL}},
    { &hf_envelope_mts_id_length,
      { "MTS Identifier Length", "dmp.mts_id_length", FT_UINT8, BASE_DEC,
        NULL, 0x1F, NULL, HFILL } },
    { &hf_envelope_ipm_id_modifier,
      { "IPM Identifier Modifier", "dmp.ipm_id_modifier", FT_UINT8, BASE_DEC,
        VALS(ipm_id_modifier), 0xC0, NULL, HFILL } },
    { &hf_envelope_ipm_id_length,
      { "IPM Identifier Length", "dmp.ipm_id_length", FT_UINT8, BASE_DEC,
        NULL, 0x3F, NULL, HFILL } },

    { &hf_thales_ipm_id_modifier,
      { "IPM Identifier Modifier", "dmp.ipm_id_modifier", FT_UINT8, BASE_DEC,
        VALS(thales_ipm_id_modifier), 0xC0, "Thales XOmail IPM Identifier Modifier", HFILL } },

    /
    { &hf_envelope_msg_id,
      { "Message Identifier", "dmp.msg_id", FT_UINT16, BASE_DEC,
        NULL, 0x0, NULL, HFILL}},
    { &hf_envelope_msg_id_12bit,
      { "Message Identifier", "dmp.msg_id", FT_UINT16, BASE_DEC,
        NULL, 0x0FFF, NULL, HFILL}},

    /
    { &hf_envelope_mts_id,
      { "MTS Identifier", "dmp.mts_id", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_envelope_ipm_id,
      { "IPM Identifier", "dmp.ipm_id", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_extensions,
      { "Extensions", "dmp.extensions", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL}},
    { &hf_extension,
      { "Extension", "dmp.extension", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_extension_header,
      { "Extension Header", "dmp.extension_header", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL}},
    { &hf_extension_more,
      { "More Extensions", "dmp.extension_more", FT_BOOLEAN, 8,
        TFS (&tfs_present_absent), 0x80, NULL, HFILL } },
    { &hf_extension_length,
      { "Extension Length (minus one)", "dmp.extension_length", FT_UINT8, BASE_DEC,
        NULL, 0x7F, "Extension Length minus one", HFILL } },
    { &hf_extension_data,
      { "Extension Data", "dmp.extension_data", FT_BYTES, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_envelope_subm_time,
      { "Submission Time", "dmp.subm_time", FT_UINT16, BASE_HEX,
        NULL, 0x0, NULL, HFILL } },
    { &hf_envelope_time_diff_present,
      { "Time Diff", "dmp.time_diff_present", FT_BOOLEAN, 16,
        TFS (&tfs_present_absent), 0x8000, "Time Diff Present", HFILL } },
    { &hf_envelope_subm_time_value,
      { "Submission Time Value", "dmp.subm_time_value", FT_UINT16,
        BASE_HEX, NULL, 0x7FFF, NULL, HFILL } },
    { &hf_envelope_time_diff,
      { "Time Difference", "dmp.time_diff", FT_UINT8, BASE_HEX,
        NULL, 0xFF, NULL, HFILL } },
    { &hf_envelope_time_diff_value,
      { "Time Difference Value", "dmp.time_diff_value", FT_UINT8,
        BASE_HEX, NULL, 0xFF, NULL, HFILL } },

    /
    { &hf_envelope_flags,
      { "Flags", "dmp.envelope_flags", FT_UINT8, BASE_DEC,
        NULL, 0x0, "Envelope Flags", HFILL}},
    { &hf_envelope_content_id_discarded,
      { "Content Identifier discarded", "dmp.cont_id_discarded",
        FT_BOOLEAN, 8, TFS(&tfs_yes_no), 0x80,
        NULL, HFILL } },
    { &hf_envelope_recip_reassign_prohib,
      { "Recipient reassign prohibited","dmp.recip_reassign_prohib",
        FT_BOOLEAN, 8, TFS(&tfs_yes_no), 0x40,
        NULL, HFILL }},
    { &hf_envelope_dl_expansion_prohib,
      { "DL expansion prohibited", "dmp.dl_expansion_prohib",
        FT_BOOLEAN, 8, TFS(&tfs_yes_no), 0x20, NULL,
        HFILL } },

    /
    { &hf_envelope_recipients,
      { "Recipient Count", "dmp.rec_count", FT_UINT8, BASE_DEC,
        NULL, 0x1F, NULL, HFILL}},
    { &hf_envelope_ext_recipients,
      { "Extended Recipient Count", "dmp.ext_rec_count", FT_UINT16,
        BASE_DEC, NULL, 0x7FFF, NULL, HFILL}},

    /
    { &hf_addr_recipient,
      { "Recipient Number", "dmp.recipient", FT_NONE, BASE_NONE,
        NULL, 0x0, "Recipient", HFILL } },
    { &hf_addr_originator,
      { "Originator", "dmp.originator", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_addr_reporting_name,
      { "Reporting Name Number", "dmp.reporting_name", FT_NONE,
        BASE_NONE, NULL, 0x0, "Reporting Name", HFILL } },
    { &hf_addr_dl_expanded,
      { "DL Expanded", "dmp.dl_expanded", FT_BOOLEAN, 8,
        NULL, 0x0, "Message has been DL expanded", HFILL } },
    { &hf_addr_int_rec,
      { "Intended Recipient", "dmp.int_rec", FT_BOOLEAN, 8,
        NULL, 0x0, "Message has an intended recipient", HFILL } },

    /
    { &hf_addr_dir_addr_ext,
      { "Address Extended", "dmp.addr_ext", FT_BOOLEAN, 8,
        NULL, 0x80, NULL, HFILL } },
    { &hf_addr_dir_rec_no,
      { "Recipient Number Offset", "dmp.rec_no_offset", FT_UINT8,
        BASE_DEC, NULL, 0xF0, NULL, HFILL } },
    { &hf_addr_dir_rec_no_generated,
      { "Recipient Number", "dmp.rec_no", FT_UINT32,
        BASE_DEC, NULL, 0x0, "Recipient Number Offset", HFILL } },
    { &hf_addr_dir_rec_no1,
      { "Recipient Number (bits 3-0)", "dmp.rec_no_offset1", FT_UINT8,
        BASE_DEC, NULL, 0xF0, "Recipient Number (bits 3-0) Offset", HFILL } },
    { &hf_addr_dir_rec_no2,
      { "Recipient Number (bits 9-4)", "dmp.rec_no_offset2", FT_UINT8,
        BASE_DEC, NULL, 0x3F, "Recipient Number (bits 9-4) Offset", HFILL } },
    { &hf_addr_dir_rec_no3,
      { "Recipient Number (bits 14-10)", "dmp.rec_no_offset3", FT_UINT8,
        BASE_DEC, NULL, 0x1F, "Recipient Number (bits 14-10) Offset",HFILL } },
    { &hf_addr_dir_rep_req1,
      { "Report Request", "dmp.rep_rec", FT_UINT8, BASE_HEX,
        VALS (report_vals_ext), 0x0C, NULL, HFILL } },
    { &hf_addr_dir_rep_req2,
      { "Report Request", "dmp.rep_rec", FT_UINT8, BASE_HEX,
        VALS (report_vals_ext), 0xC0, NULL, HFILL } },
    { &hf_addr_dir_rep_req3,
      { "Report Request", "dmp.rep_rec", FT_UINT8, BASE_HEX,
        VALS (report_vals), 0xC0, NULL, HFILL } },
    { &hf_addr_dir_not_req1,
      { "Notification Request", "dmp.not_req", FT_UINT8, BASE_HEX,
        VALS (notif_vals_ext), 0x03, NULL, HFILL } },
    { &hf_addr_dir_not_req2,
      { "Notification Request", "dmp.not_req", FT_UINT8, BASE_HEX,
        VALS (notif_vals_ext), 0xC0, NULL, HFILL } },
    { &hf_addr_dir_not_req3,
      { "Notification Request", "dmp.not_req", FT_UINT8, BASE_HEX,
        VALS (notif_vals), 0xC0, NULL, HFILL } },
    { &hf_addr_dir_action,
      { "Action", "dmp.action", FT_BOOLEAN, 8,
        TFS (&tfs_yes_no), 0x80, NULL, HFILL } },
    { &hf_addr_dir_address,
      { "Direct Address", "dmp.direct_addr", FT_UINT8,
        BASE_DEC, NULL, 0x7F, NULL, HFILL } },
    { &hf_addr_dir_address_generated,
      { "Direct Address", "dmp.direct_addr", FT_UINT32,
        BASE_DEC, NULL, 0x0, NULL, HFILL } },
    { &hf_addr_dir_address1,
      { "Direct Address (bits 6-0)", "dmp.direct_addr1", FT_UINT8,
        BASE_DEC, NULL, 0x7F, NULL, HFILL } },
    { &hf_addr_dir_address2,
      { "Direct Address (bits 12-7)", "dmp.direct_addr2", FT_UINT8,
        BASE_DEC, NULL, 0x3F, NULL, HFILL } },
    { &hf_addr_dir_address3,
      { "Direct Address (bits 18-13)", "dmp.direct_addr3", FT_UINT8,
        BASE_DEC, NULL, 0x3F, NULL, HFILL } },

    /
    { &hf_addr_ext_form,
      { "Address Form", "dmp.addr_form", FT_UINT8, BASE_DEC,
        VALS (&addr_form), 0xE0, NULL, HFILL } },
    { &hf_addr_ext_form_orig_v1,
      { "Address Form", "dmp.addr_form", FT_UINT8, BASE_DEC,
        VALS (&addr_form_orig_v1), 0xE0, NULL, HFILL } },
    { &hf_addr_ext_form_orig,
      { "Address Form", "dmp.addr_form", FT_UINT8, BASE_DEC,
        VALS (&addr_form_orig), 0xE0, NULL, HFILL } },
    { &hf_addr_ext_action,
      { "Action", "dmp.action", FT_BOOLEAN, 8,
        TFS (&tfs_yes_no), 0x10, NULL, HFILL } },
    { &hf_addr_ext_rep_req,
      { "Report Request", "dmp.rep_rec", FT_UINT8, BASE_HEX,
        VALS (report_vals), 0x0C, NULL, HFILL } },
    { &hf_addr_ext_not_req,
      { "Notification Request", "dmp.not_req", FT_UINT8, BASE_HEX,
        VALS (notif_vals), 0x03, NULL, HFILL } },
    { &hf_addr_ext_rec_ext,
      { "Recipient Number Extended", "dmp.rec_no_ext", FT_BOOLEAN, 8,
        NULL, 0x80, NULL, HFILL } },
    { &hf_addr_ext_rec_no,
      { "Recipient Number Offset", "dmp.rec_no_offset", FT_UINT8,
        BASE_DEC, NULL, 0x7F, NULL, HFILL } },
    { &hf_addr_ext_rec_no_generated,
      { "Recipient Number", "dmp.rec_no", FT_UINT32,
        BASE_DEC, NULL, 0x0, NULL, HFILL } },
    { &hf_addr_ext_rec_no1,
      { "Recipient Number (bits 6-0)", "dmp.rec_no_offset1", FT_UINT8,
        BASE_DEC, NULL, 0x7F, "Recipient Number (bits 6-0) Offset", HFILL } },
    { &hf_addr_ext_rec_no2,
      { "Recipient Number (bits 14-7)", "dmp.rec_no_offset2", FT_UINT8,
        BASE_DEC, NULL, 0xFF, "Recipient Number (bits 14-7) Offset", HFILL } },
    { &hf_addr_ext_address,
      { "Extended Address", "dmp.addr_form", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_addr_ext_type,
      { "Address Type", "dmp.addr_type", FT_UINT8, BASE_DEC,
        VALS (&ext_addr_type), 0xE0, NULL, HFILL } },
    { &hf_addr_ext_type_ext,
      { "Address Type Extended", "dmp.addr_type_ext", FT_UINT8,
        BASE_DEC, VALS (&ext_addr_type_ext), 0xE0, NULL,
        HFILL } },
    { &hf_addr_ext_length,
      { "Address Length", "dmp.addr_length", FT_UINT8,
        BASE_DEC, NULL, 0x1F, NULL, HFILL } },
    { &hf_addr_ext_length_generated,
      { "Address Length", "dmp.addr_length", FT_UINT32,
        BASE_DEC, NULL, 0x0, NULL, HFILL } },
    { &hf_addr_ext_length1,
      { "Address Length (bits 4-0)", "dmp.addr_length1", FT_UINT8,
        BASE_DEC, NULL, 0x1F, NULL, HFILL } },
    { &hf_addr_ext_length2,
      { "Address Length (bits 9-5)", "dmp.addr_length2", FT_UINT8,
        BASE_DEC, NULL, 0x1F, NULL, HFILL } },
    { &hf_addr_ext_asn1_ber,
      { "ASN.1 BER-encoded OR-name", "dmp.or_name", FT_NONE,
        BASE_NONE, NULL, 0x0, NULL, HFILL } },
    { &hf_addr_ext_asn1_per,
      { "ASN.1 PER-encoded OR-name", "dmp.asn1_per", FT_BYTES,
        BASE_NONE, NULL, 0x0, NULL, HFILL } },
    { &hf_addr_ext_unknown,
      { "Unknown encoded address", "dmp.addr_unknown", FT_BYTES,
        BASE_NONE, NULL, 0x0, NULL, HFILL } },

    /
    { &hf_message_content,
      { "Message Content", "dmp.message", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_report_content,
      { "Report Content", "dmp.report", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_notif_content,
      { "Notification Content", "dmp.notification", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    { &hf_message_st_type,
      { "Message type", "dmp.msg_type", FT_UINT8, BASE_DEC,
        VALS (message_type_vals), 0xC0, NULL, HFILL } },
    { &hf_message_precedence,
      { "Precedence", "dmp.precedence", FT_UINT8, BASE_DEC,
        VALS (precedence), 0x1C, NULL, HFILL } },
    { &hf_message_importance,
      { "Importance", "dmp.importance", FT_UINT8, BASE_DEC,
        VALS (importance), 0x1C, NULL, HFILL } },
    { &hf_message_body_format,
      { "Body format", "dmp.body_format", FT_UINT8, BASE_DEC,
        VALS (body_format_vals), 0x03, NULL, HFILL } },

    /
    { &hf_message_sec_label,
      { "Security Label", "dmp.sec_label", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_sec_class_val,
      { "Security Classification", "dmp.sec_class", FT_UINT8,
        BASE_DEC, NULL, 0xE0, NULL, HFILL}},
    { &hf_message_sec_pol,
      { "Security Policy", "dmp.sec_pol", FT_UINT8, BASE_DEC,
        VALS (sec_pol), 0x1C, NULL, HFILL } },
    { &hf_message_heading_flags,
      { "Heading Flags", "dmp.heading_flags", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_auth_users,
      { "Authorizing users discarded", "dmp.auth_discarded",
        FT_BOOLEAN, 8, TFS (&tfs_yes_no), 0x02,
        NULL, HFILL }},
    { &hf_message_subject_disc,
      { "Subject discarded", "dmp.subject_discarded", FT_BOOLEAN, 8,
        TFS (&tfs_yes_no), 0x01, NULL, HFILL } },

    /
    { &hf_message_national_policy_id,
      { "National Policy Identifier", "dmp.nat_pol_id", FT_UINT8,
        BASE_DEC, VALS(nat_pol_id), 0x0, NULL,
        HFILL } },

    /
    { &hf_message_mission_policy_id,
      { "Mission Policy Identifier", "dmp.mission_pol_id", FT_UINT8,
        BASE_DEC, NULL, 0x0, NULL,
        HFILL } },

    /
    { &hf_message_sec_cat_nat,
      { "Security Categories", "dmp.sec_cat", FT_UINT8, BASE_HEX,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_sec_cat_val,
      { "Security Categories", "dmp.sec_cat", FT_UINT8, BASE_HEX,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_sec_cat_cl,
      { "Clear", "dmp.sec_cat.cl", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x80, NULL, HFILL } },
    { &hf_message_sec_cat_cs,
      { "Crypto Security", "dmp.sec_cat.cs", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x40, NULL, HFILL } },
    { &hf_message_sec_cat_ex,
      { "Exclusive", "dmp.sec_cat.ex", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x20, NULL, HFILL } },
    { &hf_message_sec_cat_ne,
      { "National Eyes Only", "dmp.sec_cat.ne", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x10, NULL, HFILL } },
    { &hf_message_sec_cat_permissive,
      { "Releasable to", "dmp.sec_cat.permissive", FT_UINT8, BASE_HEX,
        VALS (nat_pol_id), 0xFC, NULL, HFILL } },
    { &hf_message_sec_cat_country_code,
      { "Country Code", "dmp.sec_cat.country", FT_UINT8, BASE_DEC,
        NULL, 0x00, NULL, HFILL } },
    { &hf_message_sec_cat_restrictive,
      { "Restrictive", "dmp.sec_cat.restrictive", FT_UINT8, BASE_HEX,
        NULL, 0xFC, NULL, HFILL } },
    { &hf_message_sec_cat_extended,
      { "Extended", "dmp.sec_cat.extended", FT_UINT8, BASE_HEX,
        VALS (ext_sec_cat), 0x03, "Extended Security Category", HFILL } },
    { &hf_message_sec_cat_bit0,
      { "Bit 0", "dmp.sec_cat.bit0", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x01, NULL, HFILL } },
    { &hf_message_sec_cat_bit1,
      { "Bit 1", "dmp.sec_cat.bit1", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x02, NULL, HFILL } },
    { &hf_message_sec_cat_bit2,
      { "Bit 2", "dmp.sec_cat.bit2", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x04, NULL, HFILL } },
    { &hf_message_sec_cat_bit3,
      { "Bit 3", "dmp.sec_cat.bit3", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x08, NULL, HFILL } },
    { &hf_message_sec_cat_bit4,
      { "Bit 4", "dmp.sec_cat.bit4", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x10, NULL, HFILL } },
    { &hf_message_sec_cat_bit5,
      { "Bit 5", "dmp.sec_cat.bit5", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x20, NULL, HFILL } },
    { &hf_message_sec_cat_bit6,
      { "Bit 6", "dmp.sec_cat.bit6", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x40, NULL, HFILL } },
    { &hf_message_sec_cat_bit7,
      { "Bit 7", "dmp.sec_cat.bit7", FT_BOOLEAN, 8,
        TFS (&tfs_set_notset), 0x80, NULL, HFILL } },

    /
    { &hf_message_exp_time,
      { "Expiry Time", "dmp.expiry_time", FT_UINT8, BASE_HEX,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_exp_time_val,
      { "Expiry Time Value", "dmp.expiry_time_val", FT_UINT8, BASE_HEX,
        NULL, 0xFF, NULL, HFILL } },

    /
    { &hf_message_dtg,
      { "DTG", "dmp.dtg", FT_UINT8, BASE_HEX,
        NULL, 0xFF, NULL, HFILL } },
    { &hf_message_dtg_sign,
      { "DTG in the", "dmp.dtg.sign", FT_BOOLEAN, 8, TFS (&dtg_sign),
        0x80, "Sign", HFILL } },
    { &hf_message_dtg_val,
      { "DTG Value", "dmp.dtg.val", FT_UINT8, BASE_HEX, NULL,
        0x7F, NULL, HFILL } },

    /
    { &hf_message_sic,
      { "SIC", "dmp.sic", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_sic_key,
      { "SICs", "dmp.sic_key", FT_NONE, BASE_NONE,
        NULL, 0x0, "SIC Content", HFILL } },
    { &hf_message_sic_key_values,
      { "Content Byte", "dmp.sic_key.values", FT_UINT8, BASE_HEX,
        NULL, 0x0, "SIC Content Byte", HFILL } },
    { &hf_message_sic_key_type,
      { "Type", "dmp.sic_key.type", FT_UINT8, BASE_HEX,
        VALS (sic_key_type), 0xF0, "SIC Content Type", HFILL } },
    { &hf_message_sic_key_chars,
      { "Valid Characters", "dmp.sic_key.chars", FT_BOOLEAN, 8,
        TFS (&sic_key_chars), 0x08, "SIC Valid Characters", HFILL } },
    { &hf_message_sic_key_num,
      { "Number of SICs", "dmp.sic_key.num", FT_UINT8, BASE_HEX,
        VALS (sic_key_num), 0x07, NULL, HFILL } },
    { &hf_message_sic_bitmap,
      { "Length Bitmap (0 = 3 bytes, 1 = 4-8 bytes)", "dmp.sic_bitmap",
        FT_UINT8, BASE_HEX, NULL, 0xFF, "SIC Length Bitmap", HFILL } },
    { &hf_message_sic_bits,
      { "Bit 7-4", "dmp.sic_bits", FT_UINT8, BASE_HEX,
        VALS(sic_bit_vals), 0xF0, "SIC Bit 7-4, Characters [A-Z0-9] only",
        HFILL } },
    { &hf_message_sic_bits_any,
      { "Bit 7-4", "dmp.sic_bits_any", FT_UINT8, BASE_HEX,
        VALS(sic_bit_any_vals), 0xF0, "SIC Bit 7-4, Any valid characters",
        HFILL } },

    /
    { &hf_message_subj_id,
      { "Subject Message Identifier", "dmp.subj_id", FT_UINT16,
        BASE_DEC, NULL, 0x0, NULL, HFILL } },

    /
    { &hf_message_subj_mts_id,
      { "Subject MTS Identifier", "dmp.subj_mts_id", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_message_subj_ipm_id,
      { "Subject IPM Identifier", "dmp.subj_ipm_id", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_message_body,
      { "Message Body", "dmp.body", FT_NONE, BASE_NONE, NULL,
        0x0, NULL, HFILL}},

    /
    { &hf_message_eit,
      { "EIT", "dmp.body.eit", FT_UINT8, BASE_DEC,
        VALS(eit_vals), 0xE0, "Encoded Information Type", HFILL } },
    { &hf_message_compr,
      { "Compression", "dmp.body.compression", FT_UINT8, BASE_DEC,
        VALS(compression_vals), 0x18, NULL, HFILL } },

    /
    { &hf_message_subject,
      { "Subject", "dmp.subject", FT_STRINGZ, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_message_body_data,
      { "User data", "dmp.body.data", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_body_plain,
      { "Message Body", "dmp.body.plain", FT_STRING, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_bodyid_uint8,
      { "Structured Id", "dmp.body.id", FT_UINT8, BASE_DEC,
        NULL, 0x0, "Structured Body Id (1 byte)", HFILL } },
    { &hf_message_bodyid_uint16,
      { "Structured Id", "dmp.body.id", FT_UINT16, BASE_DEC,
        NULL, 0x0, "Structured Body Id (2 bytes)", HFILL } },
    { &hf_message_bodyid_uint32,
      { "Structured Id", "dmp.body.id", FT_UINT32, BASE_DEC,
        NULL, 0x0, "Structured Body Id (4 bytes)", HFILL } },
    { &hf_message_bodyid_uint64,
      { "Structured Id", "dmp.body.id", FT_UINT64, BASE_DEC,
        NULL, 0x0, "Structured Body Id (8 bytes)", HFILL } },
    { &hf_message_bodyid_string,
      { "Structured Id", "dmp.body.id", FT_STRING, BASE_NONE,
        NULL, 0x0, "Structured Body Id (fixed text string)", HFILL } },
    { &hf_message_bodyid_zstring,
      { "Structured Id", "dmp.body.id", FT_STRINGZ, BASE_NONE,
        NULL, 0x0, "Structured Body Id (zero terminated text string)",
        HFILL } },
    { &hf_message_body_structured,
      { "Structured Body", "dmp.body.structured", FT_BYTES, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_message_body_uncompr,
      { "Uncompressed User data", "dmp.body.uncompressed", FT_NONE,
        BASE_NONE, NULL, 0x0, NULL, HFILL } },
    { &hf_message_body_uncompressed,
      { "Uncompressed Message Body", "dmp.body.uncompressed",
        FT_STRING, BASE_NONE, NULL, 0x0, NULL,
        HFILL } },

    /
    { &hf_delivery_report,
      { "Delivery Report", "dmp.dr", FT_NONE, BASE_NONE, NULL,
        0x0, NULL, HFILL}},
    { &hf_non_delivery_report,
      { "Non-Delivery Report", "dmp.ndr", FT_NONE, BASE_NONE, NULL,
        0x0, NULL, HFILL}},

    { &hf_report_type,
      { "Report Type", "dmp.report_type", FT_BOOLEAN, 8,
        TFS (&report_type), 0x80, NULL, HFILL } },
    { &hf_report_info_present_dr,
      { "Info Present", "dmp.info_present", FT_BOOLEAN, 8,
        TFS (&tfs_present_absent), 0x40, NULL, HFILL } },
    { &hf_report_addr_enc_dr,
      { "Address Encoding", "dmp.addr_encoding", FT_BOOLEAN, 8,
        TFS (&addr_enc), 0x20, NULL, HFILL } },
    { &hf_report_del_time,
      { "Delivery Time", "dmp.delivery_time", FT_UINT8, BASE_HEX,
        NULL, 0x0, NULL, HFILL } },
    { &hf_report_del_time_val,
      { "Delivery Time Value", "dmp.delivery_time_val", FT_UINT8,
        BASE_HEX, NULL, 0xFF, NULL, HFILL } },
    { &hf_report_addr_enc_ndr,
      { "Address Encoding", "dmp.addr_encoding", FT_BOOLEAN, 8,
        TFS (&addr_enc), 0x40, NULL, HFILL } },
    { &hf_report_reason,
      { "Reason (P1)", "dmp.report_reason", FT_UINT8, BASE_DEC,
        VALS (p1_NonDeliveryReasonCode_vals), 0x3F,
        "Reason", HFILL } },
    { &hf_report_info_present_ndr,
      { "Info Present", "dmp.info_present", FT_BOOLEAN, 8,
        TFS (&tfs_present_absent), 0x80, NULL, HFILL } },
    { &hf_report_diagn,
      { "Diagnostic (P1)", "dmp.report_diagnostic", FT_UINT8, BASE_DEC,
        VALS (p1_NonDeliveryDiagnosticCode_vals), 0x7F,
        "Diagnostic", HFILL } },
    { &hf_report_suppl_info_len,
      { "Supplementary Information", "dmp.suppl_info_len", FT_UINT8,
        BASE_DEC, NULL, 0x0, "Supplementary Information Length", HFILL } },
    { &hf_report_suppl_info,
      { "Supplementary Information", "dmp.suppl_info", FT_STRINGZ,
        BASE_NONE, NULL, 0x0, NULL, HFILL } },

    /
    { &hf_receipt_notif,
      { "Receipt Notification (RN)", "dmp.rn", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL} },
    { &hf_non_receipt_notif,
      { "Non-Receipt Notification (NRN)", "dmp.nrn", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL} },
    { &hf_other_notif,
      { "Other Notification (ON)", "dmp.on", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL} },

    { &hf_notif_type,
      { "Notification Type", "dmp.notif_type", FT_UINT8, BASE_DEC,
        VALS (notif_type), 0x03, NULL, HFILL } },
    { &hf_notif_rec_time,
      { "Receipt Time", "dmp.receipt_time", FT_UINT8, BASE_HEX,
        NULL, 0x0, NULL, HFILL } },
    { &hf_notif_rec_time_val,
      { "Receipt Time Value", "dmp.receipt_time_val", FT_UINT8,
        BASE_HEX, NULL, 0xFF, NULL, HFILL } },
    { &hf_notif_suppl_info_len,
      { "Supplementary Information", "dmp.suppl_info_len",
        FT_UINT8, BASE_DEC, NULL, 0x0, "Supplementary Information Length",
        HFILL } },
    { &hf_notif_suppl_info,
      { "Supplementary Information", "dmp.suppl_info",
        FT_STRINGZ, BASE_NONE, NULL, 0x0, NULL,
        HFILL } },
    { &hf_notif_non_rec_reason,
      { "Non-Receipt Reason", "dmp.notif_non_rec_reason",
        FT_UINT8, BASE_DEC, VALS (p22_NonReceiptReasonField_vals), 0x0,
        NULL, HFILL } },
    { &hf_notif_discard_reason,
      { "Discard Reason", "dmp.notif_discard_reason", FT_UINT8,
        BASE_DEC, VALS (p22_DiscardReasonField_vals), 0x0,
        NULL, HFILL } },
    { &hf_notif_on_type,
      { "ON Type", "dmp.notif_on_type", FT_UINT8, BASE_DEC,
        VALS (on_type), 0x0, NULL, HFILL } },
    { &hf_notif_acp127,
      { "ACP127 Recipient", "dmp.acp127recip_len", FT_UINT8,
        BASE_DEC, NULL, 0x0, "ACP 127 Recipient Length", HFILL } },
    { &hf_notif_acp127recip,
      { "ACP127 Recipient", "dmp.acp127recip", FT_STRINGZ,
        BASE_NONE, NULL, 0x0, "ACP 127 Recipient", HFILL } },

    /
    { &hf_ack,
      { "Acknowledgement", "dmp.ack", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },
    { &hf_ack_reason,
      { "Ack Reason", "dmp.ack_reason", FT_UINT8, BASE_DEC,
        VALS (&ack_reason), 0x0, "Reason", HFILL } },
    { &hf_ack_diagnostic,
      { "Ack Diagnostic", "dmp.ack_diagnostic", FT_UINT8, BASE_DEC,
        NULL, 0x0, "Diagnostic", HFILL } },
    { &hf_ack_recips,
      { "Recipient List", "dmp.ack_rec_list", FT_NONE, BASE_NONE,
        NULL, 0x0, NULL, HFILL } },

    /
    { &hf_checksum,
      { "Checksum", "dmp.checksum", FT_UINT16, BASE_HEX,
        NULL, 0x0, NULL, HFILL } },
    { &hf_checksum_good,
      { "Good", "dmp.checksum_good", FT_BOOLEAN, BASE_NONE,
        NULL, 0x0, "True: checksum matches packet content; False: doesn't match content or not checked", HFILL } },
    { &hf_checksum_bad,
      { "Bad", "dmp.checksum_bad", FT_BOOLEAN, BASE_NONE,
        NULL, 0x0, "True: checksum doesn't match packet content; False: matches content or not checked", HFILL } },

    /
    { &hf_analysis_ack_time,
      { "Acknowledgement Time", "dmp.analysis.ack_time", FT_RELATIVE_TIME, BASE_NONE,
        NULL, 0x0, "The time between the Message and the Acknowledge", HFILL } },
    { &hf_analysis_rep_time,
      { "Report Reply Time", "dmp.analysis.report_time", FT_RELATIVE_TIME, BASE_NONE,
        NULL, 0x0, "The time between the Message and the Report", HFILL } },
    { &hf_analysis_not_time,
      { "Notification Reply Time", "dmp.analysis.notif_time", FT_RELATIVE_TIME, BASE_NONE,
        NULL, 0x0, "The time between the Message and the Notification", HFILL } },
    { &hf_analysis_total_time,
      { "Total Time", "dmp.analysis.total_time", FT_RELATIVE_TIME, BASE_NONE,
        NULL, 0x0, "The time between the first Message and the Acknowledge", HFILL } },
    { &hf_analysis_retrans_time,
      { "Retransmission Time", "dmp.analysis.retrans_time", FT_RELATIVE_TIME, BASE_NONE,
        NULL, 0x0, "The time between the last Message and this Message", HFILL } },
    { &hf_analysis_total_retrans_time,
      { "Total Retransmission Time", "dmp.analysis.total_retrans_time", FT_RELATIVE_TIME, BASE_NONE,
        NULL, 0x0, "The time between the first Message and this Message", HFILL } },
    { &hf_analysis_msg_num,
      { "Message in", "dmp.analysis.msg_in", FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This packet has a Message in this frame", HFILL } },
    { &hf_analysis_ack_num,
      { "Acknowledgement in", "dmp.analysis.ack_in", FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This packet has an Acknowledgement in this frame", HFILL } },
    { &hf_analysis_rep_num,
      { "Report in", "dmp.analysis.report_in", FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This packet has a Report in this frame", HFILL } },
    { &hf_analysis_not_num,
      { "Notification in", "dmp.analysis.notif_in", FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This packet has a Notification in this frame", HFILL } },
    { &hf_analysis_msg_missing,
      { "Message missing", "dmp.analysis.msg_missing", FT_NONE, BASE_NONE,
        NULL, 0x0, "The Message for this packet is missing", HFILL } },
    { &hf_analysis_ack_missing,
      { "Acknowledgement missing", "dmp.analysis.ack_missing", FT_NONE, BASE_NONE,
        NULL, 0x0, "The acknowledgement for this packet is missing", HFILL } },
    { &hf_analysis_retrans_no,
      { "Retransmission #", "dmp.analysis.retrans_no", FT_UINT32, BASE_DEC,
        NULL, 0x0, "Retransmission count", HFILL } },
    { &hf_analysis_ack_dup_no,
      { "Duplicate ACK #", "dmp.analysis.dup_ack_no", FT_UINT32, BASE_DEC,
        NULL, 0x0, "Duplicate Acknowledgement count", HFILL } },
    { &hf_analysis_msg_resend_from,
      { "Retransmission of Message sent in", "dmp.analysis.msg_first_sent_in",
        FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This Message was first sent in this frame", HFILL } },
    { &hf_analysis_rep_resend_from,
      { "Retransmission of Report sent in", "dmp.analysis.report_first_sent_in",
        FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This Report was first sent in this frame", HFILL } },
    { &hf_analysis_not_resend_from,
      { "Retransmission of Notification sent in", "dmp.analysis.notif_first_sent_in",
        FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This Notification was first sent in this frame", HFILL } },
    { &hf_analysis_ack_resend_from,
      { "Retransmission of Acknowledgement sent in", "dmp.analysis.ack_first_sent_in",
        FT_FRAMENUM, BASE_NONE,
        NULL, 0x0, "This Acknowledgement was first sent in this frame", HFILL } },

    /
    { &hf_reserved_0x01,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x01, NULL, HFILL } },
    { &hf_reserved_0x02,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x02, NULL, HFILL } },
    { &hf_reserved_0x04,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x04, NULL, HFILL } },
    { &hf_reserved_0x07,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x07, NULL, HFILL } },
    { &hf_reserved_0x08,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x08, NULL, HFILL } },
    { &hf_reserved_0x0F,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x0F, NULL, HFILL } },
    { &hf_reserved_0x1F,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x1F, NULL, HFILL } },
    { &hf_reserved_0x20,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x20, NULL, HFILL } },
    { &hf_reserved_0x40,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0x40, NULL, HFILL } },
    { &hf_reserved_0xC0,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0xC0, NULL, HFILL } },
    { &hf_reserved_0xE0,
      { "Reserved", "dmp.reserved", FT_UINT8, BASE_DEC,
        NULL, 0xE0, NULL, HFILL } },
    { &hf_reserved_0x8000,
      { "Reserved", "dmp.reserved", FT_UINT16, BASE_DEC,
        NULL, 0x8000, NULL, HFILL } },
  };

  static gint *ett[] = {
    &ett_dmp,
    &ett_envelope,
    &ett_envelope_version,
    &ett_envelope_hop_count,
    &ett_envelope_rec_present,
    &ett_envelope_addr_enc,
    &ett_envelope_checksum,
    &ett_envelope_extensions,
    &ett_envelope_msg_id_type,
    &ett_envelope_msg_id,
    &ett_envelope_mts_id_length,
    &ett_envelope_ipm_id_length,
    &ett_envelope_cont_type,
    &ett_envelope_subm_time,
    &ett_envelope_time_diff,
    &ett_envelope_flags,
    &ett_envelope_recipients,
    &ett_envelope_ext_recipients,
    &ett_envelope_addresses,
    &ett_address,
    &ett_address_direct,
    &ett_address_rec_no,
    &ett_address_extended,
    &ett_address_ext_form,
    &ett_address_ext_rec_no,
    &ett_address_ext_action,
    &ett_address_ext_rep_req,
    &ett_address_ext_not_req,
    &ett_address_ext_type,
    &ett_address_ext_length,
    &ett_extensions,
    &ett_extension,
    &ett_extension_header,
    &ett_content,
    &ett_message,
    &ett_message_st_type,
    &ett_message_reserved,
    &ett_message_precedence,
    &ett_message_importance,
    &ett_message_body_format,
    &ett_message_sec_class,
    &ett_message_sec_pol,
    &ett_message_sec_cat,
    &ett_message_heading_flags,
    &ett_message_exp_time,
    &ett_message_dtg,
    &ett_message_sic,
    &ett_message_sic_key,
    &ett_message_sic_bitmap,
    &ett_message_sic_bits,
    &ett_message_eit,
    &ett_message_compr,
    &ett_message_body_reserved,
    &ett_message_body,
    &ett_message_body_uncompr,
    &ett_report,
    &ett_report_type,
    &ett_report_info_present_dr,
    &ett_report_info_present_ndr,
    &ett_report_addr_enc_dr,
    &ett_report_addr_enc_ndr,
    &ett_report_reserved,
    &ett_report_del_time,
    &ett_report_reason,
    &ett_report_suppl_info,
    &ett_report_diagn,
    &ett_notif,
    &ett_notif_type,
    &ett_notif_rec_time,
    &ett_notif_suppl_info,
    &ett_notif_acp127recip,
    &ett_ack,
    &ett_ack_recips,
    &ett_checksum,
    &ett_analysis
  };
  
  static uat_field_t attributes_flds[] = {
    UAT_FLD_VS(dmp_security_class,nation, "Nation", nat_pol_id, 0),
    UAT_FLD_DEC(dmp_security_class,class, "Classification", "Security Classification"),
    UAT_FLD_CSTRING(dmp_security_class,name, "Name", "Classification Name"),
    UAT_END_FIELDS
  };
  
  uat_t *attributes_uat = uat_new("DMP Security Classifications",
                                  sizeof(dmp_security_class_t),
                                  "dmp_security_classifications",
                                  TRUE,
                                  (void*) &dmp_security_classes,
                                  &num_dmp_security_classes,
                                  UAT_CAT_FFMT,
                                  "ChDMPSecurityClassifications",
                                  dmp_class_copy_cb,
                                  NULL,
                                  dmp_class_free_cb,
                                  NULL,
                                  attributes_flds);

  module_t *dmp_module;

  proto_dmp = proto_register_protocol (PNAME, PSNAME, PFNAME);
  register_dissector(PFNAME, dissect_dmp, proto_dmp);

  proto_register_field_array (proto_dmp, hf, array_length (hf));
  proto_register_subtree_array (ett, array_length (ett));
  register_init_routine (&dmp_init_routine);

  /
  range_convert_str (&global_dmp_port_range, DEFAULT_DMP_PORT_RANGE,
                     MAX_UDP_PORT);

  /
  build_national_strings ();

  /
  dmp_module = prefs_register_protocol (proto_dmp, proto_reg_handoff_dmp);

  prefs_register_obsolete_preference (dmp_module, "udp_port");
  prefs_register_obsolete_preference (dmp_module, "udp_port_second");

  prefs_register_range_preference (dmp_module, "udp_ports",
                                  "DMP port numbers",
                                  "Port numbers used for DMP traffic",
                                   &global_dmp_port_range, MAX_UDP_PORT);
  prefs_register_enum_preference (dmp_module, "national_decode",
                                  "National decoding",
                                  "Select the type of decoding for nationally-defined values",
                                  &dmp_nat_decode, national_decoding,
                                  FALSE);
  prefs_register_enum_preference (dmp_module, "local_nation",
                                  "Nation of local server",
                                  "Select the nation of sending server.  This is used when presenting"
                                  " security classification values in messages with security"
                                  " policy set to National (nation of local server)",
                                  &dmp_local_nation, dmp_national_values,
                                  FALSE);
  prefs_register_uat_preference (dmp_module, "classes_table",
                                 "National Security Classifications",
                                 "Translation table for national security classifications.  This is used"
                                 " when presenting security classification values in messages with"
                                 " security policy set to National or Extended National",
                                 attributes_uat);
  prefs_register_bool_preference (dmp_module, "seq_ack_analysis",
                                  "SEQ/ACK Analysis",
                                  "Calculate sequence/acknowledgement analysis",
                                  &use_seq_ack_analysis);
  prefs_register_bool_preference (dmp_module, "align_ids",
                                  "Align identifiers in info list",
                                  "Align identifiers in info list"
                                  " (does not align when retransmission or"
                                  " duplicate acknowledgement indication)",
                                  &dmp_align);
  prefs_register_bool_preference (dmp_module, "subject_as_id",
                                  "Print subject as body id",
                                  "Print subject as body id in free text "
                                  "messages with subject",
                                  &dmp_subject_as_id);
  prefs_register_enum_preference (dmp_module, "struct_print",
                                  "Structured message id format",
                                  "Format of the structured message id",
                                  &dmp_struct_format, struct_id_options,
                                  FALSE);
  prefs_register_uint_preference (dmp_module, "struct_offset",
                                  "Offset to structured message id",
                                  "Used to set where the structured message "
                                  "id starts in the User Data",
                                  10, &dmp_struct_offset);

  prefs_register_uint_preference (dmp_module, "struct_length",
                                  "Fixed text string length",
                                  "Used to set length of fixed text string "
                                  "in the structured message id format "
                                  "(maximum 128 characters)",
                                  10, &dmp_struct_length);
}
