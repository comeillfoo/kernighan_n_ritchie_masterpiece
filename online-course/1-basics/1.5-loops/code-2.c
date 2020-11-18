int is_square(int num) {
    int step = 1;
    if (num < 0) step = -step;
    for (int i = 0; i * step <= num * step; i += step)
        if (i * i == num) return 1;
    return 0;
}