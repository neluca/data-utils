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

#ifndef UTILS_BITMAP_H_
#define UTILS_BITMAP_H_

#include <stdint.h>
#include <string.h>

typedef uint8_t bitmap_t;

#define bitmap_size(num)        (((num) >> 3) + 1)
#define bitmap_get_f(_map, i)   ((_map[(i) >> 3] >> ((i) & 7)) & 1)
#define bitmap_set_1(_map, i)   do { _map[((i) >> 3)] |= (1 << ((i) & 7)); } while(0)
#define bitmap_set_0(_map, i)   do { _map[((i) >> 3)] &= ~(1 << ((i) & 7)); } while(0)
#define bitmap_clear(_map, num) do { memset(_map, 0, bitmap_size(num)); } while(0)

#endif  /* UTILS_BITMAP_H_ */
