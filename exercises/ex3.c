#include <stdio.h>

int main() {
    int arr[5] = {1,2,3,4,5};

    for(int i = 0; i < 5; i++) {
        printf("number at index %d is: %d\n", i, arr[i]);
        printf("address of number at index %d is: %p\n", i, &arr[i]);
    }

    printf("address of arr: %p\n" , arr);
    int idx_2 = *(arr + 2);
    printf("number at index 2: %d\n" , idx_2);

    return 0;
}