#include <stdio.h>
#include <stdlib.h>

int is_key_present(int** arr, int n, int key) {
    int rw = 0;
    int col = n - 1;
    while (rw < n && col >= 0) {
        if (*(*(arr + rw) + col) == key) {
            return 1;
        } else if (*(*(arr + rw) + col) < key) {
            rw++;
        } else {
            col--;
        }
    }
    return 0;
}

int main() {
    int n ;
    printf("enter the val for n nxn: ");
    scanf("%d",&n);
    int** arr = (int**)malloc(n * sizeof(int*));
    for (int rw = 0; rw < n; rw++) {
        *(arr + rw) = (int*)malloc(n * sizeof(int));
        for (int col = 0; col < n; col++) {
            scanf("%d", (*(arr + rw) + col));
        }
    }

    int key ;
    printf("enter the value for key to serh: ");
    scanf("%d",&key);
    if (is_key_present(arr, n, key)) {
        printf("\nKey %d presnt\n", key);
    } else {
        printf("\nKey %d not presnt\n", key);
    }

    for (int rw = 0; rw < n; rw++) {
        free(*(arr + rw));
    }
    free(arr);

    return 0;
}
