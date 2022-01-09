//
// Created by zyl on 2020/3/27.
//

#include "sort.h"

/*****************************************************/
/* Do not consume extra space */
/*****************************************************/
void insertSort(vector<int> &nums) {
    for (int i = 0; i < nums.size(); i++) {
        for (int j = i-1; j >= 0; j--) {
            if (nums[j+1] < nums[j]) {
                // 如果比前一个元素小就交换位置
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}


/****************************************************************************/
/* Quick sort:  divide and conquer
 *              Note: do not use other vectors to store left and right */
/****************************************************************************/
void quickSortPart(vector<int>& nums, int low, int high) {
    /*if (low >= high)
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
    quickSortPart(nums, i+1, high);*/

    // Practice again
    if (low >= high) return;
    int i = low, j = high;
    int key = nums[key];
    while (i < j) {
        while (nums[j] >= key && i < j) {
            j--;
        }
        if (i < j) {
            nums[i] = nums[j];
            i++;
        }
        while (nums[i] < key && i < j) {
            i++;
        }
        if (i < j) {
            nums[j] = nums[i];
            j--;
        }
    }
    nums[i] = key;
    quickSortPart(nums, low, i - 1);
    quickSortPart(nums, i + 1, high);
}

void quickSort(vector<int>& nums) {
    int low = 0;
    int high = nums.size()-1;
    quickSortPart(nums, low, high);
}


/****************************************************************************/
/* Heap sort:   build a max heap, then delete the root node and update heap
 *              and in circulation */
/****************************************************************************/
void heapSort(vector<int>& nums) {
    if (nums.empty())
        return;
    if (nums.size() == 1)
        return;

    // build heap
    int L = nums.size();
    int i = L / 2 - 1;  // the position of current root node
    while (i >= 0) {
        int j = i; //
        while (true) {
            int next = 0;
            if (2 * j + 2 <= nums.size() - 1) {
                if (nums[2 * j + 2] >= nums[2 * j + 1])
                    next = 2 * j + 2;
                else
                    next = 2 * j + 1;
                if (nums[j] < nums[next]) {
                    // swap the value of root and child
                    int temp = nums[j];
                    nums[j] = nums[next];
                    nums[next] = temp;
                    j = next;
                } else
                    break;
            } else {
                if (2*j+1 == nums.size()-1) {
                    if (nums[2 * j + 1] > nums[j]) {
                        int temp = nums[j];
                        nums[j] = nums[2 * j + 1];
                        nums[2 * j + 1] = temp;
                    }
                }
                break;
            }
        }
        i--;
    }

    // swap the root and child at the end and then update
    int end = (int)nums.size() - 1;
    while (end > 0) {
        // update the tree;
        int temp = nums[0];
        nums[0] = nums[end];
        nums[end] = temp;
        i = 0;
        while (true) {
            if (2 * i + 2 <= end - 1) {
                int next = 0;
                if (nums[2 * i + 2] >= nums[2 * i + 1])
                    next = 2 * i + 2;
                else
                    next = 2 * i + 1;
                if (nums[i] < nums[next]) {
                    temp = nums[i];
                    nums[i] = nums[next];
                    nums[next] = temp;
                    i = next;
                } else
                    break;
            } else {
                if (2 * i + 1 == end - 1) {
                    if (nums[2 * i + 1] > nums[i]) {
                        temp = nums[i];
                        nums[i] = nums[2 * i + 1];
                        nums[2 * i + 1] = temp;
                    }
                }
                break;
            }
        }
        end--;
    }
}


// trick from leetcode answers
std::vector<int> sortArray(std::vector<int>& nums) {
    int minVal = INT_MAX, maxVAl = INT_MIN;

    for(int i = 0; i < nums.size(); i++){
        minVal = std::min(minVal, nums[i]);
        maxVAl = std::max(maxVAl, nums[i]);
    }

    std::vector<int> tem(maxVAl - minVal + 1, 0);

    for(int i = 0 ; i < nums.size(); i++){
        tem[nums[i] - minVal]++;
    }

    int index = 0;
    for(int i = 0; i < tem.size(); i++){
        while(tem[i]--){
            nums[index++] = i + minVal;
        }
    }

    return nums;
}
