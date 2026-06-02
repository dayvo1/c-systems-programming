#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exercise 8 — Linked List
//
// Concept: A linked list is a chain of nodes where each node holds
// a value and a pointer to the next node. Unlike arrays, nodes don't
// need to be contiguous in memory — the pointers connect them.
//
//   [data|next] -> [data|next] -> [data|next] -> NULL
//
// The last node's next pointer is NULL — that's how you know you've
// reached the end.
//
// This is your first real data structure in C. It combines everything
// you've learned: structs, pointers, malloc, and free.
//
// Tasks:
// 1. Define a struct Node with fields: int data, struct Node* next
// 2. Write a function create_node(int data) that mallocs a new Node,
//    sets its data and next (next should be NULL), and returns a pointer to it
// 3. In main, create 3 nodes and link them together manually using the next pointers
// 4. Write a function print_list(struct Node* head) that traverses the list
//    and prints each node's data — stop when next is NULL
// 5. Free all 3 nodes when done
//
// Goal: understand how pointers connect structs into a data structure,
// and practice traversing a chain of pointers.


struct Node
{
    int data;
    struct Node* next;
};

struct Node* create_node(int data) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list(struct Node* head) {
    while (head != NULL)
    {
        printf("%d\n",head->data);
        head = head->next;
    }
    
}

int main() {
    struct Node* n1 = create_node(1);
    struct Node* n2 = create_node(2);
    struct Node* n3 = create_node(3);


    n1->next = n2;
    n2->next = n3;

    print_list(n1);

    free(n1);
    free(n2);
    free(n3);


    return 0;
}
