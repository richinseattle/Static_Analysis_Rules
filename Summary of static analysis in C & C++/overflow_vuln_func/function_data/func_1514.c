void
proto_register_mmse(void)
{
    /
    static hf_register_info hf[] = {
        {   &hf_mmse_message_type,
            {   "X-Mms-Message-Type", "mmse.message_type",
                FT_UINT8, BASE_HEX, VALS(vals_message_type), 0x00,
                "Specifies the transaction type. Effectively defines PDU.",
                HFILL
            }
        },
        {   &hf_mmse_transaction_id,
            {   "X-Mms-Transaction-ID", "mmse.transaction_id",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "A unique identifier for this transaction. Identifies request and corresponding response only.",
                HFILL
            }
        },
        {   &hf_mmse_mms_version,
            {   "X-Mms-MMS-Version", "mmse.mms_version",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Version of the protocol used.",
                HFILL
            }
        },
        {   &hf_mmse_bcc,
            {   "Bcc", "mmse.bcc",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Blind carbon copy.",
                HFILL
            }
        },
        {   &hf_mmse_cc,
            {   "Cc", "mmse.cc",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Carbon copy.",
                HFILL
            }
        },
        {   &hf_mmse_content_location,
            {   "X-Mms-Content-Location", "mmse.content_location",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Defines the location of the message.",
                HFILL
            }
        },
        {   &hf_mmse_date,
            {   "Date", "mmse.date",
                FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0x00,
                "Arrival timestamp of the message or sending timestamp.",
                HFILL
            }
        },
        {   &hf_mmse_delivery_report,
            {   "X-Mms-Delivery-Report", "mmse.delivery_report",
                FT_UINT8, BASE_HEX, VALS(vals_yes_no), 0x00,
                "Whether a report of message delivery is wanted or not.",
                HFILL
            }
        },
        {   &hf_mmse_delivery_time_abs,
            {   "X-Mms-Delivery-Time", "mmse.delivery_time.abs",
                FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0x00,
                "The time at which message delivery is desired.",
                HFILL
            }
        },
        {   &hf_mmse_delivery_time_rel,
            {   "X-Mms-Delivery-Time", "mmse.delivery_time.rel",
                FT_RELATIVE_TIME, BASE_NONE, NULL, 0x00,
                "The desired message delivery delay.",
                HFILL
            }
        },
        {   &hf_mmse_expiry_abs,
            {   "X-Mms-Expiry", "mmse.expiry.abs",
                FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0x00,
                "Time when message expires and need not be delivered anymore.",
                HFILL
            }
        },
        {   &hf_mmse_expiry_rel,
            {   "X-Mms-Expiry", "mmse.expiry.rel",
                FT_RELATIVE_TIME, BASE_NONE, NULL, 0x00,
                "Delay before message expires and need not be delivered anymore.",
                HFILL
            }
        },
        {   &hf_mmse_from,
            {   "From", "mmse.from",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Address of the message sender.",
                HFILL
            }
        },
        {   &hf_mmse_message_class_id,
            {   "X-Mms-Message-Class", "mmse.message_class.id",
                FT_UINT8, BASE_HEX, VALS(vals_message_class), 0x00,
                "Of what category is the message.",
                HFILL
            }
        },
        {   &hf_mmse_message_class_str,
            {   "X-Mms-Message-Class", "mmse.message_class.str",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Of what category is the message.",
                HFILL
            }
        },
        {   &hf_mmse_message_id,
            {   "Message-Id", "mmse.message_id",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Unique identification of the message.",
                HFILL
            }
        },
        {   &hf_mmse_message_size,
            {   "X-Mms-Message-Size", "mmse.message_size",
                FT_UINT32, BASE_DEC, NULL, 0x00,
                "The size of the message in octets.",
                HFILL
            }
        },
        {   &hf_mmse_priority,
            {   "X-Mms-Priority", "mmse.priority",
                FT_UINT8, BASE_HEX, VALS(vals_priority), 0x00,
                "Priority of the message.",
                HFILL
            }
        },
        {   &hf_mmse_read_reply,
            {   "X-Mms-Read-Reply", "mmse.read_reply",
                FT_UINT8, BASE_HEX, VALS(vals_yes_no), 0x00,
                "Whether a read report from every recipient is wanted.",
                HFILL
            }
        },
        {   &hf_mmse_read_report,
            {   "X-Mms-Read-Report", "mmse.read_report",
                FT_UINT8, BASE_HEX, VALS(vals_yes_no), 0x00,
                "Whether a read report from every recipient is wanted.",
                HFILL
            }
        },
        {   &hf_mmse_report_allowed,
            {   "X-Mms-Report-Allowed", "mmse.report_allowed",
                FT_UINT8, BASE_HEX, VALS(vals_yes_no), 0x00,
                "Sending of delivery report allowed or not.",
                HFILL
            }
        },
        {   &hf_mmse_response_status,
            {   "Response-Status", "mmse.response_status",
                FT_UINT8, BASE_HEX, VALS(vals_response_status), 0x00,
                "MMS-specific result of a message submission or retrieval.",
                HFILL
            }
        },
        {   &hf_mmse_response_text,
            {   "Response-Text", "mmse.response_text",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Additional information on MMS-specific result.",
                HFILL
            }
        },
        {   &hf_mmse_sender_visibility,
            {   "Sender-Visibility", "mmse.sender_visibility",
                FT_UINT8, BASE_HEX, VALS(vals_sender_visibility), 0x00,
                "Disclose sender identity to receiver or not.",
                HFILL
            }
        },
        {   &hf_mmse_status,
            {   "Status", "mmse.status",
                FT_UINT8, BASE_HEX, VALS(vals_message_status), 0x00,
                "Current status of the message.",
                HFILL
            }
        },
        {   &hf_mmse_subject,
            {   "Subject", "mmse.subject",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Subject of the message.",
                HFILL
            }
        },
        {   &hf_mmse_to,
            {   "To", "mmse.to",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Recipient(s) of the message.",
                HFILL
            }
        },
#if 0
        {   &hf_mmse_content_type,
            {   "Data", "mmse.content_type",
                FT_NONE, BASE_NONE, NULL, 0x00,
                "Media content of the message.",
                HFILL
            }
        },
#endif
        {   &hf_mmse_ffheader,
            {   "Free format (not encoded) header", "mmse.ffheader",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Application header without corresponding encoding.",
                HFILL
            }
        },
        /
        {   &hf_mmse_retrieve_status,
            {   "X-Mms-Retrieve-Status", "mmse.retrieve_status",
                FT_UINT8, BASE_HEX, VALS(vals_retrieve_status), 0x00,
                "MMS-specific result of a message retrieval.",
                HFILL
            }
        },
        {   &hf_mmse_retrieve_text,
            {   "X-Mms-Retrieve-Text", "mmse.retrieve_text",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Status text of a MMS message retrieval.",
                HFILL
            }
        },
        {   &hf_mmse_read_status,
            {   "X-Mms-Read-Status", "mmse.read_status",
                FT_UINT8, BASE_HEX, VALS(vals_read_status), 0x00,
                "MMS-specific message read status.",
                HFILL
            }
        },
        {   &hf_mmse_reply_charging,
            {   "X-Mms-Reply-Charging", "mmse.reply_charging",
                FT_UINT8, BASE_HEX, VALS(vals_reply_charging), 0x00,
                "MMS-specific message reply charging method.",
                HFILL
            }
        },
        {   &hf_mmse_reply_charging_deadline_abs,
            {   "X-Mms-Reply-Charging-Deadline", "mmse.reply_charging_deadline.abs",
                FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0x00,
                "The latest time of the recipient(s) to submit the Reply MM.",
                HFILL
            }
        },
        {   &hf_mmse_reply_charging_deadline_rel,
            {   "X-Mms-Reply-Charging-Deadline", "mmse.reply_charging_deadline.rel",
                FT_RELATIVE_TIME, BASE_NONE, NULL, 0x00,
                "The latest time of the recipient(s) to submit the Reply MM.",
                HFILL
            }
        },
        {   &hf_mmse_reply_charging_id,
            {   "X-Mms-Reply-Charging-Id", "mmse.reply_charging_id",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Unique reply charging identification of the message.",
                HFILL
            }
        },
        {   &hf_mmse_reply_charging_size,
            {   "X-Mms-Reply-Charging-Size", "mmse.reply_charging_size",
                FT_UINT32, BASE_DEC, NULL, 0x00,
                "The size of the reply charging in octets.",
                HFILL
            }
        },
        {   &hf_mmse_prev_sent_by,
            {   "X-Mms-Previously-Sent-By", "mmse.previously_sent_by",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Indicates that the MM has been previously sent by this user.",
                HFILL
            }
        },
        {   &hf_mmse_prev_sent_by_fwd_count,
            {   "Forward Count", "mmse.previously_sent_by.forward_count",
                FT_UINT32, BASE_DEC, NULL, 0x00,
                "Forward count of the previously sent MM.",
                HFILL
            }
        },
        {   &hf_mmse_prev_sent_by_address,
            {   "Address", "mmse.previously_sent_by.address",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Indicates from whom the MM has been previously sent.",
                HFILL
            }
        },
        {   &hf_mmse_prev_sent_date,
            {   "X-Mms-Previously-Sent-Date", "mmse.previously_sent_date",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Indicates the date that the MM has been previously sent.",
                HFILL
            }
        },
        {   &hf_mmse_prev_sent_date_fwd_count,
            {   "Forward Count", "mmse.previously_sent_date.forward_count",
                FT_UINT32, BASE_DEC, NULL, 0x00,
                "Forward count of the previously sent MM.",
                HFILL
            }
        },
        {   &hf_mmse_prev_sent_date_date,
            {   "Date", "mmse.previously_sent_date.date",
                FT_STRING, BASE_NONE, NULL, 0x00,
                "Time when the MM has been previously sent.",
                HFILL
            }
        },
        {   &hf_mmse_header_uint,
            {   "Header Uint Value", "mmse.header.uint",
                FT_UINT8, BASE_DEC, NULL, 0x00, NULL, HFILL
            }
        },
        {   &hf_mmse_header_string,
            {   "Header String Value", "mmse.header.string",
                FT_STRING, BASE_NONE, NULL, 0x00, NULL, HFILL
            }
        },
        {   &hf_mmse_header_bytes,
            {   "Header Byte array", "mmse.header.bytes",
                FT_BYTES, BASE_NONE, NULL, 0x00, NULL, HFILL
            }
        },


    };
    /
    static gint *ett[] = {
        &ett_mmse,
        &ett_mmse_hdr_details,
    };

    /
    proto_mmse = proto_register_protocol("MMS Message Encapsulation",
                                         "MMSE", "mmse");

    /
    proto_register_field_array(proto_mmse, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));
}
