#include "list.h"
#include "map.h"

int main() {
  // struct list* l = c(1, c(2, c(4, NULL)));

  // list_foreach(l, entry_print);

  // print_newline();

  // list_add_back(&l, 42);
  // list_foreach(l, entry_print); 
  struct map m = map_create();

  map_add(m, "hello", "world");
  map_add(m, "hello2", "world2");

  map_foreach_kvp(m, entry_print);
  
  printf("%s\n", map_get(m, "hello2"));

  map_destroy(m);
  return 0;
}
