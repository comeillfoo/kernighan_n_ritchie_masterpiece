#include "list.h"
#include <malloc.h>
#include "common.h"

// the code should include many but brief functions
// it helps testing and debugging

//===========================
// Supportive list interface
//===========================


/**
 * Service function creating
 * new node in list. It's a good
 * manner for using special function
 * that creates objects (structures)
 * and initializes its fields.
 */
static struct list* node_create(entry e) {
  struct list* result = malloc(sizeof(struct list));
  // tip: sizeof not a function and evaluates during compilation time
  result->value = e;
  // tip: bad manner leave some field uninitialized because of trash
  result->next = NULL;
  return result;
}
// the "static" keyword reduces function scope to this file
// often uses with service function


struct list* list_last(struct list* l) {
  // const pointer not used because of
  // returning parameter which is mutable
  if (l == NULL) return NULL;
  struct list* cur = l;
  for (; cur->next != NULL; cur = cur->next);
  return cur;
}

//=======================
// Initial list interface
//=======================

/**
 * Empty list it is a pointer to NULL.
 * Otherwise, it's a pointer to the
 * first element of list.
 *
 * To add new element to list we need to
 * reset the original pointer (by returning
 * new pointer or change pointer to pointer).
 * So, we use <i>struct list**<i> type
 * (double pointer).
 */
void list_add_front(struct list** l, entry e) {
  if (*l) {
    // *l != NULL
    struct list* const oldstart = *l;
    *l = node_create(e);
    (*l)->next = oldstart;
  } else *l = node_create(e);
}
// the well and safe code should contains
// as many constants as possible

void list_add_back(struct list** l, entry e) {
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


//===========================
// Additional list interface
//===========================

/*
 * In fact, we separate the number printing
 * from element printing from iterating through
 * the list and function invocation
 * for each element.
 *
 */

void list_foreach(struct list const* l, entry_action f) {
  for (const struct list* cur = l; cur; cur = cur->next)
    f(cur->value);
}


void entry_print(entry e) {
  // print_int64(e);
  printf("%s -> %s", e.key, e.value);
  print_newline();
}

struct entry const* list_find_key(struct list* l, const char* query) {
  for (const struct list* cur = l; cur; cur = cur->next)
    if (0 == strcmp(query, cur->value.key))
      return &(cur->value);
  return NULL;
}

struct list* c(entry value, struct list* next) {
  struct list* l = node_create(value);
  l->next = next;
  return l;
}
