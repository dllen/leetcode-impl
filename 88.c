// 合并2个有序数组
//

#include <stdio.h>
#include <stdlib.h>

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) 
{
    // define array
    int* array = (int*)malloc((m + n) * sizeof(int));
    int i = 0;
    int j = 0;
    int k = 0;
    while(i < m && j < n) {
        if(nums1[i] < nums2[j]) {
            array[k++] = nums1[i++];
        } else {
            array[k++] = nums2[j++];
        }
    }

    while(i < m) {
        array[k++] = nums1[i++];
    }

    while(j < n) {
        array[k++] = nums2[j++];
    }

    // Copy merged result back to nums1
    for(int idx = 0; idx < m + n; idx++) {
        nums1[idx] = array[idx];
    }
    
    // Free temporary array
    free(array);
}

int main()
{
    int nums1[] = {1, 2, 3, 0, 0, 0};
    int nums2[] = {2, 5, 6};
    merge(nums1, 6, 3, nums2, 3, 3);
    for(int i = 0; i < 6; i++) {
        printf("%d ", nums1[i]);
    }
    return 0;
}
