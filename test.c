/*
  $ cc test.c -L $PWD -l queue -Wl,-rpath,$PWD -o test
*/

#include <string.h>
#include <stdio.h>
#include "list.h"

typedef struct
{
  char text[255];
} foo_t;

int main()
{
  void *list = new_list();
  foo_t f[3];
  strcpy(f[0].text, "Foo 1");
  strcpy(f[1].text, "Foo 2");
  strcpy(f[2].text, "Foo 3");

  for (unsigned int i = 0; i < 3; i++)
    insert_tail(list, &f[i], sizeof(foo_t));
  
  for (unsigned int i = 0; i < 3; i++)
    {
      node_t *f = head(list);
      char *text = f->data;
      printf("%s\n", text);
      del_head(list);
    }

  del_list(list);
  return 0;
}
