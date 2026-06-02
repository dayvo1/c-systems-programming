#include <stdio.h>

int main() {

    int x = 11;
    int* p = &x;

    printf("value of x: %d\naddress of x:%p\nvalue of x through pointer p: %d\n", x, p, *p);
    
    *p = 3;
    printf("new value of x changed throug pointer: %d\n", *p);
    return 0;
}