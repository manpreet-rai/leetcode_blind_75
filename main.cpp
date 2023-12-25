#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;


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
        unordered_set<int> s;
        for (auto num : nums) {
            if (const auto j = s.find(num); j != s.cend()) return true;
            s.insert(num);
        }

        return false;
     */

    /**
     * Approach 2:
     * Time complexity: O(N * Log N).
     * Space complexity: O(1).
     */
    sort(nums.begin(), nums.end());
    for (int i = 0; i != nums.size() - 1; ++i) {
        if (nums[i] == nums[i+1]) return true;
    }
    return false;
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
    cout << "Product except self: ";
    for(int i : resultsSelf) cout << i << ' ';
    cout << '\n';

    vector<int> subArrayNums {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Max sub-array sum: " << maxSubArray(subArrayNums) << '\n';

    return 0;
}
