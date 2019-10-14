/*
  $ cc test_list.c -L $PWD -l queue -Wl,-rpath,$PWD -o test_list && ./test_list
*/

#include <string.h>
#include <stdio.h>
#include "list.h"

typedef struct
{
  char text[255];
} foo_t;

void func_cb(node_t *node, void *context)
{
  foo_t *f = node->data;
  strcat(f->text, " Bar");
  printf("%s\n", f->text);
}

int main()
{
  void *list = new_list();
  foo_t f[3];
  strcpy(f[0].text, "1 Foo");
  strcpy(f[1].text, "2 Foo");
  strcpy(f[2].text, "3 Foo");

  for (unsigned int i = 0; i < 3; i++)
    insert_tail(list, &f[i], sizeof(foo_t));
  
  for (unsigned int i = 0; i < 3; i++)
    {
      node_t *f = head(list);
      char *text = f->data;
      printf("%s\n", text);
      for_each(list, func_cb, NULL);
      del_head(list);
    }
  
  del_list(list);
  return 0;
}
