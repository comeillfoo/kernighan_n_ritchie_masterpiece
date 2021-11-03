/*

struct array_int {
  int64_t* data;
  size_t size;
};

struct stack {
  size_t count;
  struct array_int data;
};

*/

void interpret(struct vm_state* state, ins_interpreter * const  (actions)[]) {
  for (; state->ip ;) {
    const union ins* ins = state->ip;

    const struct ins_descr* ins_descr = instructions + ins->opcode;
      
    if ( ins_descr->min_stack > (state->data_stack).count ) {
        printf( "Stack underflow\n" );
        break;
    }
    if ( (state->data_stack).count > ( (state->data_stack).data).size - ins_descr->stack_delta ) {
        printf( "Stack overflow\n" );
        break;
    }

    actions[ins->opcode](state);

    if (!ins_descr->affects_ip) { state->ip = state->ip + 1; }
  }
}