#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

struct test_tree_node {
  struct rbtree_node node;
  int data;
};

int test_compare(void *left, void *right) {
  struct test_tree_node *node_left = (struct test_tree_node *)left;
  struct test_tree_node *node_right = (struct test_tree_node *)right;

  if (node_left->data == node_right->data) {
	return 0;
  } else if (node_left->data < node_right->data) {
	return RBTREE_LEFT;
  }
  return RBTREE_RIGHT;
}

int test_lookup_compare(void *key, void *node) {
  int *key_left = key;
  struct test_tree_node *node_right = (struct test_tree_node *)node;

  if (*key_left == node_right->data) {
	return 0;
  } else if (*key_left < node_right->data) {
	return RBTREE_LEFT;
  }
  return RBTREE_RIGHT;
}

int depth = 0;
void node_info(struct test_tree_node *p) {
  struct test_tree_node *cur;
  if (p->node.left != NULL) {
	depth++;
	cur = (struct test_tree_node *)p->node.left;
	node_info(cur);
  }
  for (int i = 0; i < depth; i++) {
	printf("    ");
  }
  printf("%d\n", p->data);
  if (p->node.right != NULL) {
	depth++;
	cur = (struct test_tree_node *)p->node.right;
	node_info(cur);
  }
  depth--;
}

void print_tree(struct rbtree *tree) {
  depth = 0;
  if (tree->root == NULL)
	return;
  struct test_tree_node *p = (struct test_tree_node *)tree->root;
  node_info(p);
  printf("\n");
}

#define LEN 100
//int a[LEN] = {3, 1, 2};
#define REMOVE_P 41
int main() {
  struct rbtree rbtree;
  rbtree_init(&rbtree, test_compare);

  struct test_tree_node node[LEN];
  struct rbtree_node *f;
  for (int i = 0; i < LEN; i++) {
	rbtree_node_init(&(node[i].node));
	node[i].data = rand() % 100;
//	node[i].data = i;
	f = rbtree_insert(&rbtree, (struct rbtree_node *)&(node[i]));
	if (f != (struct rbtree_node *)&(node[i])) {
	  printf("%d(F)  ", node[i].data);
	} else {
	  printf("%d  ", node[i].data);
	}
  }

  printf("\n-----------------\n");

  struct test_tree_node *n1 = (struct test_tree_node *)rbtree_lookup(&rbtree, (struct rbtree_node *)&(node[REMOVE_P]));
  if (n1 && n1->data == node[REMOVE_P].data) {
	printf("lookup  success !!  %d\n", n1->data);
  }

  int key = node[REMOVE_P].data;
  n1 = (struct test_tree_node *)rbtree_lookup2(&rbtree, &key, test_lookup_compare);
  if (n1 && n1->data == key) {
	printf("lookup2 success !!\n");
  }

  print_tree(&rbtree);
  printf("\n-----------------\n");

  rbtree_remove(&rbtree, (struct rbtree_node *)n1);

  struct test_tree_node *n2 = (struct test_tree_node *)rbtree_lookup(&rbtree, (struct rbtree_node *)&(node[REMOVE_P]));
  if (n2 && n2->data == node[REMOVE_P].data) {
	printf("lookup success !!\n");
  }
  print_tree(&rbtree);
  printf("\n-----------------\n");

  struct test_tree_node *p1 = (struct test_tree_node *)rbtree_first(&rbtree);
  struct test_tree_node *p2 = (struct test_tree_node *)rbtree_last(&rbtree);

  while (p1) {
	printf("%d  ", p1->data);
	p1 = (struct test_tree_node *)rbtree_next((struct rbtree_node *)p1);
  }
  printf("\n-----------------\n");
  while (p2) {
	printf("%d  ", p2->data);
	p2 = (struct test_tree_node *)rbtree_prev((struct rbtree_node *)p2);
  }

  printf("\n-----------------\n");
  p1 = (struct test_tree_node *)rbtree.root;
  while (p1) {
	printf("%d  ", p1->data);
	p1 = (struct test_tree_node *)rbtree_next((struct rbtree_node *)p1);
  }
  printf("\n");
  p1 = (struct test_tree_node *)rbtree.root;
  while (p1) {
	printf("%d  ", p1->data);
	p1 = (struct test_tree_node *)rbtree_prev((struct rbtree_node *)p1);
  }

  return 0;
}
