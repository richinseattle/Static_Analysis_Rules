static int qcow_open(BlockDriverState *bs, QDict *options, int flags,
                     Error **errp)
{
    BDRVQcowState *s = bs->opaque;
    unsigned int len, i, shift;
    int ret;
    QCowHeader header;

    ret = bdrv_pread(bs->file, 0, &header, sizeof(header));
    if (ret < 0) {
        goto fail;
    }
    be32_to_cpus(&header.magic);
    be32_to_cpus(&header.version);
    be64_to_cpus(&header.backing_file_offset);
    be32_to_cpus(&header.backing_file_size);
    be32_to_cpus(&header.mtime);
    be64_to_cpus(&header.size);
    be32_to_cpus(&header.crypt_method);
    be64_to_cpus(&header.l1_table_offset);

    if (header.magic != QCOW_MAGIC) {
        error_setg(errp, "Image not in qcow format");
        ret = -EINVAL;
        goto fail;
    }
    if (header.version != QCOW_VERSION) {
        char version[64];
        snprintf(version, sizeof(version), "QCOW version %" PRIu32,
                 header.version);
        error_set(errp, QERR_UNKNOWN_BLOCK_FORMAT_FEATURE,
                  bs->device_name, "qcow", version);
        ret = -ENOTSUP;
        goto fail;
    }

    if (header.size <= 1) {
        error_setg(errp, "Image size is too small (must be at least 2 bytes)");
        ret = -EINVAL;
        goto fail;
    }
    if (header.cluster_bits < 9 || header.cluster_bits > 16) {
        error_setg(errp, "Cluster size must be between 512 and 64k");
        ret = -EINVAL;
        goto fail;
    }

    /
    if (header.l2_bits < 9 - 3 || header.l2_bits > 16 - 3) {
        error_setg(errp, "L2 table size must be between 512 and 64k");
        ret = -EINVAL;
        goto fail;
    }

    if (header.crypt_method > QCOW_CRYPT_AES) {
        error_setg(errp, "invalid encryption method in qcow header");
        ret = -EINVAL;
        goto fail;
    }
    s->crypt_method_header = header.crypt_method;
    if (s->crypt_method_header) {
        bs->encrypted = 1;
    }
    s->cluster_bits = header.cluster_bits;
    s->cluster_size = 1 << s->cluster_bits;
    s->cluster_sectors = 1 << (s->cluster_bits - 9);
    s->l2_bits = header.l2_bits;
    s->l2_size = 1 << s->l2_bits;
    bs->total_sectors = header.size / 512;
    s->cluster_offset_mask = (1LL << (63 - s->cluster_bits)) - 1;

    /
    shift = s->cluster_bits + s->l2_bits;
    if (header.size > UINT64_MAX - (1LL << shift)) {
        error_setg(errp, "Image too large");
        ret = -EINVAL;
        goto fail;
    } else {
        uint64_t l1_size = (header.size + (1LL << shift) - 1) >> shift;
        if (l1_size > INT_MAX / sizeof(uint64_t)) {
            error_setg(errp, "Image too large");
            ret = -EINVAL;
            goto fail;
        }
        s->l1_size = l1_size;
    }

    s->l1_table_offset = header.l1_table_offset;
    s->l1_table = g_try_malloc(s->l1_size * sizeof(uint64_t));
    if (s->l1_table == NULL) {
        error_setg(errp, "Could not allocate memory for L1 table");
        ret = -ENOMEM;
        goto fail;
    }

    ret = bdrv_pread(bs->file, s->l1_table_offset, s->l1_table,
               s->l1_size * sizeof(uint64_t));
    if (ret < 0) {
        goto fail;
    }

    for(i = 0;i < s->l1_size; i++) {
        be64_to_cpus(&s->l1_table[i]);
    }

    /
    s->l2_cache =
        qemu_try_blockalign(bs->file,
                            s->l2_size * L2_CACHE_SIZE * sizeof(uint64_t));
    if (s->l2_cache == NULL) {
        error_setg(errp, "Could not allocate L2 table cache");
        ret = -ENOMEM;
        goto fail;
    }
    s->cluster_cache = g_malloc(s->cluster_size);
    s->cluster_data = g_malloc(s->cluster_size);
    s->cluster_cache_offset = -1;

    /
    if (header.backing_file_offset != 0) {
        len = header.backing_file_size;
        if (len > 1023) {
            error_setg(errp, "Backing file name too long");
            ret = -EINVAL;
            goto fail;
        }
        ret = bdrv_pread(bs->file, header.backing_file_offset,
                   bs->backing_file, len);
        if (ret < 0) {
            goto fail;
        }
        bs->backing_file[len] = '\0';
    }

    /
    error_set(&s->migration_blocker,
              QERR_BLOCK_FORMAT_FEATURE_NOT_SUPPORTED,
              "qcow", bs->device_name, "live migration");
    migrate_add_blocker(s->migration_blocker);

    qemu_co_mutex_init(&s->lock);
    return 0;

 fail:
    g_free(s->l1_table);
    qemu_vfree(s->l2_cache);
    g_free(s->cluster_cache);
    g_free(s->cluster_data);
    return ret;
}