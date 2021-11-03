static struct stack_interface {
  struct stack_int_interface {
    struct stack_int* (*create)();
    bool (*empty)(struct stack_int const*);
    bool (*full)(struct stack_int const*);
    void (*destroy)(struct stack_int*);
    bool (*push)(struct stack_int*, item);
    struct maybe_item (*pop)(struct stack_int*);
  } int64;
} const stack = {{stack_int_create, stack_int_empty, stack_int_full,
                  stack_int_destroy, stack_int_push, stack_int_pop}};