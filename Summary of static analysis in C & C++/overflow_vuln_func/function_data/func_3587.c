    predictor_pair = s->c_predictor_table[index]; \
    horiz_pred += (predictor_pair >> 1); \
    if (predictor_pair & 1) { \
        GET_NEXT_INDEX() \
        if (!index) { \
            GET_NEXT_INDEX() \
            predictor_pair = s->fat_c_predictor_table[index]; \
            horiz_pred += (predictor_pair >> 1); \
            if (predictor_pair & 1) \
                GET_NEXT_INDEX() \
            else \
                index++; \
        } \
    } else \
