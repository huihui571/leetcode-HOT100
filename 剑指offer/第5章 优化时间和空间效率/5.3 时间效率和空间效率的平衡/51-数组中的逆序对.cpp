/*<FH+>***************************************************************
*   Editor      : CLion
*   File name   : 51-数组中的逆序对.cpp
*   Author      : huihui571
*   Created date: 2020-12-31
*   Description : 在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。
*
*<FH->***************************************************************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

/**
 * 归并排序模板，分而治之
 */
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if (nums.size() < 2)
            return 0;
        vector<int> helper(nums.size());
        return mergeSort(nums, 0, nums.size() - 1, helper);
    }

    int mergeSort(vector<int>& nums, int start, int end, vector<int>& helper) {
        if (end <= start)
            return 0;

        int mid = (start + end) >> 1;
        //左右内部的逆序对数量
        int count = mergeSort(nums, start, mid, helper) + mergeSort(nums, mid + 1, end, helper);

        //加速，这种情况下不存在左右之间的逆序对了
        if (nums[mid] <= nums[mid + 1])
            return count;

        //左右之间的逆序对数量
        int j = mid + 1;
        for (int i = start; i <= mid; ++i) {
            //Note:因为左右两部分都是排序的，因此i和后面的组成逆序对，那么i+1..mid和后面也一定都组成对，所以j不需要每次更新重新计算，这里的复杂度才变成O(n)的
            while (j <= end && nums[i] > nums[j])
                j++;
            count += j - (mid + 1);
        }

        merge(nums, start, mid, end, helper);
        return count;
    }

    //合并两个有序数组
    void merge(vector<int>& nums, int start, int mid, int end, vector<int>& helper) {
//        vector<int> helper(end - start + 1);    //辅助数组用全局变量而不是每次都创建可以加速 Note:如果指针从后往前比较，(如果原数组后面有空余空间的话)是可以在原数组上操作，达到O(1)的空间复杂度合并的。

        int i = start, j = mid + 1, k = start;
        while (i <= mid && j <= end) {
            helper[k++] = nums[i] < nums[j] ? nums[i++] : nums[j++];
        }
        while (i <= mid) helper[k++] = nums[i++];
        while (j <= end) helper[k++] = nums[j++];

//        copy(helper.begin(), helper.end(), nums.begin() + start);
        for (int p = start; p <= end; ++p) {
            nums[p] = helper[p];
        }
    }
};