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

#include "heap.h"

void heap_init(struct heap *heap, heap_compare_fn compare_cb) {
  heap->root = NULL;
  heap->num_elements = 0;

  heap->compare_cb = compare_cb;
}

static inline void heap_node_swap(struct heap *heap, struct heap_node *parent, struct heap_node *child) {
  struct heap_node *sibling;
  register struct heap_node tmp;

  tmp = *parent;
  *parent = *child;
  *child = tmp;

  parent->parent = child;
  if (child->left == child) {
	child->left = parent;
	sibling = child->right;
  } else {
	child->right = parent;
	sibling = child->left;
  }
  if (sibling)
	sibling->parent = child;

  if (!child->parent)
	heap->root = child;
  else if (child->parent->left == parent)
	child->parent->left = child;
  else
	child->parent->right = child;

  if (parent->left)
	parent->left->parent = parent;
  if (parent->right)
	parent->right->parent = parent;
}

void heap_push(struct heap *heap, struct heap_node *new_node) {
  new_node->parent = NULL;
  new_node->left = NULL;
  new_node->right = NULL;

  size_t path = 0;
  size_t k = 0;
  size_t n = 1 + heap->num_elements;

  for (; n >= 2; ++k, n >>= 1) {
	path <<= 1;
	path |= (n & 1);
  }

  struct heap_node **parent = &heap_top(heap);
  struct heap_node **child = &heap_top(heap);

  while (k > 0) {
	parent = child;
	if (path & 1)
	  child = &((*child)->right);
	else
	  child = &((*child)->left);
	path >>= 1;
	--k;
  }

  new_node->parent = *parent;
  *child = new_node;
  heap->num_elements++;

  struct heap_node *cur_node = new_node;
  while (cur_node->parent && heap->compare_cb(cur_node, cur_node->parent))
	heap_node_swap(heap, cur_node->parent, cur_node);
}

void heap_remove(struct heap *heap, struct heap_node *node) {
  if (heap->num_elements == 0)
	return;

  size_t path = 0;
  size_t k = 0;
  size_t n = heap->num_elements;

  for (; n >= 2; ++k, n >>= 1) {
	path <<= 1;
	path |= (n & 1);
  }

  struct heap_node **p_leaf_node = &heap_top(heap);
  while (k > 0) {
	if (path & 1)
	  p_leaf_node = &((*p_leaf_node)->right);
	else
	  p_leaf_node = &((*p_leaf_node)->left);
	path >>= 1;
	--k;
  }

  heap->num_elements--;

  struct heap_node *replace_node = *p_leaf_node;
  *p_leaf_node = NULL;

  if (replace_node == node) {
	if (replace_node == heap_top(heap))
	  heap->root = NULL;
	return;
  }

  *replace_node = *node;

  if (!node->parent)
	heap->root = replace_node;
  else if (node->parent->left == node)
	node->parent->left = replace_node;
  else
	node->parent->right = replace_node;

  if (node->left)
	replace_node->left->parent = replace_node;
  if (node->right)
	replace_node->right->parent = replace_node;

  struct heap_node *cur_node;
  for (;;) {
	cur_node = replace_node;
	if (replace_node->left && heap->compare_cb(replace_node->left, cur_node))
	  cur_node = replace_node->left;
	if (replace_node->right && heap->compare_cb(replace_node->right, cur_node))
	  cur_node = replace_node->right;
	if (cur_node == replace_node)
	  break;
	heap_node_swap(heap, replace_node, cur_node);
  }
  cur_node = replace_node;
  while (cur_node->parent && heap->compare_cb(cur_node, cur_node->parent))
	heap_node_swap(heap, cur_node->parent, cur_node);
}

void heap_pop(struct heap *heap) {
  size_t path = 0;
  size_t k = 0;
  size_t n = heap->num_elements;

  for (; n >= 2; ++k, n >>= 1) {
	path <<= 1;
	path |= (n & 1);
  }

  struct heap_node **p_leaf_node = &heap_top(heap);
  while (k > 0) {
	if (path & 1)
	  p_leaf_node = &((*p_leaf_node)->right);
	else
	  p_leaf_node = &((*p_leaf_node)->left);
	path >>= 1;
	--k;
  }

  heap->num_elements--;

  struct heap_node *node = heap_top(heap);
  struct heap_node *replace_node = *p_leaf_node;
  *p_leaf_node = NULL;

  if (replace_node == node) {
	heap->root = NULL;
	return;
  }

  *replace_node = *node;
  heap->root = replace_node;
  if (replace_node->left)
	replace_node->left->parent = replace_node;
  if (replace_node->right)
	replace_node->right->parent = replace_node;

  struct heap_node *cur_node;
  for (;;) {
	cur_node = replace_node;
	if (replace_node->left && heap->compare_cb(replace_node->left, cur_node))
	  cur_node = replace_node->left;
	if (replace_node->right && heap->compare_cb(replace_node->right, cur_node))
	  cur_node = replace_node->right;
	if (cur_node == replace_node)
	  break;
	heap_node_swap(heap, replace_node, cur_node);
  }
  cur_node = replace_node;
  while (cur_node->parent && heap->compare_cb(cur_node, cur_node->parent))
	heap_node_swap(heap, cur_node->parent, cur_node);
}
