enum move_dir { MD_UP, MD_RIGHT, MD_DOWN, MD_LEFT, MD_NONE };

typedef void move_callback(enum move_dir);

// struct --- template of data bundles
struct list {
  move_callback* value;
  struct list* next;
};

static struct list* node_create(move_callback e) {
  struct list* result = malloc(sizeof(struct list));
  // tip: sizeof not a function and evaluates during compilation time
  result->value = e;
  // tip: bad manner leave some field uninitialized because of trash
  result->next = NULL;
  return result;
}

struct list* list_last(struct list* l) {
  // const pointer not used because of
  // returning parameter which is mutable
  if (l == NULL) return NULL;
  struct list* cur = l;
  for (; cur->next != NULL; cur = cur->next);
  return cur;
}

void list_add_front(struct list** l, move_callback e) {
  if (*l) {
    // *l != NULL
    struct list* const oldstart = *l;
    *l = node_create(e);
    (*l)->next = oldstart;
  } else *l = node_create(e);
}

void list_add_back(struct list** l, move_callback e) {
  // *l != NULL
  if (*l) list_last(*l)->next = node_create(e);
  else list_add_front(l, e);
}

void list_destroy(struct list* l) {
  if (!l) return;
  struct list* cur = l;
  while (cur) {
    struct list* next = cur->next;
    free(cur);
    cur = next;
  }
}

// Робот и его callback'и
// callback'ов может быть неограниченное количество
struct robot {
  const char* name;
  struct list* handlers;
};

void list_foreach(struct list const* l, enum move_dir d) {
  for (const struct list* cur = l; cur; cur = cur->next)
    cur->value(d);
}


// Добавить callback к роботу, чтобы он вызывался при движении
// В callback будет передаваться направление движения
void register_callback(struct robot* robot, move_callback new_cb) {
  list_add_back( &(robot->handlers), new_cb );
}

// Отменить все подписки на события.
// Это нужно чтобы освободить зарезервированные ресурсы
// например, выделенную в куче память
void unregister_all_callbacks(struct robot* robot) {
  list_destroy( robot->handlers );
}

// Вызывается когда робот движется
// Эта функция должна вызвать все обработчики событий
void move(struct robot* robot, enum move_dir dir) {
  list_foreach(robot->handlers, dir);
}