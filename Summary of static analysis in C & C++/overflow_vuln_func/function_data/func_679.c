static int
dissect_packetcable_cccV6_option(proto_tree *v_tree, proto_item *v_item, packet_info *pinfo, tvbuff_t *tvb, int optoff,
    int optend)
{
    int         suboptoff = optoff;
    guint16     subopt, subopt_len;
    guint8      type;
    proto_item *vti, *ti;
    proto_tree *pkt_s_tree;
    int         i;

    subopt = tvb_get_ntohs(tvb, optoff);
    suboptoff += 2;

    subopt_len = tvb_get_ntohs(tvb, suboptoff);
    suboptoff += 2;

    /
    if (optend <= 0) {
        expert_add_info_format(pinfo, v_item, &ei_dhcpv6_no_suboption_len, "Sub element %d: no room left in option for suboption length", subopt);
        return (optend);
    }

    vti = proto_tree_add_item(v_tree, hf_packetcable_cccV6_suboption, tvb, optoff, 2, ENC_BIG_ENDIAN);
    pkt_s_tree = proto_item_add_subtree(vti, ett_dhcpv6_pkt_option);

    switch (subopt) {
    case PKT_CCCV6_PRI_DSS:
        if (subopt_len < 35) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_pri_dss, tvb, suboptoff, subopt_len, ENC_ASCII|ENC_NA);
        } else {
            expert_add_info_format(pinfo, vti, &ei_dhcpv6_bogus_length, "Bogus length: %d", subopt_len);
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_SEC_DSS:
        if (subopt_len < 35) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_sec_dss, tvb, suboptoff, subopt_len, ENC_ASCII|ENC_NA);
        } else {
            expert_add_info_format(pinfo, vti, &ei_dhcpv6_bogus_length, "Bogus length: %d", subopt_len);
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_IETF_PROV_SRV:
        proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_prov_srv_type, tvb, suboptoff, 1, ENC_BIG_ENDIAN);
        type = tvb_get_guint8(tvb, suboptoff);

        /
        if (type == 0) {
            dhcpv6_domain(pkt_s_tree, vti, pinfo, hf_packetcable_cccV6_prov_srv_fqdn, tvb, suboptoff+1, subopt_len-1);

            /
        } else if (type == 1) {
            if ((subopt_len % 16) == 0) {
                for (i = 0; i < subopt_len/16; i++) {
                    proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_prov_srv_ipv6, tvb, suboptoff+1, 4, ENC_NA);
                    suboptoff += 16;
                }
            }
        } else {
            expert_add_info_format(pinfo, vti, &ei_dhcpv6_invalid_type, "Invalid type: %u (%u byte%s)",
                                   type, subopt_len, plurality(subopt_len, "", "s"));
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_IETF_AS_KRB:
        if (subopt_len == 12) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_as_krb_nominal_timeout, tvb, suboptoff, 4, ENC_BIG_ENDIAN);
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_as_krb_max_timeout, tvb, suboptoff+4, 4, ENC_BIG_ENDIAN);
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_as_krb_max_retry_count, tvb, suboptoff+8, 4, ENC_BIG_ENDIAN);
        } else {
            proto_item_append_text(vti, "Bogus length: %d", subopt_len);
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_IETF_AP_KRB:
        if (subopt_len == 12) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_ap_krb_nominal_timeout, tvb, suboptoff, 4, ENC_BIG_ENDIAN);
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_ap_krb_max_timeout, tvb, suboptoff+4, 4, ENC_BIG_ENDIAN);
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_ap_krb_max_retry_count, tvb, suboptoff+8, 4, ENC_BIG_ENDIAN);
        } else {
            proto_item_append_text(vti, "Bogus length: %d", subopt_len);
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_KRB_REALM:
        if (subopt_len > 0) {
            dhcpv6_domain(pkt_s_tree, vti, pinfo, hf_packetcable_cccV6_krb_realm, tvb, suboptoff, subopt_len);
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_TGT_FLAG:
        if (subopt_len == 1) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_tgt_flag, tvb, suboptoff, 1, ENC_BIG_ENDIAN);
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_tgt_flag_fetch, tvb, suboptoff, 1, ENC_BIG_ENDIAN);
        }
        else {
            expert_add_info_format(pinfo, vti, &ei_dhcpv6_bogus_length, "Bogus length: %d", subopt_len);
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_PROV_TIMER:
        if (subopt_len == 1) {
            ti = proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_prov_timer, tvb, suboptoff, 1, ENC_BIG_ENDIAN);
            if (tvb_get_guint8(tvb, suboptoff) > 30)
                expert_add_info(pinfo, ti, &ei_dhcpv6_invalid_time_value);
        }
        else {
            expert_add_info_format(pinfo, vti, &ei_dhcpv6_bogus_length, "Bogus length: %d", subopt_len);
        }
        suboptoff += subopt_len;
        break;
    case PKT_CCCV6_IETF_SEC_TKT:
        proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_sec_tcm, tvb, suboptoff, 2, ENC_BIG_ENDIAN);
        if (subopt_len == 2) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_sec_tcm_provisioning_server, tvb, suboptoff, 2, ENC_BIG_ENDIAN);
            proto_tree_add_item(pkt_s_tree, hf_packetcable_cccV6_sec_tcm_call_manager_server, tvb, suboptoff, 2, ENC_BIG_ENDIAN);
        } else {
            expert_add_info_format(pinfo, vti, &ei_dhcpv6_bogus_length, "Bogus length: %d", subopt_len);
        }
        suboptoff += subopt_len;
        break;
    default:
        suboptoff += subopt_len;
        break;
    }
    /
    return (suboptoff - optoff);
}