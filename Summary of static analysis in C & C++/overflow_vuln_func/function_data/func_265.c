static gboolean logcat_dump_text(wtap_dumper *wdh,
    const struct wtap_pkthdr *phdr,
    const guint8 *pd, int *err)
{
    gchar                          *buf;
    gint                            length;
    gchar                           priority;
    const gchar                    *tag;
    const gint                     *pid;
    const gint                     *tid;
    const gchar                    *log;
    gchar                          *log_part;
    const gchar                    *str_begin;
    const gchar                    *str_end;
    const guint32                  *datetime;
    const guint32                  *nanoseconds;
    const union wtap_pseudo_header *pseudo_header = &phdr->pseudo_header;
    const struct dumper_t          *dumper        = (const struct dumper_t *) wdh->priv;

    /
    if (phdr->rec_type != REC_TYPE_PACKET) {
        *err = WTAP_ERR_REC_TYPE_UNSUPPORTED;
        return FALSE;
    }

    if (pseudo_header->logcat.version == 1) {
        pid = (const gint *) (pd + 4);
        tid = (const gint *) (pd + 2 * 4);
        datetime = (const guint32 *) (pd + 3 * 4);
        nanoseconds = (const guint32 *) (pd + 4 * 4);
        priority = get_priority((const guint8 *) (pd + 5 * 4));
        tag = (const gchar *) (pd + 5 * 4 + 1);
        log = tag + strlen(tag) + 1;
    } else if (pseudo_header->logcat.version == 2) {
        pid = (const gint *) (pd + 4);
        tid = (const gint *) (pd + 2 * 4);
        datetime = (const guint32 *) (pd + 3 * 4);
        nanoseconds = (const guint32 *) (pd + 4 * 4);
        priority = get_priority((const guint8 *) (pd + 6 * 4));
        tag = (const char *) (pd + 6 * 4 + 1);
        log = tag + strlen(tag) + 1;
    } else {
        *err = WTAP_ERR_UNSUPPORTED;
        return FALSE;
    }

    str_begin = str_end = log;
    while (dumper->type != DUMP_LONG && (str_end = strchr(str_begin, '\n'))) {
        log_part = (gchar *) g_malloc(str_end - str_begin + 1);
        g_strlcpy(log_part, str_begin, str_end - str_begin + 1);

        str_begin = str_end + 1;

        buf = logcat_log(dumper, *datetime, *nanoseconds / 1000000, *pid, *tid,
                priority, tag, log_part);
        if (!buf) {
            g_free(log_part);
            return FALSE;
        }
        g_free(log_part);
        length = (guint32)strlen(buf);

        if (!wtap_dump_file_write(wdh, buf, length, err)) {
            g_free(buf);
            return FALSE;
        }

        wdh->bytes_dumped += length;

        g_free(buf);
    }

    if (*str_begin != '\0') {
        log_part = (gchar *) g_malloc(strlen(str_begin) + 1);
        g_strlcpy(log_part, str_begin, strlen(str_begin) + 1);

        buf = logcat_log(dumper, *datetime, *nanoseconds / 1000000, *pid, *tid,
                priority, tag, log_part);
        if (!buf) {
            g_free(log_part);
            return FALSE;
        }
        g_free(log_part);
        length = (guint32)strlen(buf);

        if (!wtap_dump_file_write(wdh, buf, length, err)) {
            g_free(buf);
            return FALSE;
        }

        wdh->bytes_dumped += length;
        g_free(buf);
    }

    return TRUE;
}
