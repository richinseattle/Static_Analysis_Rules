static int mpegvideo_probe(AVProbeData *p)
{
    uint32_t code= -1;
    int pic=0, seq=0, slice=0, pspack=0, vpes=0, apes=0, res=0, sicle=0;
    const uint8_t *ptr = p->buf, *end = ptr + p->buf_size;
    uint32_t last = 0;
    int j;

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &code);
        if ((code & 0xffffff00) == 0x100) {
            switch(code){
            case     SEQ_START_CODE:
                if (!(ptr[3 + 1 + 2] & 0x20))
                    break;
                j = -1;
                if (ptr[j + 8] & 2)
                    j+= 64;
                if (ptr + j >= end)
                    break;
                if (ptr[j + 8] & 1)
                    j+= 64;
                if (ptr + j >= end)
                    break;
                if (AV_RB24(ptr + j + 9) & 0xFFFFFE)
                    break;
                seq++;
            break;
            case PICTURE_START_CODE:   pic++; break;
            case    PACK_START_CODE: pspack++; break;
            case              0x1b6:
                                        res++; break;
            }
            if (code >= SLICE_START_CODE && code <= 0x1af) {
                if (last >= SLICE_START_CODE && last <= 0x1af) {
                    if (code >= last) slice++;
                    else              sicle++;
                }else{
                    if (code == SLICE_START_CODE) slice++;
                    else                          sicle++;
                }
            }
            if     ((code & 0x1f0) == VIDEO_ID)   vpes++;
            else if((code & 0x1e0) == AUDIO_ID)   apes++;
            last = code;
        }
    }
    if(seq && seq*9<=pic*10 && pic*9<=slice*10 && !pspack && !apes && !res && slice > sicle) {
        if(vpes) return AVPROBE_SCORE_EXTENSION / 4;
        else     return pic>1 ? AVPROBE_SCORE_EXTENSION + 1 : AVPROBE_SCORE_EXTENSION / 2; // +1 for .mpg
    }
    return 0;
}
