/* Описание инструкций (см. предыдущий шаг) */
enum opcode { BC_PUSH, BC_IPRINT, BC_IREAD, BC_IADD, BC_STOP };

struct bc_noarg {
  enum opcode opcode;
};
struct bc_arg64 {
  enum opcode opcode;
  int64_t arg;
};
union ins {
  enum opcode opcode;
  struct bc_arg64 as_arg64;
  struct bc_noarg as_noarg;
};

/* ------------------------ */

struct vm_state {
  const union ins *ip;
  struct stack data_stack;
};

/* Начальная вместимость стека задаётся определением STACK_CAPACITY */
struct vm_state state_create(const union ins *ip) {
  return (struct vm_state){.ip = ip,
                           .data_stack = stack_create(STACK_CAPACITY)};
}

// Как правильно деинициализировать состояние, освободить все ресурсы?
void state_destroy(struct vm_state *state) {
  stack_destroy( &(state->data_stack) );
}


/* Вы можете использовать эти функции: */
void print_int64(int64_t);
struct maybe_int64 maybe_read_int64();

struct stack stack_create(size_t size);
void stack_destroy(struct stack *s);
bool stack_push(struct stack *s, int64_t value);
struct maybe_int64 stack_pop(struct stack *s);

/* Опишите цикл интерпретации с выборкой и выполнением команд (пока не выполним STOP) */
void interpret(struct vm_state *state) {
  while ( state->ip != NULL ) {
      switch ( ( state->ip )->opcode ) {
          case BC_IPRINT: print_int64( stack_pop( &(state->data_stack) ).value ); break;
          case BC_IREAD: stack_push( &(state->data_stack), maybe_read_int64().value ); break;
          case BC_PUSH: stack_push( &(state->data_stack), ( (state->ip)->as_arg64 ).arg ); break;
          case BC_IADD:
            stack_push( &(state->data_stack), stack_pop( &(state->data_stack) ).value + stack_pop( &(state->data_stack) ).value );
            break;
          case BC_STOP:
          default: state->ip = NULL; break;
      }
      if ( state->ip == NULL )
          break;
      else state->ip++;
  };
}

void interpret_program(const union ins *program) {
  struct vm_state state = state_create(program);
  interpret(&state);
  state_destroy(&state);
}