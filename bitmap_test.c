#include <stdio.h>
#include "bitmap.h"

int main() {
  bitmap_t bitmap[bitmap_size(10)];
  bitmap_clear(bitmap, 10);

  bitmap_set_1(bitmap, 9);
  bitmap_set_0(bitmap, 9);
  int c = bitmap_get_f(bitmap, 9);
  printf("%d\n", c);


  printf("%d\n\n", bitmap[1]);
  return 0;
}