#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exercise 9 — File I/O
//
// Concept: In C, files are accessed through a FILE* pointer.
// The OS gives you a file descriptor and you read/write through it.
// This is the same mechanism behind sockets, pipes, and stdin/stdout —
// in Unix, everything is a file.
//
// Key functions:
//   fopen(path, mode)   — opens a file, returns FILE* (NULL on failure)
//   fprintf(fp, ...)    — write formatted text to a file
//   fgets(buf, n, fp)   — read a line from a file into a buffer
//   fclose(fp)          — close the file
//
// Modes: "r" = read, "w" = write (creates/truncates), "a" = append
//
// Always check if fopen returns NULL — it means the file couldn't be opened.
// Always fclose what you fopen.
//
// Tasks:
// 1. Open a file called "data.txt" for writing
// 2. Write at least 3 lines of text to it using fprintf
// 3. Close the file
// 4. Reopen the same file for reading
// 5. Read and print each line using fgets in a loop — stop at end of file
// 6. Close the file
//
// Goal: understand file I/O as the same pointer/handle pattern you've
// already used, and see how fgets + a loop replaces manual indexing.

int main() {

    FILE* file = fopen("data.txt","w");
    if(file == NULL) {return -1;}

    fprintf(file, "Hello\n");
    fprintf(file,"I am writing to data.txt\n");
    fprintf(file, "from ex9.c\n");
    fclose(file);


    file = fopen("data.txt","r");
    if(file == NULL) {return -1;}
    char buf[100];
    while(fgets(buf, sizeof(buf), file) != NULL) {
        printf("%s", buf);
    }

    fclose(file);

    return 0;
}