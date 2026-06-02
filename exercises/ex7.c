#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exercise 7 — Structs
//
// Concept: A struct lets you group related variables under one name.
// It's the foundation of almost every data structure in C — linked lists,
// trees, network packets, OS structures. Under the hood it's just a
// contiguous block of memory with named fields.
//
//   struct Point {
//       int x;
//       int y;
//   };
//
// You can access fields with dot notation: p.x
// If you have a pointer to a struct, use arrow notation: ptr->x
// (ptr->x is just shorthand for (*ptr).x)
//
// Tasks:
// 1. Define a struct called Person with fields: name (char[50]), age (int)
// 2. Create a Person on the stack, assign values to its fields, and print them
// 3. Create a Person on the heap using malloc, assign values, print, then free
// 4. Write a function print_person that takes a pointer to a Person and prints its fields
//    — call it with both your stack and heap Person
//
// Goal: understand structs as grouped memory, and practice using
// dot vs arrow notation and passing structs by pointer.

struct Person
{
    char name[50];
    int age;
};

void print_person(struct Person* p) {
    printf("Name: %s\nAge: %d\n", p->name, p->age);
}


int main() {

    struct Person p1;
    strcpy(p1.name, "John Doe");
    p1.age = 11;

    print_person(&p1);


    struct Person* p2 = malloc(sizeof(struct Person));
    p2->age = 25;
    strcpy(p2->name, "Fred");
    print_person(p2);
    free(p2);

    return 0;
}