struct heap_string {
  char* addr;
};

// скопировать в кучу
struct heap_string halloc( const char* s ){
    char* a = malloc(sizeof(char*));
    strcpy(a, s);
    return (struct heap_string){.addr=a};
}

// освободить память
void heap_string_free( struct heap_string h ){
    free(h.addr);
}
