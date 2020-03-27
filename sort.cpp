//
// Created by zyl on 2020/3/27.
//

#include "sort.h"


/****************************************************************************/
/* Quick sort:  divide and conquer
 *              Note: do not use other vectors to store left and right */
/****************************************************************************/
void quickSortPart(vector<int>& nums, int low, int high) {
    if (low >= high)
        return;
    int i = low;
    int j = high;
    int key = nums[low];
    while (i < j) {
        while (i < j && nums[j] >= key)
            j--;
        if (i < j) {
            nums[i] = nums[j];  // when find an element that is larger smaller than key
            i++;                // current location move forward so that
            // the found element is on the left of key
        }
        while (i < j && nums[i] < key)
            i++;
        if (i < j) {
            nums[j] = nums[i];
            j--;
        }
    }
    nums[i] = key;
    quickSortPart(nums, low, i-1);
    quickSortPart(nums, i+1, high);
}

void quickSort(vector<int>& nums) {
    int low = 0;
    int high = nums.size()-1;
    quickSortPart(nums, low, high);
}