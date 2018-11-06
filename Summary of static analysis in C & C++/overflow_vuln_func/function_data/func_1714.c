void
dissect_isup_called_party_number_parameter(tvbuff_t *parameter_tvb, proto_tree *parameter_tree, proto_item *parameter_item)
{
  proto_item *address_digits_item;
  proto_tree *address_digits_tree;
  guint8 indicators1, indicators2;
  guint8 address_digit_pair=0;
  gint offset=0;
  gint i=0;
  gint length;
  char called_number[MAXDIGITS + 1]="";
  e164_info_t e164_info;
  gint number_plan;

  indicators1 = tvb_get_guint8(parameter_tvb, 0);
  proto_tree_add_boolean(parameter_tree, hf_isup_odd_even_indicator, parameter_tvb, 0, 1, indicators1);
  proto_tree_add_uint(parameter_tree, hf_isup_called_party_nature_of_address_indicator, parameter_tvb, 0, 1, indicators1);
  indicators2 = tvb_get_guint8(parameter_tvb, 1);
  number_plan = (indicators2 & 0x70)>> 4;
  proto_tree_add_boolean(parameter_tree, hf_isup_inn_indicator, parameter_tvb, 1, 1, indicators2);
  proto_tree_add_uint(parameter_tree, hf_isup_numbering_plan_indicator, parameter_tvb, 1, 1, indicators2);
  offset = 2;

  address_digits_item = proto_tree_add_text(parameter_tree, parameter_tvb,
					    offset, -1,
					    "Called Party Number");
  address_digits_tree = proto_item_add_subtree(address_digits_item, ett_isup_address_digits);

  while((length = tvb_reported_length_remaining(parameter_tvb, offset)) > 0){
	  address_digit_pair = tvb_get_guint8(parameter_tvb, offset);
	  proto_tree_add_uint(address_digits_tree, hf_isup_called_party_odd_address_signal_digit, parameter_tvb, offset, 1, address_digit_pair);
	  called_number[i++] = number_to_char(address_digit_pair & ISUP_ODD_ADDRESS_SIGNAL_DIGIT_MASK);
		if (i > MAXDIGITS)
			THROW(ReportedBoundsError);
		if ((length - 1) > 0 ){
			proto_tree_add_uint(address_digits_tree, hf_isup_called_party_even_address_signal_digit, parameter_tvb, offset, 1, address_digit_pair);
			called_number[i++] = number_to_char((address_digit_pair & ISUP_EVEN_ADDRESS_SIGNAL_DIGIT_MASK) / 0x10);
			if (i > MAXDIGITS)
				THROW(ReportedBoundsError);
			}
		offset++;
		}
  if  (((indicators1 & 0x80) == 0) && (tvb_length(parameter_tvb) > 0)){ /
		proto_tree_add_uint(address_digits_tree, hf_isup_called_party_even_address_signal_digit, parameter_tvb, offset - 1, 1, address_digit_pair);
		called_number[i++] = number_to_char((address_digit_pair & ISUP_EVEN_ADDRESS_SIGNAL_DIGIT_MASK) / 0x10);
		if (i > MAXDIGITS)
			THROW(ReportedBoundsError);
  }

  called_number[i++] = '\0';
  proto_item_set_text(address_digits_item, "Called Party Number: %s", called_number);
  proto_item_set_text(parameter_item, "Called Party Number: %s", called_number);
  if ( number_plan == 1 ) {
		e164_info.e164_number_type = CALLED_PARTY_NUMBER;
		e164_info.nature_of_address = indicators1 & 0x7f;
		e164_info.E164_number_str = called_number;
		e164_info.E164_number_length = i - 1;
		dissect_e164_number(parameter_tvb, address_digits_tree, 2, (offset - 2), e164_info);
		proto_tree_add_string_hidden(address_digits_tree, hf_isup_called, parameter_tvb,
		offset - length, length, called_number);
  } else {
		proto_tree_add_string(address_digits_tree, hf_isup_called, parameter_tvb, 
			offset - length, length, called_number);
  }
  tap_called_number = ep_strdup(called_number);
}