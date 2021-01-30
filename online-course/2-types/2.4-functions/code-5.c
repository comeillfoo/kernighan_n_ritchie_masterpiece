/*  Вы можете пользоваться следующими функциями */
size_t stack_count( const struct stack* s );

struct stack
     stack_create( size_t size );
void stack_destroy( struct stack* s );
bool stack_is_full( const struct stack * s);
bool stack_is_empty( const struct stack * s);
bool stack_push( struct stack* s, int64_t value );
struct maybe_int64
     stack_pop( struct stack* s );
void stack_print( const struct stack* s );

// --- Интерпретатор ---


// Здесь перечислены все типы инструкций
enum opcode { 
    BC_PUSH, BC_POP, BC_SWAP, BC_DUP,
    BC_IADD, BC_ISUB, BC_IMUL, BC_IDIV, 
    BC_INEG,
    BC_IPRINT, BC_IREAD, 
    BC_ICMP, 
    BC_STOP 
};

// Инструкция union ins в одном из форматов
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

// Теперь опишем инструкции языка
// Все инструкции попадают в формат "нет аргументов" или "один аргумент"
enum ins_format { IAT_NOARG, IAT_I64 };

// Эта структура позволяет декларативно описать инструкцию
struct ins_descr { const char* mnemonic; enum ins_format format; };

// Индекс в этом массиве соответствует типу инструкции
// Каждая структура описывает мнемонику инструкции (текстовое представление)
// и её тип
static const struct ins_descr instructions[] = {

  /* Добавьте описания PUSH и IADD */
  [BC_PUSH]   = { "push",  IAT_I64   },
  [BC_IADD]   = { "iadd",  IAT_NOARG },
  [BC_ISUB]   = { "isub",  IAT_NOARG },
  [BC_IMUL]   = { "imul",  IAT_NOARG },
  [BC_IDIV]   = { "idiv",  IAT_NOARG },
  [BC_INEG]   = { "ineg",  IAT_NOARG },
  [BC_IPRINT] = { "iprint",IAT_NOARG },
  [BC_IREAD]  = { "iread", IAT_NOARG },
  [BC_SWAP]   = { "swap",  IAT_NOARG },
  [BC_POP]    = { "pop",   IAT_NOARG },
  [BC_DUP]    = { "dup",   IAT_NOARG },
  [BC_ICMP]   = { "icmp",  IAT_NOARG },
  [BC_STOP]   = { "stop",  IAT_NOARG }
};


// Чтобы интерпретировать программу
// заведём структуру "состояние программы"
// Содержит указатель на текущую инструкцию и стек чисел
struct vm_state { 
    const union ins* ip; 
    struct stack data_stack; 
};

// Создаёт начальное состояние программы
// Вместимость стека задаётся препроцессорным определением STACK_CAPACITY
struct vm_state
state_create( union ins* ip ) {
  return (struct vm_state){ .ip = ip, .data_stack = stack_create( STACK_CAPACITY ) };
}
void
state_destroy( struct vm_state * state ) {
    stack_destroy( &(state->data_stack) );
    // free( state );
}

// Эти функции поднимают операции над числами на уровень стековых операций
// lift_unop применяет операцию к вершине стека;
void lift_unop( struct stack* s, int64_t (f)(int64_t))
{
  struct maybe_int64 top = stack_pop( s );
  // if ( top.valid )
      stack_push( s, f( top.value ) );
}
// lift_binop забирает из стека два аргумента,
// применяет к ним функцию от двух переменных и возвращает в стек результат
// Это позволяет единообразно реализовать команды IADD, ISUB, IMUL, ICMP и др.
void lift_binop( struct stack* s, int64_t (f)(int64_t, int64_t))
{
  struct maybe_int64 top_a = stack_pop( s );
  struct maybe_int64 top_b = stack_pop( s );
  // if ( top_a.valid && top_b.valid )
      stack_push( s, f( top_b.value, top_a.value ) );
}

// Интерпретатор каждой инструкции это функция над состоянием машины
// Определите тип такой функции по имени ins_interpreter

typedef void ins_interpreter(struct vm_state*);

void interpret(struct vm_state* state, ins_interpreter * const  (actions)[]) {
  for (;;) {
    actions[state->ip->opcode](state);
    // Если команда записывает NULL в state->ip, надо остановиться
    if (!state->ip) break;
    state->ip = state->ip + 1;
  }
}
void vm_stop( struct vm_state* state ) { state->ip = NULL; }

void interpret_program( union ins* program, ins_interpreter * const  (actions)[]) {
  struct vm_state state = state_create( program );
  interpret( &state, actions );
  state_destroy( &state );
}

/*  Интерпретаторы команд */
void interpret_push  ( struct vm_state* state ) {
  int64_t arg = ((state->ip)->as_arg64).arg;
  stack_push( &(state->data_stack), arg );
}

void interpret_iprint( struct vm_state* state ) {
  struct maybe_int64 top = stack_pop( &(state->data_stack) );
  // if ( top.valid )
      printf( "%" PRId64, top.value );
}

void interpret_iread ( struct vm_state* state ) {
  stack_push( &(state->data_stack), read_int64() );
}

void interpret_swap  ( struct vm_state* state )  {
  struct maybe_int64 top_b = stack_pop( &(state->data_stack) );
  struct maybe_int64 top_a = stack_pop( &(state->data_stack) );
  // if ( top_b.valid && top_a.valid ) {
      stack_push( &(state->data_stack), top_b.value );
      stack_push( &(state->data_stack), top_a.value );
  // }
}

void interpret_pop   ( struct vm_state* state )  {
  stack_pop( &(state->data_stack) );
}
void interpret_dup   ( struct vm_state* state )  {
  struct maybe_int64 top = stack_pop( &(state->data_stack) );
  // if ( top.valid ) {
      stack_push( &(state->data_stack), top.value );
      stack_push( &(state->data_stack), top.value );
  // }
}

void interpret_stop  ( struct vm_state* state )  { vm_stop( state );  }

/*  Чтобы заработали эти функции необходимо реализовать lift_binop и lift_unop */

void interpret_iadd  ( struct vm_state* state );
/*{
     lift_binop(& state->data_stack, i64_add );
  }
При этом i64_add выглядит так:

int64_t i64_add( int64_t a, int64_t b ) { return a + b; }

  Следующиe функции реализованы аналогично 
  (и их не нужно реализовывать, достаточно lift_binop):
*/
void interpret_isub  ( struct vm_state* state );
void interpret_imul  ( struct vm_state* state );
void interpret_idiv  ( struct vm_state* state );
void interpret_ineg  ( struct vm_state* state );
void interpret_icmp  ( struct vm_state* state );
/* {
   lift_binop(& state->data_stack, i64_cmp);

   } */


/* Массив указателей на функции; индекс = номер инструкции */
ins_interpreter* const ins_interpreters[] = {
  [BC_PUSH]   = interpret_push,
  [BC_IADD]   = interpret_iadd,
  [BC_ISUB]   = interpret_isub,
  [BC_IMUL]   = interpret_imul,
  [BC_IDIV]   = interpret_idiv,
  [BC_INEG]   = interpret_ineg,
  [BC_IPRINT] = interpret_iprint,
  [BC_IREAD]  = interpret_iread,
  [BC_SWAP]   = interpret_swap,
  [BC_POP]    = interpret_pop,
  [BC_DUP]    = interpret_dup,
  [BC_ICMP]   = interpret_icmp,
  [BC_STOP]   = interpret_stop
};

/* С помощью interpret можно также напечатать программу на экран
   Принтер работает так же как интерпретатор,
  только смысл инструкций становится другим: каждая инструкция
  просто себя печатает.
  Реализуйте массив ins_printers, который можно передавать в функцию
  interpret_program.
  Подсказка: да, потребуются ещё функции
*/

void print_as_arg64( struct vm_state* state ) {
  struct bc_arg64 instruct = (state->ip)->as_arg64;
  enum opcode c = (state->ip)->opcode;
  printf("%s %" PRId64 "\n", (instructions[c]).mnemonic, instruct.arg );
}

void print_as_noarg( struct vm_state* state ) {
  enum opcode c = (state->ip)->opcode;  
  printf("%s\n", (instructions[c]).mnemonic );
}

void print_n_stop( struct vm_state* state ) {
  print_as_noarg( state );
  interpret_stop( state );
}

static ins_interpreter* const ins_printers[] = {
  [BC_PUSH]   = print_as_arg64,
  [BC_IADD]   = print_as_noarg,
  [BC_ISUB]   = print_as_noarg,
  [BC_IMUL]   = print_as_noarg,
  [BC_IDIV]   = print_as_noarg,
  [BC_INEG]   = print_as_noarg,
  [BC_IPRINT] = print_as_noarg,
  [BC_IREAD]  = print_as_noarg,
  [BC_SWAP]   = print_as_noarg,
  [BC_POP]    = print_as_noarg,
  [BC_DUP]    = print_as_noarg,
  [BC_ICMP]   = print_as_noarg,
  [BC_STOP]   = print_n_stop
};