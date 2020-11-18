void factorize( int n, int* a, int* b )
{
    *a = 1;
    if (n >> 1) {
        int i;
        for (i = 2; i < n / 2; ++i)
            if (!(n % i)) {
                *a = i;
                break;
            }
    }
    *b = n / *a;
}