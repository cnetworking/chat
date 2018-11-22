#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int *add(int *old_arr, int value) {
    int old_size = sizeof(old_arr) / sizeof(old_arr[0]);
    int *new_arr = malloc(sizeof(old_arr) + sizeof(value));
    for (int i = 0; i < old_size; i++) {
        new_arr[i] = old_arr[i];
    }
    // new_arr[old_size + 1] = value;
    return new_arr;
}

int main() {
    int arr[] = { 1, 2, 3 };
    int *new_arr = add(arr, 10);
    
    for (int i = 0; i < 4; i++) {
        printf("%d\n", new_arr[i]);
    }
    
    return 0;
}