void array_reverse(int* array, int size) {
  for (int i = 0, j = size - 1; i < j; ++i, --j)
    array[i] ^= array[j] ^= array[i] ^= array[j];
}

void array_reverse_ptr(int* array, int* limit) {
  int size = limit - array;
  array_reverse(array, size);
}