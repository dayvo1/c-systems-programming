#include <stdio.h>
#include <string.h>

// Exercise 6 — Strings
//
// Concept: C has no built-in string type. A string is just an array of chars
// ending with a null terminator '\0'. That's how C knows where the string ends.
//
//   char s[] = "hi";  →  ['h']['i']['\0']
//
// The standard library (string.h) gives you functions to work with them:
//   strlen(s)        — number of chars (not counting '\0')
//   strcpy(dst, src) — copy src into dst
//   strcat(dst, src) — append src onto dst
//   strcmp(a, b)     — compare two strings (0 = equal)
//
// Tasks:
// 1. Declare a string using char[] and print it
// 2. Print its length using strlen
// 3. Declare a second string and concatenate them using strcat, print the result
// 4. Compare two strings using strcmp and print whether they are equal or not
// 5. Manually loop over the string char by char and print each character
//    — this shows you what a string actually is under the hood
//
// Goal: understand that strings are just memory — a char array with a '\0' at the end.

int main() {
   char c1[20] = "hi";
   printf("%s\n", c1);
   printf("%lu\n", strlen(c1));

   char c2[] = " , how are you?";
   strcat(c1, c2);
   printf("%s\n" , c1);
   printf("%d\n", strcmp(c1,c2));
   for(int i = 0; i < strlen(c1); i++) {
    printf("%c", c1[i]);
   }
   printf("\n");
}