// Заполняет выделенный массив значениями, считанными со входа
void array_int_fill( int64_t* array, size_t size ) {
  for (size_t i = 0; i < size; ++i)
    scanf("%" SCNd64 " ", array + i);
}

// Считывает размер и записывает в *size;
// Выделяет память под массив
// Заполняет массив значениями, считанными со входа 
// возвращает его
int64_t* array_int_read( size_t* size ) {
  scanf("%" SCNu64 " ", size);
  int64_t* array = malloc(sizeof(int64_t) * *size);
  array_int_fill(array, *size);
  return array;
}

// Печатает массив; пробел после каждого элемента
void array_int_print(int64_t const* array, size_t size) {
   for( size_t i = 0; i < size; i = i + 1) {
      printf( "%" PRIu64 " ", array[i] );
   }
}

// Возвращает указатель на минимальный элемент; NULL если его нет
int64_t* array_int_min( int64_t* array, size_t size ) {
  if (!size)
    return NULL;
  size_t i = 0;
  int64_t min = array[i];
  size_t imin = 0;
  for (i = 1; i < size; ++i)
    if (min > array[i]) {
      min = array[i];
      imin = i;
    }
  return array + imin;
}

// Считывает массив, если минимальный элемент существует то печатает его на выход
void perform() {
  size_t* size = malloc(sizeof(size_t));
  int64_t* array = array_int_read(size);
  int64_t* ptr_min = array_int_min(array, *size);
  if (ptr_min)
    printf("%" PRId64 "\n", *ptr_min);
  free(size);
  free(array);
}