#include <string.h>
#include "list.h"

void *new_list(void)
{
  TAILQ_HEAD(queue, node);
  struct queue *list = malloc(sizeof(struct queue));
  TAILQ_INIT(list);
  return list;
}

void clear_list(void *list)
{
  TAILQ_HEAD(queue, node);

  while (!TAILQ_EMPTY((struct queue *) list))
    {
      node_t *n = TAILQ_FIRST((struct queue *) list);
      TAILQ_REMOVE((struct queue *) list, n, nodes);

      if (n->size)
	free(n->data);

      free(n);
    }
}

void del_list(void *list)
{
  clear_list(list);
  free(list);
}

void insert_head(void *list, void *data, size_t size)
{
  node_t *h = (node_t *) malloc(sizeof(node_t));
  h->list = list;
  h->size = size;

  if (!size)
    h->data = data;

  else
    {
      h->data = malloc(size);
      memcpy(h->data, data, size);
    }

  TAILQ_HEAD(queue, node);
  TAILQ_INSERT_HEAD((struct queue *) list, h, nodes);
}

void insert_tail(void *list, void *data, size_t size)
{
  node_t *h = (node_t *) malloc(sizeof(node_t));
  h->list = list;
  h->size = size;

  if (!size)
    h->data = data;

  else
    {
      h->data = malloc(size);
      memcpy(h->data, data, size);
    }

  TAILQ_HEAD(queue, node);
  TAILQ_INSERT_TAIL((struct queue *) list, h, nodes);
}

void del_head(void *list)
{
  TAILQ_HEAD(queue, node);

  if (TAILQ_EMPTY((struct queue *) list))
    return;

  node_t *n = TAILQ_FIRST((struct queue *) list);
  TAILQ_REMOVE((struct queue *) list, n, nodes);

  if (n->size)
    free(n->data);

  free(n);
}

void del_tail(void *list)
{
  TAILQ_HEAD(queue, node);

  if (TAILQ_EMPTY((struct queue *) list))
    return;

  node_t *n = TAILQ_LAST((struct queue *) list, queue);
  TAILQ_REMOVE((struct queue *) list, n, nodes);

  if (n->size)
    free(n->data);

  free(n);
}

void del_node(void *list, node_t *n)
{
  TAILQ_HEAD(queue, node);

  if (TAILQ_EMPTY((struct queue *) list))
    return;

  TAILQ_REMOVE((struct queue *) list, n, nodes);

  if (n->size)
    free(n->data);

  free(n);
}

node_t *head(void *list)
{
  TAILQ_HEAD(queue, node);

  if (TAILQ_EMPTY((struct queue *) list))
    return NULL;

  node_t *n = TAILQ_FIRST((struct queue *) list);
  return n;
}

node_t *tail(void *list)
{
  TAILQ_HEAD(queue, node);

  if (TAILQ_EMPTY((struct queue *) list))
    return NULL;

  node_t *n = TAILQ_LAST((struct queue *) list, queue);
  return n;
}

size_t count(void *list)
{
  size_t count = 0;
  TAILQ_HEAD(queue, node);
  node_t *dummy;
  TAILQ_FOREACH(dummy, (struct queue *) list, nodes) count++;
  return count;
}

node_t *next(void *list, node_t *n)
{
  TAILQ_HEAD(queue, node);

  if (TAILQ_EMPTY((struct queue *) list))
    return NULL;

  return TAILQ_NEXT(n, nodes);
}

node_t *prev(void *list, node_t *n)
{
  TAILQ_HEAD(queue, node);

  if (TAILQ_EMPTY((struct queue *) list))
    return NULL;

  return TAILQ_PREV(n, queue, nodes);
}

node_t *itr_head(void *list, size_t N)
{
  node_t *n = head(list);

  for (size_t i = 0; i < N && n; i++)
    n = next(list, n);

  return n;
}

node_t *itr_tail(void *list, size_t N)
{
  node_t *n = tail(list);

  for (size_t i = 0; i < N && n; i++)
    n = prev(list, n);

  return n;
}

node_t *itr_node(void *list, node_t *n, size_t N, char pole)
{
  for (size_t i = 0; i < N; i++)
    {
      if (pole < 0)
	n = prev(list, n);

      else
	n = next(list, n);
    }

  return n;
}

void for_each(void *list, void (*cb)(node_t *, void *), void *context)
{
  TAILQ_HEAD(queue, node);
  node_t *node;
  TAILQ_FOREACH(node, (struct queue *) list, nodes) cb(node, context);
}

void *replicate_list(void *LIST)
{
  void *NEW_LIST = new_list();
   
  for (node_t *n = head(LIST); n; n = next(LIST, n))
    insert_tail(NEW_LIST, n->data, n->size);

  return NEW_LIST;
}
