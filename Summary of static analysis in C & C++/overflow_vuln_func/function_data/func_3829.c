static int asf_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    ASFContext *asf = s->priv_data;
    AVIOContext *pb = s->pb;
    ASFStream *stream;
    int64_t duration;
    AVCodecParameters *par;
    int64_t packet_st, pts;
    int start_sec, i;
    int flags = pkt->flags;
    uint64_t offset = avio_tell(pb);

    par  = s->streams[pkt->stream_index]->codecpar;
    stream = &asf->streams[pkt->stream_index];

    if (par->codec_type == AVMEDIA_TYPE_AUDIO)
        flags &= ~AV_PKT_FLAG_KEY;

    pts = (pkt->pts != AV_NOPTS_VALUE) ? pkt->pts : pkt->dts;
    assert(pts != AV_NOPTS_VALUE);
    duration      = pts * 10000;
    asf->duration = FFMAX(asf->duration, duration + pkt->duration * 10000);

    packet_st = asf->nb_packets;
    put_frame(s, stream, s->streams[pkt->stream_index],
              pkt->dts, pkt->data, pkt->size, flags);

    /
    if ((!asf->is_streamed) && (flags & AV_PKT_FLAG_KEY)) {
        start_sec = (int)(duration / INT64_C(10000000));
        if (start_sec != (int)(asf->last_indexed_pts / INT64_C(10000000))) {
            for (i = asf->nb_index_count; i < start_sec; i++) {
                if (i >= asf->nb_index_memory_alloc) {
                    int err;
                    asf->nb_index_memory_alloc += ASF_INDEX_BLOCK;
                    if ((err = av_reallocp_array(&asf->index_ptr,
                                                asf->nb_index_memory_alloc,
                                                sizeof(*asf->index_ptr))) < 0) {
                       asf->nb_index_memory_alloc = 0;
                       return err;
                   }
                }
                // store
                asf->index_ptr[i].packet_number = (uint32_t)packet_st;
                asf->index_ptr[i].packet_count  = (uint16_t)(asf->nb_packets - packet_st);
                asf->index_ptr[i].send_time     = start_sec * INT64_C(10000000);
                asf->index_ptr[i].offset        = offset;
                asf->maximum_packet             = FFMAX(asf->maximum_packet,
                                                        (uint16_t)(asf->nb_packets - packet_st));
            }
            asf->nb_index_count   = start_sec;
            asf->last_indexed_pts = duration;
        }
    }
    return 0;
}