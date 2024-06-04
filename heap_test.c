#include <stdio.h>
#include "heap.h"

struct test_heap {
  struct heap_node node;
  int data;
};

int heap_compare_cb(const void *a, const void *b) {
  struct test_heap *pa = (struct test_heap *)a;
  struct test_heap *pb = (struct test_heap *)b;

  return pa->data < pb->data;
}

int main() {
  struct heap _heap;
  struct heap *heap = &_heap;

  heap_init(heap, heap_compare_cb);
  struct test_heap d[20];
  int a[20] = {34, 7, 645, 23, 8655, 32, 87, 43, 986, 352, 86745, 532, 9876, 532, 8976, 436, 87453, 7645, 5234, 53};
  for (int i = 0; i < 20; i++) {
	d[i].data = a[i];
	heap_push(heap, &(d[i].node));
  }

  struct test_heap **top = (struct test_heap **)&heap_top(heap);

  for (int i = 0; i < 20; i++) {
	struct test_heap *p = (struct test_heap *)heap->root;
	printf("%d  %d\n", p->data, d[i].data);

	heap_pop(heap);
  }
  for (int i = 0; i < 20; i++) {
	d[i].data = a[i];
	heap_push(heap, &(d[i].node));
  }
  printf("----------------\n");
  heap_remove(heap, &(d[10].node));
  while (*top != NULL) {
	printf("%d\n", (*top)->data);
	heap_pop(heap);
  }

  return 0;
}
