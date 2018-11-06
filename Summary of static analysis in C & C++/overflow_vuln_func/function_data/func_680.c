static void
dissect_cablelabs_specific_opts(proto_tree *v_tree, proto_item *v_item, packet_info *pinfo, tvbuff_t *tvb, int voff, int len)
{
    guint16 type,
            tlv_len, /
            opt_len, /
            sub_value;
    proto_item *ti;
    proto_item *ti2;
    proto_tree *subtree;
    proto_tree *subtree2;
    gint tlv5_cap_index,
         tlv5_counter,
         tlv5_cap_len;
    int off = voff,
        sub_off, /
        i,
        field_len, /
        field_value;
    gchar *device_type = NULL;

    if (len > 4) {
        while (off - voff < len) {

            /
            type = tvb_get_ntohs(tvb, off);
            ti = proto_tree_add_item(v_tree, hf_cablelabs_opts, tvb, off, 2, ENC_BIG_ENDIAN);
            /
            tlv_len = tvb_get_ntohs(tvb, off+2);

            /
            sub_off = off + 4;

            switch (type) {
                /
            case CL_OPTION_DEVICE_TYPE:
                opt_len = tlv_len;
                field_len = tlv_len;

                device_type = tvb_get_string_enc(wmem_packet_scope(), tvb, sub_off, field_len, ENC_ASCII);

                if ((device_type == NULL) || (strlen(device_type) == 0)) {
                    proto_item_append_text(ti, "Packet does not contain Device Type.");
                } else {
                    proto_item_append_text(ti, "\"%s\"", device_type);
                }
                break;
            case CL_OPTION_DEVICE_SERIAL_NUMBER:
            case CL_OPTION_HARDWARE_VERSION_NUMBER:
            case CL_OPTION_SOFTWARE_VERSION_NUMBER:
            case CL_OPTION_BOOT_ROM_VERSION:
            case CL_OPTION_MODEL_NUMBER:
            case CL_OPTION_VENDOR_NAME:
            case CL_OPTION_CONFIG_FILE_NAME:
            case CL_OPTION_EMBEDDED_COMPONENT_LIST:
                opt_len = tlv_len;
                field_len = tlv_len;
                proto_item_append_text(ti, "\"%s\"",
                                       tvb_format_stringzpad(tvb, sub_off, field_len));
                break;
            case CL_OPTION_VENDOR_OUI:
                /
                opt_len = tlv_len;
                if (tlv_len == 3) {
                    proto_item_append_text(ti, "%s",
                        tvb_bytes_to_str_punct(wmem_packet_scope(), tvb, sub_off, 3, ':'));
                } else if (tlv_len == 6) {
                    proto_item_append_text(ti, "\"%s\"", tvb_format_stringzpad(tvb, sub_off, tlv_len));
                } else {
                    expert_add_info_format(pinfo, ti, &ei_dhcpv6_bogus_length, "Suboption %d: suboption length isn't 3 or 6", type);
                }
                break;
            case CL_OPTION_ORO:
                field_len = 2;
                opt_len = tlv_len;
                if (opt_len > 0) {
                    for (i = 0; i < tlv_len; i += field_len) {
                        sub_value = tvb_get_ntohs(tvb, sub_off);
                        proto_item_append_text(ti, " %d", sub_value);
                        sub_off += field_len;
                    }
                }
                break;
            /
            case CL_OPTION_TFTP_SERVERS:
            case CL_OPTION_SYSLOG_SERVERS:
            case CL_OPTION_RFC868_SERVERS:
                field_len = 16;
                opt_len = tlv_len;
                subtree = proto_item_add_subtree(ti, ett_dhcpv6_vendor_option);

                if ((tlv_len % field_len) == 0) {
                    for (i = 0; i < tlv_len/field_len; i++) {
                        ti = proto_tree_add_item(subtree, hf_cablelabs_ipv6_server, tvb, sub_off, 16, ENC_NA);
                        proto_item_prepend_text(ti, " %d ", i + 1);
                        sub_off += field_len;
                    }
                }
                break;
            case CL_OPTION_DEVICE_ID:
                opt_len = tlv_len;
                field_len = tlv_len;
                if (tlv_len != 6) {
                    expert_add_info_format(pinfo, ti, &ei_dhcpv6_bogus_length, "Bogus length: %d", tlv_len);
                }
                else {
                    proto_item_append_text(ti, "%s",
                                           tvb_bytes_to_str(wmem_packet_scope(), tvb, sub_off, field_len));
                }
                break;
            case CL_OPTION_TLV5:
                /
                opt_len = tlv_len;

                if (device_type == NULL)
                    break;

                tlv5_counter = 0;
                tlv5_cap_index = sub_off;

                subtree = proto_item_add_subtree(ti, ett_dhcpv6_tlv5_type);

                while (tlv5_counter < tlv_len) {

                    if (!g_ascii_strncasecmp(device_type, "ecm", 3)) {
                        ti2 = proto_tree_add_item(subtree, hf_modem_capabilities_encoding_type, tvb, tlv5_cap_index, 1, ENC_BIG_ENDIAN);
                    } else if (!g_ascii_strncasecmp(device_type, "edva", 3)) {
                        ti2 = proto_tree_add_item(subtree, hf_eue_capabilities_encoding_type, tvb, tlv5_cap_index, 1, ENC_BIG_ENDIAN);
                    } else {
                        break;
                    }

                    tlv5_cap_index++;
                    tlv5_counter++;

                    /
                    subtree2 = proto_item_add_subtree(ti2, ett_dhcpv6_tlv5_type);

                    proto_tree_add_item(subtree2, hf_capabilities_encoding_length, tvb, tlv5_cap_index, 1, ENC_BIG_ENDIAN);
                    tlv5_cap_len = (guint8) tvb_get_guint8(tvb, tlv5_cap_index);

                    tlv5_cap_index++;
                    tlv5_counter += tlv5_cap_len;

                    /
                    if (tlv5_cap_len > 2) {
                            proto_tree_add_item(subtree2, hf_capabilities_encoding_bytes, tvb, tlv5_cap_index, tlv5_cap_len, ENC_NA);
                    } else {
                            proto_tree_add_item(subtree2, hf_capabilities_encoding_number, tvb, tlv5_cap_index, tlv5_cap_len, ENC_BIG_ENDIAN);
                    }

                    tlv5_cap_index += tlv5_cap_len;
                    tlv5_counter++;
                }
                break;
            case CL_OPTION_TIME_OFFSET:
                opt_len = tlv_len;
                proto_item_append_text(ti, "%d", tvb_get_ntohl(tvb, sub_off));
                break;
            case CL_OPTION_IP_PREF:
                opt_len = tlv_len;
                field_value = tvb_get_guint8(tvb, sub_off);
                if (field_value == 1) {
                    proto_item_append_text(ti, "%s", "IPv4");
                } else if (field_value == 2) {
                    proto_item_append_text(ti, "%s", "IPv6");
                } else if (field_value == 6) {
                    proto_item_append_text(ti, "%s", "Dual Stack");
                } else {
                    proto_item_append_text(ti, "%s%d", "Invalid IP Preference value ", field_value);
                }
                break;
            case CL_OPTION_DOCS_CMTS_CAP:
                opt_len = tlv_len;
                field_len = 0;
                subtree = proto_item_add_subtree(ti, ett_dhcpv6_vendor_option);

                /
                if (tlv_len > 0) {
                    for (i = 0; field_len < opt_len; i++) {
                        int tagLen = 0;
                        int tag = 0;
                        tag = tvb_get_guint8(tvb, sub_off);
                        sub_off++;
                        tagLen = tvb_get_guint8(tvb, sub_off);
                        sub_off++;
                        if ((tag == CL_OPTION_DOCS_CMTS_TLV_VERS_NUM) && (tagLen == 2)) {
                            proto_tree_add_item(subtree, hf_cablelabs_docsis_version_number, tvb, sub_off,
                                2, ENC_BIG_ENDIAN);
                            sub_off += 2;
                        }
                        else
                            sub_off += tagLen;

                        field_len += tagLen + 2;
                    }
                }
                else
                    proto_item_append_text(ti, " (empty)");
                break;
            case CL_CM_MAC_ADDR:
                opt_len = tlv_len;
                if (tlv_len != 6) {
                    expert_add_info_format(pinfo, ti, &ei_dhcpv6_bogus_length, "Bogus length: %d", tlv_len);
                }
                else {
                    /
                    proto_item_append_text(ti, "%s", tvb_bytes_to_str_punct(wmem_packet_scope(), tvb, sub_off, opt_len, ':'));
                    /
                }
                break;
            case CL_EROUTER_CONTAINER_OPTION:
                opt_len = tlv_len;
                proto_item_append_text(ti, " %s (len=%d)",
                                       tvb_bytes_to_str(wmem_packet_scope(), tvb, sub_off, opt_len), tlv_len);
                break;
            case CL_OPTION_CCC:
                opt_len = tlv_len;
                field_len = 0;
                subtree = proto_item_add_subtree(ti, ett_dhcpv6_vendor_option);
                proto_item_append_text(ti, " (%d bytes)", opt_len);
                while (field_len < opt_len) {
                    sub_value = dissect_packetcable_ccc_option(subtree, ti, pinfo, tvb,
                                                               sub_off, (opt_len - field_len));
                    sub_off += sub_value;
                    field_len += sub_value;
                }
                break;
            case CL_OPTION_CCCV6:
                opt_len = tlv_len;
                field_len = 0;
                subtree = proto_item_add_subtree(ti, ett_dhcpv6_vendor_option);
                proto_item_append_text(ti, " (%d bytes)", opt_len);
                while (field_len < opt_len) {
                    sub_value = dissect_packetcable_cccV6_option(subtree, ti, pinfo, tvb,
                        sub_off, (opt_len - field_len));
                    sub_off += sub_value;
                    field_len += sub_value;
                }
                break;
            case CL_OPTION_CORRELATION_ID:
                opt_len = tlv_len;
                 if (tlv_len != 4) {
                    proto_item_append_text(ti, "Bogus value length=%d",
                                           tlv_len);
                }
                else {
                    proto_item_append_text(ti, "%u", tvb_get_ntohl(tvb, sub_off));
                }
                break;
            default:
                opt_len = tlv_len;
                break;
            }
            off += (opt_len + 4);

        }
    }
    else {
        expert_add_info_format(pinfo, v_item, &ei_dhcpv6_bogus_length, "Bogus length: %d", len);
    }
}
