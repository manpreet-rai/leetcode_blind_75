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
 * @see https://leetcode.com/problems/two-sum/
 * @param nums
 * @param target
 * @return vector<int>
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
 * @see https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * @param prices
 * @return int
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
 * @return bool
 */
bool containsDuplicate(vector<int>& nums) {
    /**
     * Approach 1:
        unordered_set<int> s;
        for (auto num : nums) {
            if (const auto j = s.find(num); j != s.cend()) return true;
            s.insert(num);
        }

        return false;
     */

    /**
     * Approach 2:
     */
    sort(nums.begin(), nums.end());
    for (int i = 0; i != nums.size() - 1; ++i) {
        if (nums[i] == nums[i+1]) return true;
    }
    return false;
}


vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> prefix (nums.size()), postfix (nums.size()), results (nums.size());

    for (int i = 0; i != nums.size(); ++i) {
        if (i == 0) {
            prefix.push_back(nums[i] * 1);
        } else prefix.push_back(nums[i] * prefix[i-1]);

        cout << prefix[i] << " : ";
    }

    for (int i = nums.size() - 1; i != -1; --i) {
        if (i == nums.size() - 1 ) {
            postfix.insert(postfix.begin(), nums[i] * 1);
        }
        postfix.insert(postfix.begin(), nums[i] * postfix[i+1]);
    }

    for (int i = 0; i != nums.size(); ++i) {
        if (i == 0) {
            results.push_back(postfix[i+1] * 1);
        }
        else if (i == nums.size() - 1 ) {
            results.push_back(prefix[i-1] * 1);
        }
        else {
            results.push_back(prefix[i-1] * postfix[i+1]);
        }
    }

    return results;
}


int main() {
    vector<int> nums {2,7,011,15};
    int target = 9;

    auto results = twoSum(nums, target);
    cout << results[0] << ':' << results[1] << '\n';

    vector<int> prices {7,1,5,3,6,4};
    cout << "Max profit: " << maxProfit(prices) << '\n';

    vector<int> duplicateNums {1,2,3,1};
    cout << "Contains duplicate: 0- false, 1- true: " << containsDuplicate(duplicateNums) << '\n';

    vector selfNums {1,2,3,4};
    vector<int> resultsSelf = productExceptSelf(selfNums);
    cout << resultsSelf[0] << resultsSelf[1];

    return 0;
}
