#ifndef TPOOL_H
#define TPOOL_H

#include <pthread.h>
#include <stdbool.h>

typedef struct
{
  void (*func)(void *);
  void *arg;
} job_t;

typedef struct
{
  void *jobs_q;
  pthread_mutex_t mutex;
  pthread_cond_t cond_var;
  pthread_t pth;
  bool quit;
} tpool_t;

void tpool_queue(tpool_t *, void (*)(void *), void *);
void clear_tpool(tpool_t *);
void del_tpool(tpool_t *);
tpool_t *create_tpool(size_t, void *);

#endif
