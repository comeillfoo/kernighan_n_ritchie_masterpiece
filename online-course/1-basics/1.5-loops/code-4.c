int is_prime(int num) {
    num = num < 0? -num : num;
    if (!num || !(num >> 1)) return 0;
    for (int i = 2; i < num; ++i)
        if (num % i == 0) return 0;
    return 1;
}