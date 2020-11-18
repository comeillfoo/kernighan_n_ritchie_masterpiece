size_t count_zeroes(void const* data, size_t sz ) {
    size_t counter = 0;
    for (size_t i = 0; i < sz; ++i)
        counter += !((uint8_t*) data)[i];
    return counter;
}
