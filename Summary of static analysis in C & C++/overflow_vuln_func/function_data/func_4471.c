static av_always_inline void \
ff_vp9_##avg##_8tap_1d_##dir##_##sz##_##opt(uint8_t *dst, ptrdiff_t dst_stride, \
                                            const uint8_t *src, ptrdiff_t src_stride, \
                                            int h, const int8_t (*filter)[32]) \
{ \
    ff_vp9_##avg##_8tap_1d_##dir##_##hsz##_##opt(dst,       dst_stride, src, \
                                                 src_stride, h, filter); \
    ff_vp9_##avg##_8tap_1d_##dir##_##hsz##_##opt(dst + hsz, dst_stride, src + hsz, \
                                                 src_stride, h, filter); \
}
