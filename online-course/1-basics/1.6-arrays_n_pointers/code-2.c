void normalize(int* ptr_num) {
    if (!*ptr_num) return;
    if (*ptr_num % 2 != 0) return;
    else {
        *ptr_num >>= 1;
        normalize(ptr_num);
    }
}