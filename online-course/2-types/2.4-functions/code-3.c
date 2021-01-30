// Мы хотим, чтобы в структуре user хранились ссылки только на строчки из кучи.
typedef struct { char* addr; } string_heap ;

/*  Тип для идентификаторов пользователей
    и его спецификаторы ввода и вывода для printf */
typedef uint64_t uid;
#define PRI_uid PRIu64
#define SCN_uid SCNu64

enum city {C_SARATOV, C_MOSCOW, C_PARIS, C_LOS_ANGELES, C_OTHER};

/*  Массив, где элементам перечисления сопоставляются их текстовые представления */
const char* city_string[] = {
  [C_SARATOV] = "Saratov",
  [C_MOSCOW] = "Moscow",
  [C_PARIS] = "Paris",
  [C_LOS_ANGELES] = "Los Angeles",
  [C_OTHER] = "Other"
};


struct user {
  const uid id;
  const string_heap name;
  enum city city;
};

int user_uid_comparer(const struct user* _x, const struct user* _y) {
   return (int)(_y->id - _x->id);
}

int user_uid_void_comparer(const void* _x, const void* _y) {
   return user_uid_comparer(_y, _x);
}

/* Сортировать массив пользователей по полю uid по возрастанию */
void users_sort_uid(struct user users[], size_t sz) {
  qsort(users, sz, sizeof(struct user), user_uid_void_comparer );
}

int user_name_comparer(const struct user* _x, const struct user* _y) {
    return strcmp( _x->name.addr, _y->name.addr );
}

int user_name_void_comparer(const void* _x, const void* _y) {
  return user_name_comparer(_x, _y);
}

/* Сортировать массив пользователей по полю name */
/* Порядок строк лексикографический; можно использовать компаратор 
   строк -- стандартную функцию strcmp */
void users_sort_name(struct user users[], size_t sz) {
  qsort(users, sz, sizeof(struct user), user_name_void_comparer );
}

int user_city_comparer(const struct user* _x, const struct user* _y) {
    return strcmp( city_string[_x->city], city_string[_y->city] );
}

int user_city_void_comparer(const void* _x, const void* _y) {
  return user_city_comparer( _x, _y );
}

/* Сортировать массив по _текстовому представлению_ города */
void users_sort_city(struct user users[], size_t sz) {
  qsort(users, sz, sizeof(struct user), user_city_void_comparer );
}