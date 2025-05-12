#include <stdio.h>

void rear_eve_odd(int *arr, int n) {
    int i = 0, j = 0;
   
    while (i < n) {
        
        if (!(*(arr + i) & 1)) {  
            i++;
        } else {
            j = (j > i + 1) ? j : i + 1;
            while (j < n && (*(arr + j) & 1)) {  
                j++;
            }
            if (j == n) {
                break;
            }
            int even = *(arr + j);
            for (int k = j; k > i; k--) {
                *(arr + k) = *(arr + k - 1);
            }
            *(arr + i) = even;
            i++;
            j++;
        }
    }
}

int main() {
    int arr[] = {1, 3, 4, 5, 6, 8, 2, 0,7,792,1211,5021};
    int n = sizeof(arr) / sizeof(arr[0]);
   
    rear_eve_odd(arr, n);
   
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
