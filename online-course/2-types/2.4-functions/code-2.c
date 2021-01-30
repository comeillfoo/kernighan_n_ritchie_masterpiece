/* Этими функциями вы можете пользоваться */
void print_int64(int64_t i);
void print_size(size_t i) ;

struct maybe_int64 some_int64(int64_t i);
//const struct maybe_int64 none_int64 = { 0 };

void maybe_int64_print( struct maybe_int64 i );

struct maybe_int64 read_int64();

struct list* node_create( int64_t value );

void list_destroy( struct list* list );
void list_add_front( struct list** old, int64_t value );
struct list* list_last( struct list * list );
void list_add_back( struct list** old, int64_t value );
size_t list_length( struct list const* list );
struct list* list_node_at( struct list* list, size_t idx );
struct maybe_int64 list_at(struct list* list, size_t idx);
struct list* list_reverse( const struct list* list );
void list_print(const struct list* l);




/* Запустить функцию f на каждом элементе списка  */
void list_foreach(const struct list* const l, void (f)(int64_t)) {
  for (const struct list* cur = l; cur; cur = cur->next)
      f(cur->value);
}



/* Изменить каждый элемент списка с помощью функции f  */
void list_map_mut(struct list* const l, int64_t (f) (int64_t)) {
  for (struct list* cur = l; cur; cur = cur->next)
      cur->value = f(cur->value);
}

/*  Создать новый список, в котором каждый элемент получен из соответствующего
 элемента списка l путём применения функции f */
struct list* list_map(const struct list* const l, int64_t (f) (int64_t)) {
    struct list* nl = NULL;
    
    for (const struct list* cur = l; cur; cur = cur->next)
       list_add_front( &nl, f(cur->value) );
    
    struct list* result = list_reverse(nl);
    list_destroy(nl);
    return result;
}

/* Свернуть список l с помощью функции f. */
int64_t list_fold(const struct list* l, int64_t init, int64_t (f)(int64_t, int64_t)) {
    int64_t result = init;
    
    for(const struct list* cur = l; cur; cur = cur->next ) {
        result = f( result, cur->value );
    }
    
    return result;
}

/*  Сгенерировать список длины sz с помощью значения init и функции f
 Результат: init, f(init), f(f(init)), ... */
struct list* list_iterate( int64_t init, size_t sz, int64_t (f) (int64_t) ) {
    struct list* nl = NULL;
    
    list_add_front( &nl, init );
    
    int64_t prev = init;
    
    for (size_t i = 1; i < sz; ++i) {
       prev = f(prev);
       list_add_front( &nl, prev );
    }
    
    struct list* result = list_reverse(nl);
    list_destroy(nl);
    return result;
}