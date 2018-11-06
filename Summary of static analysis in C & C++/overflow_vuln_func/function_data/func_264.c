static gboolean logcat_read_packet(struct logcat_phdr *logcat, FILE_T fh,
    struct wtap_pkthdr *phdr, Buffer *buf, int *err, gchar **err_info)
{
    gint                 bytes_read;
    gint                 packet_size;
    guint16              payload_length;
    guint                tmp[2];
    guint8              *pd;

    bytes_read = file_read(&tmp, 2, fh);
    if (bytes_read != 2) {
        *err = file_error(fh, err_info);
        if (*err == 0 && bytes_read != 0)
            *err = WTAP_ERR_SHORT_READ;
        return FALSE;
    }
    payload_length = pletoh16(tmp);

    if (logcat->version == 1) {
        packet_size = 5 * 4 + payload_length;
    } else if (logcat->version == 2) {
        packet_size = 6 * 4 + payload_length;
    } else {
        return FALSE;
    }

    buffer_assure_space(buf, packet_size);
    pd = buffer_start_ptr(buf);

    /
    memcpy(pd, tmp, 2);

    /
    bytes_read = file_read(pd + 2, packet_size - 2, fh);
    if (bytes_read != packet_size - 2) {
        *err = file_error(fh, err_info);
        if (*err == 0)
            *err = WTAP_ERR_SHORT_READ;
        return FALSE;
    }

    phdr->rec_type = REC_TYPE_PACKET;
    phdr->presence_flags = WTAP_HAS_TS;
    phdr->ts.secs = (time_t) pletoh32(pd + 12);
    phdr->ts.nsecs = (int) pletoh32(pd + 16);
    phdr->caplen = packet_size;
    phdr->len = packet_size;

    phdr->pseudo_header.logcat.version = logcat->version;

    return TRUE;
}
