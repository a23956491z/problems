#include <algorithm>
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {

        size_t minWindowSize = nums.size()+1;
        size_t window_start = 0;

        int sum = 0;
        for(size_t window_end = 0; window_end != nums.size(); window_end++){
            sum += nums[window_end];

            while(sum >= s){

                minWindowSize = min(minWindowSize, window_end - window_start + 1);
                sum -= nums[window_start];
                window_start++;
            }
        }


        if(minWindowSize == nums.size()+1) return 0;
        return minWindowSize;

    }
};
