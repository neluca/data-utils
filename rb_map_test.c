#include <stdio.h>
#include <string.h>
#include "rbtree.h"

typedef struct {
  struct rbtree_node node;
  char *key;
  char *value;
} rb_map_node_t;

int map_compare(void *left, void *right) {
  rb_map_node_t *_left = (rb_map_node_t *)left;
  rb_map_node_t *_right = (rb_map_node_t *)right;
  return strcmp(_left->key, _right->key);
}

int key_compare(void *key, void *tree_node) {
  char *s1 = key;
  char *s2 = ((rb_map_node_t *)tree_node)->key;
  return strcmp(s1, s2);
}

int main() {
  struct rbtree rb_map;
  rbtree_init(&rb_map, map_compare);

  rb_map_node_t kv[10];
  kv[0].key = "hello";
  kv[0].value = "10";

  kv[1].key = "world";
  kv[1].value = "11";

  kv[2].key = "qw";
  kv[2].value = "12";

  kv[3].key = "qwerty";
  kv[3].value = "13";

  kv[4].key = "bob";
  kv[4].value = "14";

  kv[5].key = "Alice";
  kv[5].value = "15";

  kv[6].key = "Cat";
  kv[6].value = "16";

  kv[7].key = "Dog";
  kv[7].value = "1123";

  kv[8].key = "Liao";
  kv[8].value = "14953";

  kv[9].key = "Yin";
  kv[9].value = "10087";

  for (int i = 0; i < 10; i++) {
	rbtree_node_init(&kv[i].node);
	rbtree_insert(&rb_map, &kv[i].node);
  }

  rb_map_node_t *d = rbtree_lookup2(&rb_map, "Liao", key_compare);
  if (d)
	printf("%s  %s\n", d->key, d->value);

  d = rbtree_lookup2(&rb_map, "Alice", key_compare);
  if (d)
	printf("%s  %s\n", d->key, d->value);

  printf("\n-----------------\n");
  rb_map_node_t *p = (rb_map_node_t *)rbtree_first(&rb_map);
  while (p) {
	printf("%s\n", p->key);
	p = (rb_map_node_t *)rbtree_next((struct rbtree_node *)p);
  }

  printf("\n-----------------\n");
  rb_map_node_t *kv_0 = rbtree_entry(&kv[0].node, rb_map_node_t, node);
  printf("kv : %s   %s", kv_0->key, kv_0->value);
  return 0;
}
