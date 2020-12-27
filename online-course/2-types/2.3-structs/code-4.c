void print_int64(int64_t i) { printf("%"PRId64, i); }
void print_size(size_t i) { printf("%zu", i); }

struct maybe_int64 {int64_t value; bool valid;};
struct maybe_int64 some_int64(int64_t i) {return (struct maybe_int64) { i, true };}
const struct maybe_int64 none_int64 = { 0 };

void maybe_int64_print( struct maybe_int64 i ) {
  if (i.valid) printf("Some %" PRId64, i.value );
  else printf("None");
}

// Считать число с входа
// Если scanf возвращает константу EOF, то больше на входе ничего нет
struct maybe_int64 read_int64() {
    int64_t i;
    if (scanf("%" SCNd64, &i) == EOF)
        return none_int64;
    return (struct maybe_int64){i, true};
}


struct list {
  int64_t value;
  struct list* next;
};

struct list* node_create( int64_t value ) {
  struct list* const list = malloc( sizeof( list ) );
  *list = (struct list) { .value = value, .next = NULL };
  return list;
}

// Освободить память под весь список
void list_destroy( struct list* list ) {
    struct list* next_list;
    while(list != NULL){
        next_list = list->next;
        free(list);
        list = next_list;
    }
}

// добавить элемент в начало списка
// необходимо передавать указатель на указатель, т.к.
// список задаётся указателем на первый элемент
// Добавление элемента в начало это перенаправление
// указателя на свежий элемент.
void list_add_front( struct list** old, int64_t value ) {
    struct list* new_head = node_create(value);
    new_head->next = *old;
    *old = new_head;
}


// Последний элемент списка
struct list* list_last( struct list * list ) {
    while(list->next != NULL){
        list = list->next;
    }
    return list;
}


// Добавить элемент в конец
// Используйте list_last
void list_add_back( struct list** old, int64_t value ) {
    struct list* new_tail = node_create(value);
    if(*old != NULL){
        list_last(*old)->next = new_tail;
    }else{
        *old = new_tail;    
    }
}

// Посчитать длину списка
size_t list_length( struct list const* list ) {
    size_t length = 0;
    while(list != NULL){
        length++;
        list = list->next;
    }
    return length;
}

// указатель на структуру по индексу или NULL
struct list* list_node_at( struct list* list, size_t idx ) {
    size_t index = 0;
    while(list != NULL){
        if(idx == index)
            return list;
        list = list->next;  
        index++;
    }
    return NULL;
}

// Вернуть элемент по индексу или none_int64 если индекс слишком большой
struct maybe_int64 list_at(struct list* list, size_t idx) {
    if(list_node_at(list, idx) == NULL)
        return none_int64;
    return (struct maybe_int64){list_node_at(list, idx)->value, true};
}


// Сумма элементов в списке
int64_t list_sum( struct list const* list ) {
    int64_t sum = 0;
    while(list != NULL){
        sum += list->value;
        list = list->next;
    }
    return sum;    
}


// Возвращает перевернутую копию списка
struct list* list_reverse( const struct list* list ) {
    struct list* reversed_list = NULL;
    while (list->next != NULL) {
        list_add_front(&reversed_list, list->value);
        list = list->next;
    }
    list_add_front(&reversed_list, list->value);
    return reversed_list;
}


// Прочитать список со входа
struct list* list_read() {
  struct list* l = NULL;
  for (;;) {
    const struct maybe_int64 i = read_int64();
    if (i.valid) {
      list_add_front( &l, i.value );
    }
    else { break; }
  }
  struct list* rev = list_reverse( l );
  list_destroy( l );
  return rev;
}

// Вывести список
void list_print(const struct list* l) {
  while (l) {
    printf("%" PRId64 " ", l->value);
    l = l->next;
  }
}
