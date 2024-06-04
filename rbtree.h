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

#ifndef UTILS_RBTREE_H_
#define UTILS_RBTREE_H_

#include <stddef.h>
#define RBTREE_LEFT  (-1)
#define RBTREE_RIGHT  1

enum rbtree_node_color { RED = 0, BLACK };

struct rbtree_node {
  struct rbtree_node *parent;
  struct rbtree_node *left;
  struct rbtree_node *right;
  enum rbtree_node_color color;
};

// left == right return 0
// left < right return RBTREE_LEFT
// left > right return RBTREE_RIGHT
typedef int (*rbtree_node_compare_fn)(void *left, void *right);

struct rbtree {
  struct rbtree_node *root;

  rbtree_node_compare_fn compare_cb;
};

// 插入之前一定要将node初始化
static inline void rbtree_node_init(struct rbtree_node *node) {
  node->color = RED;
  node->parent = node;
  node->left = NULL;
  node->right = NULL;
}

#define rbtree_entry(entry, type, node_member) \
    ((type *) ((char *)(entry) - offsetof(type, node_member)))

void rbtree_init(struct rbtree *tree, rbtree_node_compare_fn compare_cb);
void *rbtree_insert(struct rbtree *tree, struct rbtree_node *new_node); // 注意插入 node_member 地址
void *rbtree_lookup(struct rbtree *tree, struct rbtree_node *node);
void *rbtree_lookup2(struct rbtree *tree, void *key, int (*compare_fn)(void *key, void *tree_node));
#define rbtree_lookup3(tree, key, compare_fn, type, node_member) \
    rbtree_entry(rbtree_lookup2(tree, key, compare_fn), type, node_member)

void rbtree_remove(struct rbtree *tree, struct rbtree_node *node);

struct rbtree_node *rbtree_first(struct rbtree *tree);
struct rbtree_node *rbtree_last(struct rbtree *tree);

struct rbtree_node *rbtree_next(struct rbtree_node *node);
struct rbtree_node *rbtree_prev(struct rbtree_node *node);

void rbtree_node_replace(struct rbtree *tree, struct rbtree_node *dst, struct rbtree_node *src);
#define rbtree_node_replace2(tree, dst, src, node_member) \
    *(dst) = *(src);                                      \
    rbtree_node_replace(tree, &((dst)->node_member), &((src)->node_member))

#endif  /* UTILS_RBTREE_H_ */
