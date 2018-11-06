static float getRate( guint8 plcpType, guint8 mcsIndex, guint16 rflags, guint8 nss )
{
    /
    float canonical_rate_legacy[]  = {1.0f, 2.0f, 5.5f, 11.0f, 6.0f, 9.0f, 12.0f, 18.0f, 24.0f, 36.0f, 48.0f, 54.0f};

    int   canonical_ndbps_20_ht[]  = {26, 52, 78, 104, 156, 208, 234, 260};
    int   canonical_ndbps_40_ht[]  = {54, 108, 162, 216, 324, 432, 486, 540};

    int   canonical_ndbps_20_vht[] = {26,52, 78, 104, 156, 208, 234, 260, 312};
    int   canonical_ndbps_40_vht[] = {54, 108, 162, 216, 324, 432, 486, 540, 648, 720};
    int   canonical_ndbps_80_vht[] = {117, 234, 351, 468, 702, 936, 1053, 1170, 1404, 1560};

    int   ndbps;
    float symbol_tx_time, bitrate  = 0.0f;

    if (plcpType == 0)
        bitrate =  canonical_rate_legacy[mcsIndex];
    else if (plcpType == 1 || plcpType == 2)
    {
        if ( rflags & FLAGS_CHAN_SHORTGI)
            symbol_tx_time = 3.6f;
        else
            symbol_tx_time = 4.0f;

        if ( rflags & FLAGS_CHAN_40MHZ )
            ndbps = canonical_ndbps_40_ht[ mcsIndex - 8*(int)(mcsIndex/8) ];
        else
            ndbps = canonical_ndbps_20_ht[ mcsIndex - 8*(int)(mcsIndex/8) ];

        bitrate = ( ndbps * (((int)(mcsIndex/8) + 1) )) / symbol_tx_time;
    }
    else
    {
        if ( rflags & FLAGS_CHAN_SHORTGI)
            symbol_tx_time = 3.6f;
        else
            symbol_tx_time = 4.0f;

    /
    if (mcsIndex > 9) mcsIndex = 9;
        if ( rflags & FLAGS_CHAN_40MHZ )
            bitrate = (canonical_ndbps_40_vht[ mcsIndex ] * nss) / symbol_tx_time;
        else if (rflags & FLAGS_CHAN_80MHZ )
            bitrate = (canonical_ndbps_80_vht[ mcsIndex ] * nss) / symbol_tx_time;
        else
        {
            if (mcsIndex == 9 && nss == 3)
                bitrate = 1040 / symbol_tx_time;
            else if (mcsIndex < 9)
                bitrate = (canonical_ndbps_20_vht[ mcsIndex ] * nss) / symbol_tx_time;
        }
    }

    return bitrate;
}
