static int
dissect_packetcable_ccc_option(proto_tree *v_tree, proto_item *v_item, packet_info *pinfo, tvbuff_t *tvb, int optoff,
                               int optend)
{
    /
    int         suboptoff = optoff;
    guint16     subopt, subopt_len;
    proto_item *vti;
    proto_tree *pkt_s_tree;

    subopt = tvb_get_ntohs(tvb, optoff);
    suboptoff += 2;

    subopt_len = tvb_get_ntohs(tvb, suboptoff);
    suboptoff += 2;

    /
    if (optend <= 0) {
        expert_add_info_format(pinfo, v_item, &ei_dhcpv6_no_suboption_len, "Sub element %d: no room left in option for suboption length", subopt);
        return (optend);
    }
    /

    vti = proto_tree_add_item(v_tree, hf_packetcable_ccc_suboption, tvb, optoff, 2, ENC_BIG_ENDIAN);
    pkt_s_tree = proto_item_add_subtree(vti, ett_dhcpv6_pkt_option);

    switch (subopt) {
    case PKT_CCC_PRI_DHCP:      /
        if (subopt_len == 4) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_ccc_pri_dhcp, tvb, suboptoff, 4, ENC_BIG_ENDIAN);
        }
        else {
            expert_add_info_format(pinfo, vti, &ei_dhcpv6_bogus_length, "Bogus length: %d", subopt_len);
        }

        suboptoff += subopt_len;
        break;
    case PKT_CCC_SEC_DHCP:
        if (subopt_len == 4) {
            proto_tree_add_item(pkt_s_tree, hf_packetcable_ccc_sec_dhcp, tvb, suboptoff, 4, ENC_BIG_ENDIAN);
        }
        else {
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
