#include <stdio.h>
#include <stdlib.h>

// Exercise 5 — Heap Memory (malloc & free)
//
// Concept: So far all your variables lived on the stack — automatically
// allocated when a function is called and destroyed when it returns.
// The heap is different: you manually request memory with malloc() and
// manually release it with free(). This gives you control over how long
// memory lives, but also responsibility — if you forget to free, you get
// a memory leak.
//
// malloc(n) — allocates n bytes on the heap, returns a void* pointer to it
// free(p)   — releases the memory at pointer p back to the OS
//
// Tasks:
// 1. Use malloc to allocate space for a single int on the heap
// 2. Assign a value to it through the pointer and print it
// 3. Free it when done
// 4. Use malloc to allocate an array of 5 ints on the heap
// 5. Fill it with values using a loop and print each element
// 6. Free the array when done
//
// Goal: understand the difference between stack and heap memory,
// and build the habit of always freeing what you allocate.

int main() {
    int* p = malloc(sizeof(int));
    *p = 10;
    printf("p holds the value: %d\n", *p);
    free(p);
    p = NULL;

    int* arr = malloc(sizeof(int)*5);
    
    for(int i = 0; i < 5; i++) {
        arr[i] = i;
        printf("number at index %d: %d\n", i, arr[i]);
    }

    free(arr);
    arr = NULL;
}