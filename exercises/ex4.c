#include <stdio.h>

// Exercise 4 — Functions & the Stack
//
// Concept: Every function call creates a stack frame — a block of memory
// holding local variables and the return address. When the function returns,
// the frame is destroyed. This is why local variables don't persist between
// calls, and it's the foundation of buffer overflows.
//
// Tasks:
// 1. Write a function `add` that takes two ints and returns their sum
// 2. Write a function `square` that takes an int and returns its square
// 3. Write a function `swap` that takes two int pointers and swaps their values
// 4. In main, call all three and print the results
// 5. For swap — print both variables before and after to prove it worked
//
// Goal: understand pass-by-value vs pass-by-pointer, and why a pointer
// is needed to modify a caller's variable.


int add(int a, int b) {
    return a + b;
}

int square(int a) {
    return a * a;
}

void swap(int *a ,int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    printf("add function result: %d\n" , add(2,3));
    printf("square function result: %d\n" , square(3));
    
    int a = 6;
    int b = 7;
    

    printf("a before swapping: %d\nb before swapping: %d\n", a, b);
    swap(&a,&b);
    printf("a after swapping: %d\nb after swapping: %d\n", a, b);
    return 0;
}