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

#ifndef SRC_UTILS_LIST_H_
#define SRC_UTILS_LIST_H_

struct list_node {
  struct list_node *prev;
  struct list_node *next;
};

typedef struct list_node list_t;

#define list_entry(entry, type, node_member) \
    ((type *) ((char *)(entry) - offsetof(type, node_member)))

static inline void list_init(list_t *h) {
  h->next = h;
  h->prev = h;
}

static inline void list_node_init(struct list_node *node) {
  node->next = node;
  node->prev = node;
}

static inline int list_empty(list_t *h) {
  return h == h->next;
}

static inline struct list_node *list_head(list_t *h) {
  return h->next;
}

static inline void list_insert_head(list_t *h, struct list_node *q) {
  q->next = h->next;
  q->prev = h;
  q->next->prev = q;
  h->next = q;
}

static inline void list_insert_tail(list_t *h, struct list_node *q) {
  q->next = h;
  q->prev = h->prev;
  q->prev->next = q;
  h->prev = q;
}

static inline void list_remove(struct list_node *q) {
  q->prev->next = q->next;
  q->next->prev = q->prev;
}

static inline int list_in(struct list_node *q) {
  return q->prev != q && q->prev->next == q;
  // or q->next != q && && q->next->prev == q
}

// h为链表头，q为自定义节点指针
#define list_foreach(h, q) for ((q) = (h)->next; (q) != (h); (q) = (q)->next)

#endif  /* SRC_UTILS_LIST_H_ */
