// упакованное число 42 выводится как "Some 42"
// Ошибка выводится как None
void maybe_int64_print( struct maybe_int64 i ) {
    if(i.valid) {
        printf( "Some %" PRId64, i.value );
    } else {
        printf("None");
    }
}

// Если обе упаковки содержат ошибку, то результат ошибка
// Если ровно одна упаковка содержит ошибку, то результат — вторая
// Если обе упаковки содержат число, то результат это минимум из двух чисел.
struct maybe_int64 maybe_int64_min(struct maybe_int64 a, struct maybe_int64 b) {
    if (a.valid) {
        if (b.valid) {
            if (a.value < b.value) {
                return a;
            }
            return b;
        }
        return a;
    }
    if (b.valid) {
        return b;
    }
    return none_int64;
}
