#include <stdlib.h>
#include <string.h>
#include <stdio.h>

 int *add(int *old_arr, int value) {
    int old_size = sizeof(old_arr) / sizeof(old_arr[0]) + 1;
    printf("old_size: %d\n", old_size);
    int *new_arr = malloc(sizeof(old_arr) + sizeof(int));
    for (int i = 0; i < old_size; i++) {
        new_arr[i] = old_arr[i];
    }
    new_arr[old_size] = value;
    // old_arr = new_arr;
    return new_arr;
}

int main() {
    int arr[] = { 1, 2, 3 };
    
    int *new_arr0 = add(arr, 5);
    int *new_arr1 = add(new_arr0, 10);
    // int *new_arr1 = add(new_arr0, 9);
    // int *new_arr2 = add(new_arr1, 12);
    
    for (int i = 0; i < 4; i++) {
        printf("%d\n", new_arr1[i]);
    }
    
    return 0;
}