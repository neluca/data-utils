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

#ifndef SRC_UTILS_HEAP_H_
#define SRC_UTILS_HEAP_H_

#include <stddef.h>

struct heap_node {
  struct heap_node *parent;
  struct heap_node *left;
  struct heap_node *right;
};

// > 大顶堆
// < 小顶堆
typedef int (*heap_compare_fn)(const void *a, const void *b);

struct heap {
  struct heap_node *root;
  size_t num_elements;

  heap_compare_fn compare_cb;
};

#define heap_top(heap) ((heap)->root)
#define heap_top_entry(heap, type, node_member)   \
    ((type *) ((char *)(heap_top(heap)) - offsetof(type, node_member)))

#define heap_node_entry(entry, type, node_member) \
    ((type *) ((char *)(entry) - offsetof(type, node_member)))

void heap_init(struct heap *heap, heap_compare_fn compare_cb);
void heap_push(struct heap *heap, struct heap_node *new_node);
void heap_remove(struct heap *heap, struct heap_node *node);
// pop 之前要确保heap有数据
void heap_pop(struct heap *heap);

#endif  /* SRC_UTILS_HEAP_H_ */
