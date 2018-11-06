static CryptoDevBackendSymOpInfo *
virtio_crypto_sym_op_helper(VirtIODevice *vdev,
           struct virtio_crypto_cipher_para *cipher_para,
           struct virtio_crypto_alg_chain_data_para *alg_chain_para,
           struct iovec *iov, unsigned int out_num)
{
    VirtIOCrypto *vcrypto = VIRTIO_CRYPTO(vdev);
    CryptoDevBackendSymOpInfo *op_info;
    uint32_t src_len = 0, dst_len = 0;
    uint32_t iv_len = 0;
    uint32_t aad_len = 0, hash_result_len = 0;
    uint32_t hash_start_src_offset = 0, len_to_hash = 0;
    uint32_t cipher_start_src_offset = 0, len_to_cipher = 0;

    size_t max_len, curr_size = 0;
    size_t s;

    /
    if (cipher_para) {
        iv_len = ldl_le_p(&cipher_para->iv_len);
        src_len = ldl_le_p(&cipher_para->src_data_len);
        dst_len = ldl_le_p(&cipher_para->dst_data_len);
    } else if (alg_chain_para) { /
        iv_len = ldl_le_p(&alg_chain_para->iv_len);
        src_len = ldl_le_p(&alg_chain_para->src_data_len);
        dst_len = ldl_le_p(&alg_chain_para->dst_data_len);

        aad_len = ldl_le_p(&alg_chain_para->aad_len);
        hash_result_len = ldl_le_p(&alg_chain_para->hash_result_len);
        hash_start_src_offset = ldl_le_p(
                         &alg_chain_para->hash_start_src_offset);
        cipher_start_src_offset = ldl_le_p(
                         &alg_chain_para->cipher_start_src_offset);
        len_to_cipher = ldl_le_p(&alg_chain_para->len_to_cipher);
        len_to_hash = ldl_le_p(&alg_chain_para->len_to_hash);
    } else {
        return NULL;
    }

    max_len = iv_len + aad_len + src_len + dst_len + hash_result_len;
    if (unlikely(max_len > vcrypto->conf.max_size)) {
        virtio_error(vdev, "virtio-crypto too big length");
        return NULL;
    }

    op_info = g_malloc0(sizeof(CryptoDevBackendSymOpInfo) + max_len);
    op_info->iv_len = iv_len;
    op_info->src_len = src_len;
    op_info->dst_len = dst_len;
    op_info->aad_len = aad_len;
    op_info->digest_result_len = hash_result_len;
    op_info->hash_start_src_offset = hash_start_src_offset;
    op_info->len_to_hash = len_to_hash;
    op_info->cipher_start_src_offset = cipher_start_src_offset;
    op_info->len_to_cipher = len_to_cipher;
    /
    if (op_info->iv_len > 0) {
        DPRINTF("iv_len=%" PRIu32 "\n", op_info->iv_len);
        op_info->iv = op_info->data + curr_size;

        s = iov_to_buf(iov, out_num, 0, op_info->iv, op_info->iv_len);
        if (unlikely(s != op_info->iv_len)) {
            virtio_error(vdev, "virtio-crypto iv incorrect");
            goto err;
        }
        iov_discard_front(&iov, &out_num, op_info->iv_len);
        curr_size += op_info->iv_len;
    }

    /
    if (op_info->aad_len > 0) {
        DPRINTF("aad_len=%" PRIu32 "\n", op_info->aad_len);
        op_info->aad_data = op_info->data + curr_size;

        s = iov_to_buf(iov, out_num, 0, op_info->aad_data, op_info->aad_len);
        if (unlikely(s != op_info->aad_len)) {
            virtio_error(vdev, "virtio-crypto additional auth data incorrect");
            goto err;
        }
        iov_discard_front(&iov, &out_num, op_info->aad_len);

        curr_size += op_info->aad_len;
    }

    /
    if (op_info->src_len > 0) {
        DPRINTF("src_len=%" PRIu32 "\n", op_info->src_len);
        op_info->src = op_info->data + curr_size;

        s = iov_to_buf(iov, out_num, 0, op_info->src, op_info->src_len);
        if (unlikely(s != op_info->src_len)) {
            virtio_error(vdev, "virtio-crypto source data incorrect");
            goto err;
        }
        iov_discard_front(&iov, &out_num, op_info->src_len);

        curr_size += op_info->src_len;
    }

    /
    op_info->dst = op_info->data + curr_size;
    curr_size += op_info->dst_len;

    DPRINTF("dst_len=%" PRIu32 "\n", op_info->dst_len);

    /
    if (hash_result_len > 0) {
        DPRINTF("hash_result_len=%" PRIu32 "\n", hash_result_len);
        op_info->digest_result = op_info->data + curr_size;
    }

    return op_info;

err:
    g_free(op_info);
    return NULL;
}
