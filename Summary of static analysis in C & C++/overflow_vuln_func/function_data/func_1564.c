static void dissect_r3_upstreamfields (tvbuff_t *tvb, guint32 start_offset _U_, guint32 length, packet_info *pinfo, proto_tree *tree)
{
  guint32 offset = 0;

  while (offset < tvb_reported_length (tvb))
  {
    guint32 fieldLength = tvb_get_guint8 (tvb, offset + 0);
    guint32 fieldType = tvb_get_guint8 (tvb, offset + 1);
    guint32 dataLength = fieldLength - 2;
    proto_item *upstreamfield_item = NULL;
    proto_item *upstreamfield_length = NULL;
    proto_tree *upstreamfield_tree = NULL;
    const gchar *usfn = NULL;

    usfn = val_to_str_ext_const (fieldType, &r3_upstreamfieldnames_ext, "[Unknown Field]");

    upstreamfield_item = proto_tree_add_none_format (tree, hf_r3_upstreamfield, tvb, offset + 0, fieldLength, "Upstream Field: %s (%u)", usfn, fieldType);
    upstreamfield_tree = proto_item_add_subtree (upstreamfield_item, ett_r3upstreamfield);

    upstreamfield_length = proto_tree_add_item (upstreamfield_tree, hf_r3_upstreamfieldlength, tvb, offset + 0, 1, ENC_LITTLE_ENDIAN);
    proto_tree_add_item (upstreamfield_tree, hf_r3_upstreamfieldtype, tvb, offset + 1, 1, ENC_LITTLE_ENDIAN);

    if (fieldLength < 2)
    {
      dataLength = 0;
      expert_add_info_format (pinfo, upstreamfield_length, PI_UNDECODED, PI_WARN, "Malformed length value -- all fields are at least 2 octets.");
    }

    offset += 2;

    switch (fieldType)
    {
      /
      case UPSTREAMFIELD_NOTUSED :
      case UPSTREAMFIELD_PRIMARYPIN :
      case UPSTREAMFIELD_AUXPIN :
      case UPSTREAMFIELD_ACCESSALWAYS :
      case UPSTREAMFIELD_CACHED :
      case UPSTREAMFIELD_ENTRYDEVICE :
      case UPSTREAMFIELD_PPMIFIELDTYPE :
      case UPSTREAMFIELD_RESPONSEWINDOW :
      case UPSTREAMFIELD_USERTYPE :
      case UPSTREAMFIELD_PRIMARYFIELDTYPE :
      case UPSTREAMFIELD_AUXFIELDTYPE :
      case UPSTREAMFIELD_ACCESSMODE :
      case UPSTREAMFIELD_USECOUNT :
      case UPSTREAMFIELD_EXCEPTIONGROUP :
      case UPSTREAMFIELD_NAR :
      case UPSTREAMFIELD_SEQUENCENUMBER :
      case UPSTREAMFIELD_USERNUMBER :
      case UPSTREAMFIELD_EVENTLOGRECORDCOUNT :
      case UPSTREAMFIELD_DECLINEDRECORDCOUNT :
      case UPSTREAMFIELD_ALARMRECORDCOUNT :
        proto_tree_add_item (upstreamfield_tree, hf_r3_upstreamfieldarray [fieldType], tvb, offset, dataLength, ENC_LITTLE_ENDIAN);
        break;

      /
      case UPSTREAMFIELD_PIN :
      case UPSTREAMFIELD_VERSION :
      case UPSTREAMFIELD_AUXCTLRVERSION :
        proto_tree_add_item (upstreamfield_tree, hf_r3_upstreamfieldarray [fieldType], tvb, offset, dataLength, ENC_ASCII|ENC_NA);
        break;

      /
      case UPSTREAMFIELD_SERIALNUMBER :
        {
          tvbuff_t *sn_tvb = tvb_new_subset (tvb, offset, dataLength, dataLength);

          dissect_serialnumber (sn_tvb, 0, length, pinfo, upstreamfield_tree, hf_r3_upstreamfieldarray [fieldType]);
        }
        break;

      case UPSTREAMFIELD_EVENTLOGRECORD :
        {
          proto_item *eventlog_item = NULL;
          proto_tree *eventlog_tree = NULL;

          if (dataLength != 9)
            expert_add_info_format (pinfo, tree, PI_UNDECODED, PI_WARN, "Malformed event log field -- expected 9 octets");
          else
          {
            eventlog_item = proto_tree_add_text (upstreamfield_tree, tvb, offset, 9, "Event Log Record");
            eventlog_tree = proto_item_add_subtree (eventlog_item, ett_r3eventlogrecord);

            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_year, tvb, offset + 0, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_month, tvb, offset + 1, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_day, tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_hour, tvb, offset + 3, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_minute, tvb, offset + 4, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_second, tvb, offset + 5, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_usernumber, tvb, offset + 6, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (eventlog_tree, hf_r3_eventlog_event, tvb, offset + 8, 1, ENC_LITTLE_ENDIAN);
          }
        }
        break;

      case UPSTREAMFIELD_DATETIME :
        {
          proto_item *datetime_item = NULL;
          proto_tree *datetime_tree = NULL;

          if (dataLength != 8)
            expert_add_info_format (pinfo, tree, PI_UNDECODED, PI_WARN, "Malformed date/time field -- expected 8 octets");
          else
          {
            datetime_item = proto_tree_add_text (upstreamfield_tree, tvb, offset, 8, "Date/Time: %02u/%02u/%02u-%u %02u:%02u:%02u %u",
                tvb_get_guint8 (tvb, offset + 0), tvb_get_guint8 (tvb, offset + 1), tvb_get_guint8 (tvb, offset + 2), tvb_get_guint8 (tvb, offset + 3),
                tvb_get_guint8 (tvb, offset + 4), tvb_get_guint8 (tvb, offset + 5), tvb_get_guint8 (tvb, offset + 6), tvb_get_guint8 (tvb, offset + 7));
            datetime_tree = proto_item_add_subtree (datetime_item, ett_r3datetime);

            proto_tree_add_item (datetime_tree, hf_r3_datetime_year, tvb, offset + 0, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (datetime_tree, hf_r3_datetime_month, tvb, offset + 1, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (datetime_tree, hf_r3_datetime_day, tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (datetime_tree, hf_r3_datetime_dow, tvb, offset + 3, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (datetime_tree, hf_r3_datetime_hours, tvb, offset + 4, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (datetime_tree, hf_r3_datetime_minutes, tvb, offset + 5, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (datetime_tree, hf_r3_datetime_seconds, tvb, offset + 6, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (datetime_tree, hf_r3_datetime_dst, tvb, offset + 7, 1, ENC_LITTLE_ENDIAN);
          }
        }
        break;

      case UPSTREAMFIELD_DECLINEDRECORD :
        {
          proto_item *declinedlog_item = NULL;
          proto_tree *declinedlog_tree = NULL;
          guint8 cred1type = 0;
          guint8 cred2type = 0;

          if (dataLength != 49)
            expert_add_info_format (pinfo, tree, PI_UNDECODED, PI_WARN, "Malformed declined log field -- expected 49 octets");
          else
          {
            declinedlog_item = proto_tree_add_text (upstreamfield_tree, tvb, offset, 49, "Declined Log Record");
            declinedlog_tree = proto_item_add_subtree (declinedlog_item, ett_r3declinedlogrecord);

            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_year, tvb, offset + 0, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_month, tvb, offset + 1, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_day, tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_hour, tvb, offset + 3, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_minute, tvb, offset + 4, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_second, tvb, offset + 5, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_usernumber, tvb, offset + 6, 2, ENC_LITTLE_ENDIAN);

            cred1type = tvb_get_guint8 (tvb, offset + 8) & 0x07;
            cred2type = (tvb_get_guint8 (tvb, offset + 8) & 0x38) >> 3;

            proto_tree_add_uint (declinedlog_tree, hf_r3_declinedlog_cred1type, tvb, offset, 1, cred1type);
            proto_tree_add_uint (declinedlog_tree, hf_r3_declinedlog_cred2type, tvb, offset, 1, cred2type);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_cred1, tvb, offset + 9, 19, ENC_NA);
            proto_tree_add_item (declinedlog_tree, hf_r3_declinedlog_cred2, tvb, offset + 28, 19, ENC_NA);
          }
        }
        break;

      case UPSTREAMFIELD_EXPIREON :
        {
          proto_item *expireon_item = NULL;
          proto_tree *expireon_tree = NULL;

          if (dataLength != 3)
            expert_add_info_format (pinfo, tree, PI_UNDECODED, PI_WARN, "Malformed expiration field -- expected 3 octets");
          else
          {
            expireon_item = proto_tree_add_text (upstreamfield_tree, tvb, offset, 3, "Expire YY/MM/DD: %02u/%02u/%02u",
                tvb_get_guint8 (tvb, offset + 2), tvb_get_guint8 (tvb, offset + 0), tvb_get_guint8 (tvb, offset + 1));
            expireon_tree = proto_item_add_subtree (expireon_item, ett_r3expireon);

            proto_tree_add_item (expireon_tree, hf_r3_expireon_month, tvb, offset + 0, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (expireon_tree, hf_r3_expireon_day, tvb, offset + 1, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (expireon_tree, hf_r3_expireon_year, tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
          }
        }
        break;

      case UPSTREAMFIELD_TIMEZONE :
        {
          guint32 i;
          guint32 tz;
          proto_item *timezone_item = NULL;
          proto_tree *timezone_tree = NULL;

          if (dataLength != 4)
            expert_add_info_format (pinfo, tree, PI_UNDECODED, PI_WARN, "Malformed timezone field -- expected 4 octets");
          else
          {
            tz = tvb_get_letohl (tvb, offset);
            timezone_item = proto_tree_add_item (upstreamfield_tree, hf_r3_upstreamfieldarray [fieldType], tvb, offset, 4, ENC_LITTLE_ENDIAN);
            timezone_tree = proto_item_add_subtree (timezone_item, ett_r3timezone);

            for (i = 0; i < 32; i++)
              proto_tree_add_boolean (timezone_tree, hf_r3_timezonearray [i], tvb, offset, 4, tz);
          }
        }
        break;

      case UPSTREAMFIELD_ALARMRECORD :
        {
          proto_item *alarmlog_item = NULL;
          proto_tree *alarmlog_tree = NULL;

          alarmlog_item = proto_tree_add_text (upstreamfield_tree, tvb, offset, 9, "Alarm Record");
          alarmlog_tree = proto_item_add_subtree (alarmlog_item, ett_r3alarmlogrecord);

          if (dataLength != 9)
            expert_add_info_format (pinfo, tree, PI_UNDECODED, PI_WARN, "Malformed alarm log field -- expected 9 octets");
          else
          {
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_year, tvb, offset + 0, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_month, tvb, offset + 1, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_day, tvb, offset + 2, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_hour, tvb, offset + 3, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_minute, tvb, offset + 4, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_second, tvb, offset + 5, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_id, tvb, offset + 6, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item (alarmlog_tree, hf_r3_alarmlog_usernumber, tvb, offset + 7, 2, ENC_LITTLE_ENDIAN);
          }
        }
        break;

      default :
        proto_tree_add_none_format (upstreamfield_tree, hf_r3_upstreamfielderror, tvb, offset, dataLength, "Unknown Field Type");
        break;
    }

    offset += dataLength;
  }
}
