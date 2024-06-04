/* Copyright Yinan Liao. and other contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "rbtree.h"

void rbtree_init(struct rbtree *tree, rbtree_node_compare_fn compare_cb) {
  tree->root = NULL;
  tree->compare_cb = compare_cb;
}

static void rbtree_rotate_left(struct rbtree *tree, struct rbtree_node *node) {
  struct rbtree_node *parent = node->parent;
  struct rbtree_node *right = node->right;

  if ((node->right = right->left))
	right->left->parent = node;
  right->left = node;

  if ((right->parent = parent)) {
	if (parent->left == node)
	  parent->left = right;
	else
	  parent->right = right;
  } else {
	tree->root = right;
  }
  node->parent = right;
}

static void rbtree_rotate_right(struct rbtree *tree, struct rbtree_node *node) {
  struct rbtree_node *parent = node->parent;
  struct rbtree_node *left = node->left;

  if ((node->left = left->right))
	left->right->parent = node;
  left->right = node;

  if ((left->parent = parent)) {
	if (parent->left == node)
	  parent->left = left;
	else
	  parent->right = left;
  } else {
	tree->root = left;
  }
  node->parent = left;
}

void *rbtree_insert(struct rbtree *tree, struct rbtree_node *new_node) {
  if (tree->root == NULL) {
	new_node->parent = NULL;
	new_node->color = BLACK;

	tree->root = new_node;
	return new_node;
  }

  struct rbtree_node *cur_node = tree->root;
  struct rbtree_node *cur_parent_node;
  int compare_flag;

  while (cur_node) {
	compare_flag = tree->compare_cb(new_node, cur_node);
	if (compare_flag == 0) {
	  return cur_node;
	} else if (compare_flag < 0) {
	  cur_parent_node = cur_node;
	  cur_node = cur_node->left;
	} else {
	  cur_parent_node = cur_node;
	  cur_node = cur_node->right;
	}
  }

  new_node->parent = cur_parent_node;
  if (compare_flag < 0) {
	cur_parent_node->left = new_node;
  } else {
	cur_parent_node->right = new_node;
  }

  struct rbtree_node *node = new_node;
  struct rbtree_node *parent, *grandpa;
  while ((parent = node->parent) && parent->color == RED) {
	grandpa = parent->parent;

	if (grandpa->left == parent) {
	  struct rbtree_node *uncle = grandpa->right;
	  if (uncle && uncle->color == RED) {
		uncle->color = BLACK;
		parent->color = BLACK;
		grandpa->color = RED;
		node = grandpa;
		continue;
	  }

	  if (parent->right == node) {
		rbtree_rotate_left(tree, parent);
		struct rbtree_node *tmp = parent;
		parent = node;
		node = tmp;
	  }

	  parent->color = BLACK;
	  grandpa->color = RED;
	  rbtree_rotate_right(tree, grandpa);
	} else {
	  struct rbtree_node *uncle = grandpa->left;
	  if (uncle && uncle->color == RED) {
		uncle->color = BLACK;
		parent->color = BLACK;
		grandpa->color = RED;
		node = grandpa;
		continue;
	  }

	  if (parent->left == node) {
		rbtree_rotate_right(tree, parent);
		struct rbtree_node *tmp = parent;
		parent = node;
		node = tmp;
	  }
	  parent->color = BLACK;
	  grandpa->color = RED;
	  rbtree_rotate_left(tree, grandpa);
	}
  }

  tree->root->color = BLACK;
  return new_node;
}

void *rbtree_lookup(struct rbtree *tree, struct rbtree_node *node) {
  struct rbtree_node *cur_node = tree->root;
  while (cur_node) {
	int compare_flag = tree->compare_cb(node, cur_node);
	if (compare_flag == 0) {
	  return cur_node;
	} else if (compare_flag < 0) {
	  cur_node = cur_node->left;
	} else {
	  cur_node = cur_node->right;
	}
  }
  return NULL;
}

void *rbtree_lookup2(struct rbtree *tree, void *key, int (*compare_fn)(void *key, void *tree_node)) {
  struct rbtree_node *cur_node = tree->root;
  while (cur_node) {
	int compare_flag = compare_fn(key, cur_node);
	if (compare_flag == 0) {
	  return cur_node;
	} else if (compare_flag < 0) {
	  cur_node = cur_node->left;
	} else {
	  cur_node = cur_node->right;
	}
  }
  return NULL;
}

static void rbtree_erase(struct rbtree *tree, struct rbtree_node *node, struct rbtree_node *parent) {
  struct rbtree_node *other;
  while ((!node || node->color != RED) && node != tree->root) {
	if (parent->left == node) {
	  other = parent->right;
	  if (other->color == RED) {
		other->color = BLACK;
		parent->color = RED;
		rbtree_rotate_left(tree, parent);
		other = parent->right;
	  }

	  if ((!other->left || other->left->color != RED) && (!other->right || other->right->color != RED)) {
		other->color = RED;
		node = parent;
		parent = node->parent;
	  } else {
		if (!other->right || other->right->color != RED) {
		  struct rbtree_node *o_left;
		  if ((o_left = other->left))
			o_left->color = BLACK;
		  other->color = RED;
		  rbtree_rotate_right(tree, other);
		  other = parent->right;
		}

		other->color = parent->color;
		parent->color = BLACK;
		if (other->right)
		  other->right->color = BLACK;
		rbtree_rotate_left(tree, parent);
		node = tree->root;
		break;
	  }
	} else {
	  other = parent->left;
	  if (other->color == RED) {
		other->color = BLACK;
		parent->color = RED;
		rbtree_rotate_right(tree, parent);
		other = parent->left;
	  }

	  if ((!other->left || other->left->color != RED) && (!other->right || other->right->color != RED)) {
		other->color = RED;
		node = parent;
		parent = node->parent;
	  } else {
		if (!other->left || other->left->color != RED) {
		  struct rbtree_node *o_right;
		  if ((o_right = other->right))
			o_right->color = BLACK;
		  other->color = RED;
		  rbtree_rotate_left(tree, other);
		  other = parent->left;
		}

		other->color = parent->color;
		parent->color = BLACK;
		if (other->left)
		  other->left->color = BLACK;
		rbtree_rotate_right(tree, parent);
		node = tree->root;
		break;
	  }
	}
  }

  if (node)
	node->color = BLACK;
}

void rbtree_remove(struct rbtree *tree, struct rbtree_node *node) {
  struct rbtree_node *child, *parent;
  enum rbtree_node_color color;

  if (node->parent == node) {
	return;
  }

  if (!node->left) {
	child = node->right;
  } else if (!node->right) {
	child = node->left;
  } else {
	struct rbtree_node *old = node;
	struct rbtree_node *left;

	node = node->right;
	while ((left = node->left))
	  node = left;
	child = node->right;
	parent = node->parent;
	color = node->color;

	if (child)
	  child->parent = parent;
	if (parent) {
	  if (parent->left == node)
		parent->left = child;
	  else
		parent->right = child;
	} else {
	  tree->root = child;
	}

	if (node->parent == old)
	  parent = node;
	*node = *old;

	if (old->parent) {
	  if (old->parent->left == old)
		old->parent->left = node;
	  else
		old->parent->right = node;
	} else {
	  tree->root = node;
	}

	old->left->parent = node;
	if (old->right)
	  old->right->parent = node;
	if (color != RED)
	  rbtree_erase(tree, child, parent);
	return;
  }
  parent = node->parent;
  color = node->color;

  if (child)
	child->parent = parent;

  if (parent) {
	if (parent->left == node)
	  parent->left = child;
	else
	  parent->right = child;
  } else {
	tree->root = child;
  }

  if (color != RED)
	rbtree_erase(tree, child, parent);
}

struct rbtree_node *rbtree_first(struct rbtree *tree) {
  struct rbtree_node *p = tree->root;
  if (!p) {
	return NULL;
  }
  while (p->left)
	p = p->left;
  return p;
}

struct rbtree_node *rbtree_last(struct rbtree *tree) {
  struct rbtree_node *p = tree->root;
  if (!p) {
	return NULL;
  }
  while (p->right)
	p = p->right;
  return p;
}

struct rbtree_node *rbtree_next(struct rbtree_node *node) {
  if (node->right) {
	node = node->right;
	while (node->left)
	  node = node->left;
	return node;
  }

  while (node->parent && node == node->parent->right)
	node = node->parent;
  return node->parent;
}

struct rbtree_node *rbtree_prev(struct rbtree_node *node) {
  if (node->left) {
	node = node->left;
	while (node->right)
	  node = node->right;
	return node;
  }

  while (node->parent && node == node->parent->left)
	node = node->parent;
  return node->parent;
}

void rbtree_node_replace(struct rbtree *tree, struct rbtree_node *dst, struct rbtree_node *src) {
  struct rbtree_node *parent = src->parent;
  if (parent) {
	if (parent->left == src)
	  parent->left = dst;
	else
	  parent->right = dst;
  } else {
	tree->root = dst;
  }

  if (src->left)
	src->left->parent = dst;
  if (src->right)
	src->right->parent = dst;
}
