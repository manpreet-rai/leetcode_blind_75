// Basic IO
#include <iostream>
#include <bitset>

// Containers
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Libraries
#include <algorithm>

// Additional
#include <cstdint>

using namespace std;

/// Arrays

/**
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
 * You may assume that each input would have exactly one solution, and you may not use the same element twice.
 * You can return the answer in any order.
 * Time complexity: O(N).
 * Space complexity: O(N).
 * @see https://leetcode.com/problems/two-sum/
 * @param nums
 * @param target
 * @return vector<int>: indices of numbers who's sum equals target.
 */
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> m;

    for (int i = 0; i != nums.size(); ++i) {
        if (const auto j = m.find(target - nums[i]); j != m.cend()) return {j->second, i};
        m[nums[i]] = i;
    }

    return {};
}


/**
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.
 * You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
 * Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
 * Time complexity: O(N).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * @param prices
 * @return int: max profit.
 */
int maxProfit(vector<int>& prices) {
    /**
     * Approach 1:
        int max_profit = 0;
        for (int i = 0, j = 1; j < prices.size(); ++j) {
            if (prices[i] < prices[j]) max_profit = max(max_profit, prices[j] - prices[i]);
            else i = j;
        }
        return max_profit;
     */

    /**
     * Approach 2:
        int mp = 0;
        for (auto i = prices.cbegin(), j = next(i); j < prices.cend(); ++j) {
            if(*i < *j) mp = max(mp, *j - *i);
            else i = j;
        }
        return mp;
     */

    /**
     * Approach 3:
     */
    int min_price = prices[0], max_profit = 0;
    for (int i = 1; i < prices.size(); ++i) {
        min_price = min(min_price, prices[i]);
        max_profit = max(max_profit, prices[i] - min_price);
    }
    return max_profit;
}


/**
 * Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
 * @see https://leetcode.com/problems/contains-duplicate
 * @param nums
 * @return bool: true if duplicate exists/ false otherwise.
 */
bool containsDuplicate(vector<int>& nums) {
    /**
     * Approach 1:
     * Time complexity: O(N).
     * Space complexity: O(N).
     */
        unordered_set<int> s;
        for (auto num : nums) {
            if (const auto j = s.find(num); j != s.cend()) return true;
            s.insert(num);
        }

        return false;

    /**
     * Approach 2:
     * Time complexity: O(N * Log N).
     * Space complexity: O(1).
        sort(nums.begin(), nums.end());
        for (int i = 0; i != nums.size() - 1; ++i) {
            if (nums[i] == nums[i+1]) return true;
        }
        return false;
    */
}


/**
 * Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
 * The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
 * You must write an algorithm that runs in O(n) time and without using the division operation.
 * Time complexity: O(N).
 * Space complexity: O(N).
 * @see https://leetcode.com/problems/product-of-array-except-self
 * @param nums
 * @return vector<int>: products of elements except self.
 */
vector<int> productExceptSelf(vector<int>& nums) {
    /** Approach 1:
     */
        int n = (int) nums.size();
        vector<int> results (n, 1);
        int pre = 1, post = nums[n-1];

        for (int i = 0; i != n; ++i) {
            results[i] = pre;
            pre *= nums[i];
        }

        for (int i = n - 2; i != -1; --i) {
            results[i] *= post;
            post *= nums[i];
        }

        return results;

    /**
     * Approach 2:
     *
        vector<int> pre (nums.size()), post (nums.size()), results (nums.size());

        for (int i = 0, j = nums.size() - 1; i != nums.size() && j != -1; ++i, --j) {
            if (i == 0) pre[i] = nums[i];
            else pre[i] = nums[i] * pre[i-1];

            if (j == nums.size() - 1) post[j] = nums[j];
            else post[j] = nums[j] * post[j+1];
        }

        for (int i = 0; i != nums.size(); ++i) {
            if (i == 0) results[i] = post[i+1];
            else if (i == nums.size() - 1) results[i] = pre[i-1];
            else results[i] = pre[i-1] * post[i+1];
        }

        return results;
     */
}


/**
 * Given an integer array nums, find the subarray with the largest sum, and return its sum.
 * Time complexity: O(N).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/maximum-subarray
 * @param nums
 * @return int: max sub-array sum.
 */
int maxSubArray(vector<int>& nums) {
    int max_sum = nums[0], curr_sum = nums[0];

    for (int i = 1; i != nums.size(); ++i) {
        if (curr_sum < 0) curr_sum = 0;
        curr_sum += nums[i];
        max_sum = max(max_sum, curr_sum);
    }

    return max_sum;
}


/**
 * Given an integer array nums, find a subarray that has the largest product, and return the product.
 * Time complexity: O(N).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/maximum-product-subarray
 * @param nums
 * @return int: max product
 */
int maxProduct(vector<int>& nums) {
    int result = INT_MIN, min_prod = 1, max_prod = 1;
    for (int num : nums) {
        int curr_max = max_prod * num, curr_min = min_prod * num;
        max_prod = max(max(curr_max, curr_min), num);
        min_prod = min(min(curr_max, curr_min), num);

        result = max(result, max_prod);
        if (num == 0) { min_prod = max_prod = 1; }
    }

    return result;
}


/**
 * Given the sorted rotated array nums of unique elements, return the minimum element of this array.
 * Time complexity: O(log N).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/find-minimum-in-rotated-sorted-array
 * @param nums
 * @return int: minimum element
 */
int findMin(vector<int>& nums) {
    int left = 0, right = (int) nums.size() - 1;

    while(left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] > nums[right]) left = mid + 1;
        else right = mid;
    }
    return nums[left];
}


/**
 * Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
 * Time complexity: O(log N).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/search-in-rotated-sorted-array
 * @param nums
 * @param target
 * @return index of target/ or -1
 */
int searchRotated(vector<int>& nums, int target) {
    int left = 0, right = (int) nums.size() - 1;

    while(left != right) {
        int mid = (left + right) / 2;
        if(target == nums[mid]) return mid;

        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target <= nums[mid]) right = mid;
            else left = mid + 1;
        }
        else {
            if (nums[mid] <= target && target <= nums[right]) left = mid + 1;
            else right = mid;
        }
    }

    return nums[left] == target ? left : -1;
}


/**
 * Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
 * Time complexity: O(N^2).
 * Space complexity: O(N).
 * @see https://leetcode.com/problems/3sum
 * @param nums
 * @return triplets which sums zero each
 */
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    unordered_set<int> s;
    set<vector<int>> vs;
    vector<vector<int>> results {};

    for (int i = 0; i != nums.size() - 1; ++i) {
        if (auto it = s.find(nums[i]); it != s.cend()) continue;
        s.insert(nums[i]);

        int j = i + 1, k = nums.size() - 1;
        while (j != k) {
            if (nums[j] + nums[k] + nums[i] < 0) ++j;
            else if (nums[j] + nums[k] + nums[i] > 0) --k;
            else {
                vs.insert({nums[i], nums[j], nums[k]});
                ++j;
            }
        }
    }

    for (auto v : vs) results.push_back(v);
    return results;
}


/**
 * Find two lines that together with the x-axis form a container, such that the container contains the most water. Return the maximum amount of water a container can store.
 * Time complexity: O(N).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/container-with-most-water
 * @param height
 * @return max area
 */
int maxArea(vector<int>& height) {
    int i = 0, j = height.size() - 1, max_area = INT_MIN;

    while(i != j) {
        max_area = max(max_area, min(height[i], height[j]) * (j - i));
        if (height[i] < height[j]) ++i;
        else --j;
    }

    return max_area;
}

/// Binary (Bit Manipulation)

/**
 * Given two integers a and b, return the sum of the two integers without using the operators + and -.
 * Time complexity: O(1) or O(N), N is max number of bits in any number.
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/sum-of-two-integers
 * @param a
 * @param b
 * @return sum
 */
int getSum(int a, int b) {
    return b == 0 ? a : getSum(a^b, (a&b) << 1 );
}


/**
 * Write a function that takes the binary representation of an unsigned integer and returns the number of '1' bits it has (also known as the Hamming weight).
 * Time complexity: O(1) or O(N), N represents maximum bits that can be stored in input variable.
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/number-of-1-bits
 * @param n
 * @return number of 1s
 */
int hammingWeight(uint32_t n) {
    int count = 0;
    while(n) {
        n &= (n-1);
        ++count;
    }

    return count;
}


/**
 * Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
 * Time complexity: O(N).
 * Space complexity: O(N).
 * @see https://leetcode.com/problems/counting-bits
 * @param n
 * @return bit count vector
 */
vector<int> countBits(int n) {
    vector<int> results(n+1);
    results[0] = 0;

    for (int i = 1; i != n+1; ++i) results[i] = results[i/2] + i%2;
    return results;
}


/**
 * Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
 * Time complexity: O(N).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/missing-number
 * @param nums
 * @return missing number
 */
int missingNumber(vector<int>& nums) {
    int idealSum = 0, actualSum = 0;

    for(int i = 0; i != nums.size() + 1; ++i) {
        idealSum += i;

        if (i < nums.size()) actualSum += nums[i];
    }

    return idealSum - actualSum;
}


/**
 * Reverse bits of a given 32 bits unsigned integer.
 * Time complexity: O(1).
 * Space complexity: O(1).
 * @see https://leetcode.com/problems/reverse-bits
 * @param n
 * @return reversed number
 */
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i != 32; ++i) {
        res = (res << 1) | ((n >> i) & 1);
    }

    return res;
}


int main() {
    vector<int> nums {2,7,11,15};
    int target = 9;
    auto results = twoSum(nums, target);
    cout << "Two sum: " << results[0] << ':' << results[1] << '\n';

    vector<int> prices {7,1,5,3,6,4};
    cout << "Max profit: " << maxProfit(prices) << '\n';

    vector<int> duplicateNums {1,2,3,1};
    cout << "Contains duplicate: " << containsDuplicate(duplicateNums) << '\n';

    vector<int> selfNums {1,2,3,4};
    vector<int> resultsSelf = productExceptSelf(selfNums);
    cout << "Product except self: < ";
    for(int i : resultsSelf) cout << i << ' ';
    cout << ">\n";

    vector<int> subArrayNums {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Max sub-array sum: " << maxSubArray(subArrayNums) << '\n';

    vector<int> subArrayProds {2,3,-2,4};
    cout << "Max sub-array prod: " << maxProduct(subArrayProds) << '\n';

    vector<int> minRotatedNums {3,4,5,1,2};
    cout << "Min in rotated array: " << findMin(minRotatedNums) << '\n';

    vector<int> searchRotatedNums {4,5,6,7,0,1,2};
    cout << "Search in rotated array: " << searchRotated(searchRotatedNums, 3) << '\n';

    vector threeSumNums {-2,0,1,1,2};
    vector<vector<int>> resultsThreeSum = threeSum(threeSumNums);
    cout << "Three sum: ";
    for (const auto& s : resultsThreeSum) {
        cout << "< ";
        for (auto i : s) cout << i << ' ';
        cout << "> ";
    }

    vector<int> containerHeights {1,8,6,2,5,4,8,3,7};
    cout << "\nMax container area: " << maxArea(containerHeights) << '\n';

    cout << "Sum of a and b using bit manipulation: " << getSum(2, 3) << '\n';

    cout << "Number of 1s in input are: " << hammingWeight(0b11111111111111111111111111111101) << '\n';

    cout << "Number of 1s until N are: " << "< ";
    vector<int> bitsCount = countBits(5);
    for (const int x : bitsCount) cout << x << ' ';
    cout << ">\n";

    vector<int> missingNumbers {9,6,4,2,3,5,7,0,1};
    cout << "Missing number is: " << missingNumber(missingNumbers) << '\n';

    cout << "Reverse pattern: " << std::bitset<32> {reverseBits(0b00000010100101000001111010011100)} << '\n';

    return 0;
}
