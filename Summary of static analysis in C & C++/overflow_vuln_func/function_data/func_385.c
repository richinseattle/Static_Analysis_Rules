static guint get_write_list_chunk_count(tvbuff_t *tvb, guint offset)
{
    guint32 value_follows;
    guint num_chunks;

    num_chunks = 0;
    while (1) {
        value_follows = tvb_get_ntohl(tvb, offset);
        offset += 4;
        if (!value_follows)
            break;

        num_chunks++;
        offset += get_write_chunk_size(tvb, offset);
    }

   return num_chunks;
}
