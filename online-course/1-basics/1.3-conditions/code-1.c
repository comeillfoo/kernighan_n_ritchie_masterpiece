int is_sorted2(int a, int b) {
    return a < b;
}

int is_sorted3(int a, int b, int c) {
    if (is_sorted2(a, b) && is_sorted2(b, c))
        return 1;
    else if (is_sorted2(c, b) && is_sorted2(b, a))
        return -1;
    else return 0;
}