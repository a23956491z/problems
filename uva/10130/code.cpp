#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
/*
int T, N, G, MW;
int price[1005], weight[1005];
int dp[35];
*/
class Solution{

    const int WEIGHT_RANGE = 30;
    const int SAFETY_BOUND = 10;
    const int MAX_ITEMS = 1000;

    std::vector<int> dp;
    std::vector<int> price, weight;

    int maxWeight;
    int n;
public:
    Solution():
        dp(WEIGHT_RANGE+SAFETY_BOUND, 0),
        price(MAX_ITEMS+SAFETY_BOUND, 0),
        weight(MAX_ITEMS+SAFETY_BOUND, 0)
        {
        int members = 0;
        maxWeight = 30;

        std::cin >> n;
        for(int i = 0; i != n; i++){
            std::cin >> price[i] >> weight[i];
        }
        std::cin >> members;

        knapsack();
        int out = 0;
        while(members--){
            std::cin >> maxWeight;
            out += knapsack();
        }
        std::cout << out << std::endl;
    }

    int knapsack(){
        if (dp[maxWeight]) return dp[maxWeight];
        std::vector<int> dp(WEIGHT_RANGE+SAFETY_BOUND, 0);

        for (int i = 0; i < n; ++i) {
            for (int j = maxWeight; j-weight[i] >= 0; --j) {

                dp[j] = std::max(dp[j], dp[j - weight[i]] + price[i]);
            }
        }
        return dp[maxWeight];
    }
};
int main()
{
    int times = 0;
    std::cin >> times;
    while(times--){
        Solution s;
    }
}
