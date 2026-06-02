#include <stdio.h>

// Exercise 10 — Bit Manipulation
//
// Concept: At the lowest level, everything is bits. Bit manipulation lets
// you work directly with individual bits inside an integer. This is essential
// for networking (IP addresses, TCP flags, subnet masks), OS work (permissions,
// status flags), and kernel/driver code.
//
// Operators:
//   &   AND  — 1 only if both bits are 1       (used to mask/check bits)
//   |   OR   — 1 if either bit is 1            (used to set bits)
//   ^   XOR  — 1 if bits are different         (used to toggle bits)
//   ~   NOT  — flips all bits
//   <<  left shift  — shifts bits left  (multiply by 2)
//   >>  right shift — shifts bits right (divide by 2)
//
// Example — checking if bit 3 is set:
//   int flags = 0b00001010;
//   if (flags & (1 << 3)) { ... }   // 1<<3 == 0b00001000
//
// Tasks:
// 1. Declare an unsigned int with value 0b00001111 (binary literal)
//    Print it with %u
// 2. Set bit 5 using OR, print the result
// 3. Clear bit 1 using AND + NOT, print the result
// 4. Toggle bit 0 using XOR, print the result
// 5. Left shift the original value by 2, print the result — what happened to the value?
// 6. Write a function is_bit_set(int val, int bit) that returns 1 if that bit is set, 0 if not
//    Test it on a few values
//
// Goal: get comfortable reading and writing individual bits — you will use
// this constantly in networking and OS work.

int is_bit_set(int val, int bit) {
    return (val & 1 << bit) != 0;
}

int main(){
    u_int16_t x = 0b00001111;
    printf("%u\n", x);
    x = x | (1 << 5);
    printf("%u\n", x);
    x = x & ~(1 << 1);
    printf("%u\n", x);
    x = x ^ 1;
    printf("%u\n", x);
    x = 0b00001111;
    x = x << 2; // multiply x by 4
    printf("%u\n", x); 

    printf("%d\n", is_bit_set(5,2));
}

