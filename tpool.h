#ifndef TPOOL_H
#define TPOOL_H

#include <pthread.h>
#include <stdbool.h>

typedef struct
{
  void (*func)(void *, void *);
  void *arg;
  size_t arg_size;
} job_t;

typedef struct
{
  void *jobs_q, *context;
  pthread_mutex_t mutex;
  pthread_cond_t cond_var;
  pthread_t pth;
  bool quit;
} tpool_t;

tpool_t *new_tpool(void *);
void del_tpool(tpool_t *);
void clear_tpool(tpool_t *);
void tpool_queue(tpool_t *, void (*)(void *, void *), void *, size_t);

#endif
