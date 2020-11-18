#ifndef LIST_H

#define LIST_H

#include "common.h"

// alias to list element type
// typedef int64_t entry;
typedef struct entry {
  const char* key;
  const char* value;
} entry;

// struct --- template of data bundles
struct list {
  entry value;
  struct list* next;
};




typedef void (entry_action)(entry);


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
 * So we use <i>struct list**<i> type 
 * (double pointer).
 */
void list_add_front(struct list** l, entry e);

void list_add_back(struct list** l, entry e);

void list_destroy(struct list* l);

void list_foreach(struct list const* l, entry_action f);

void entry_print(entry e);

struct entry const* list_find_key(struct list*, const char* );

struct list* c(entry value, struct list* next);

#endif // LIST_H
