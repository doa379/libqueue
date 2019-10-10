#include <pthread.h>
#include <string.h>
#include "list.h"
#include "tpool.h"

static void del_job(void *data)
{
  job_t *job = data;

  if (job->arg_size)
    free(job->arg);
}

void clear_tpool(tpool_t *tp)
{
  pthread_mutex_lock(&tp->mutex);
  for_each(tp->jobs_q, del_job); 
  clear_list(tp->jobs_q);
  pthread_mutex_unlock(&tp->mutex);
}

static void pop_queue(tpool_t *tp)
{
  node_t *node = head(tp->jobs_q);
  del_job(node->data);
  del_head(tp->jobs_q);
}

void tpool_queue(tpool_t *tp, void (*func)(void *), void *arg, size_t size)
{
  job_t job = {
    .func = func,
    .arg = arg,
    .arg_size = size
  };

  if (size)
    {
      job.arg = malloc(size);
      memcpy(job.arg, arg, size);
    }
  
  pthread_mutex_lock(&tp->mutex);
  insert_tail(tp->jobs_q, &job, sizeof(job_t));
  pthread_mutex_unlock(&tp->mutex);
  pthread_cond_signal(&tp->cond_var);
}

static void *worker_th(void *userp)
{
  tpool_t *tp = userp;
  void (*func)(void *);
  
  while (1)
    {
      pthread_mutex_lock(&tp->mutex);

      while (!count(tp->jobs_q) && !tp->quit)
	pthread_cond_wait(&tp->cond_var, &tp->mutex);

      if (tp->quit)
	{
	  pthread_mutex_unlock(&tp->mutex);
	  return NULL;
	}
      
      job_t *job = head(tp->jobs_q)->data;
      pthread_mutex_unlock(&tp->mutex);
      func = job->func;
      func(job->arg);
      pthread_mutex_lock(&tp->mutex);
      pop_queue(tp);
      pthread_mutex_unlock(&tp->mutex);
    }

  return NULL;
}

void del_tpool(tpool_t *tpool)
{
  tpool->quit = 1;
  clear_tpool(tpool);
  pthread_cond_signal(&tpool->cond_var);
  pthread_join(tpool->pth, NULL);
  pthread_cond_destroy(&tpool->cond_var);
  pthread_mutex_destroy(&tpool->mutex);
  del_list(tpool->jobs_q);
  free(tpool);
  tpool = NULL;
}

tpool_t *new_tpool(void)
{
  tpool_t *tpool = malloc(sizeof(tpool_t));
  tpool->quit = 0;
  tpool->jobs_q = new_list();
  pthread_mutex_init(&tpool->mutex, NULL);
  pthread_cond_init(&tpool->cond_var, NULL);
  pthread_create(&tpool->pth, NULL, worker_th, (void *) tpool);
  return tpool;
}
