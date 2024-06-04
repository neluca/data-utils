cmake_minimum_required(VERSION 3.23)
project(data_utils C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(rbtree_test
        rbtree_test.c
        rbtree.c
        rbtree.h)

add_executable(rb_map_test
        rbtree.c
        rbtree.h rb_map_test.c)

add_executable(heap_test heap_test.c heap.c heap.h)

add_executable(list_test list.h list_test.c)

add_executable(bitmap_test bitmap_test.c)
