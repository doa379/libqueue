/*
  $ cc test_tpool.c -L $PWD -l queue -Wl,-rpath,$PWD -o test_tpool && ./test_tpool
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tpool.h"
#include "list.h"

void func_cb(void *data)
{
  int *v = (int *) data;
  printf("%d\n", *v);
  sleep(5);
  printf("Job exit\n");
}

int main()
{
  tpool_t *tpool = create_tpool();
  srand(0);
  
  for (unsigned i = 0; i < 5; i++)
    {
      int v = rand() % 100;
      tpool_queue(tpool, func_cb, &v, sizeof(int));
      printf("Data %d job added\n", v);
    }

  while (count(tpool->jobs_q))
    {
      printf("%d jobs remaining\n", count(tpool->jobs_q));
      sleep(1);
    }
  
  del_tpool(tpool);
  return 0;
}
