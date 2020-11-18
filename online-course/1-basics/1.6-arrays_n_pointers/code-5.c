void array_fib(int* array, int* limit) {
  array[0] = array[1] = 1;
  for (int* current = array + 2; current < limit; current++)
    *current = *(current - 1) + *(current - 2);
}