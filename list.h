#ifndef LIST_H
#define LIST_H

#include <sys/queue.h>
#include <stdlib.h>

typedef struct node
{
  void *list;
  void *data;
  size_t size;
  TAILQ_ENTRY(node) nodes;
} node_t;

void *new_list(void);
void clear_list(void *);
void del_list(void *);
void insert_head(void *, void *, size_t);
void insert_tail(void *, void *, size_t);
void del_head(void *);
void del_tail(void *);
void del_node(void *, node_t *);
node_t *head(void *);
node_t *tail(void *);
size_t count(void *);
node_t *next(void *, node_t *);
node_t *prev(void *, node_t *);
node_t *itr_head(void *, size_t);
node_t *itr_tail(void *, size_t);
node_t *itr_node(void *, node_t *, size_t, char);
void for_each(void *, void (*)(node_t *, void *), void *);

#endif
