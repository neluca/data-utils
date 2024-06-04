#include <stdio.h>
#include "list.h"

struct test_list {
  struct list_node node;
  int data;
};

#define LEN 10
int main() {
  list_t list;
  list_init(&list);
  if (list_empty(&list)) {
	printf("Empty \n");
  }

  struct test_list d[LEN];
  for (int i = 0; i < LEN; i++) {
	list_node_init(&d[i].node);
	d[i].data = i;
	list_insert_tail(&list, &d[i].node);
  }

  struct list_node *p;
  list_foreach(&list, p) {
	printf("%d  ", ((struct test_list *)p)->data);
  }

  printf("\n");
  if (list_in(&d[LEN - 2].node))
	printf("IN\n");
  else
	printf("NOT IN\n");

  struct test_list d1;
  list_node_init(&d1.node);
  if (list_in(&d1.node))
	printf("IN\n");
  else
	printf("NOT IN\n");

  struct test_list d2[LEN - 1];
  for (int i = 0; i < LEN - 1; i++) {
	list_node_init(&d2[i].node);
	d2[i].data = i;
	list_insert_head(&list, &d2[i].node);
  }
  list_foreach(&list, p) {
	printf("%d  ", ((struct test_list *)p)->data);
  }

  printf("\n");
  list_remove(&d2[1].node);
  list_foreach(&list, p) {
	printf("%d  ", ((struct test_list *)p)->data);
  }

  printf("\n");
  if (list_in(&d2[1].node))
	printf("IN\n");
  else
	printf("NOT IN\n");

  p = list_head(&list);
  printf("%d\n", ((struct test_list *)p)->data);
  return 0;
}
