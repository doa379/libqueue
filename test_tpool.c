/*
  $ cc test_tpool.c -L $PWD -l queue -Wl,-rpath,$PWD -o test_tpool && ./test_tpool
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tpool.h"

void func_cb(void *data)
{
  int *v = (int *) data;
  printf("%d\n", *v);
}

int main()
{
  tpool_t *tpool = create_tpool();
  srand(0);
  
  while (1)
    {
      int v = rand() % 100;
      tpool_queue(tpool, func_cb, &v, sizeof(int));
      sleep(1);
    }
  
  del_tpool(tpool);
  return 0;
}
