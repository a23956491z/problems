#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <unordered_map>
using namespace std;

class Solution {

public:
    int lengthOfLongestSubstring(string s) {

        vector<int> last_position(256, -1);

        int window_start = 0, window_end = 0;
        int maxLen = 0;
        int str_len = s.length();

        for(window_end = 0; window_end != str_len; window_end++){

            char c = s[window_end];

            if(last_position[c] < window_start){
                last_position[c] = window_end;
                maxLen = max(maxLen, window_end - window_start + 1);

            }
            else{

                window_start = last_position[c] + 1;
                last_position[c] = window_end;
            }
        }
        return maxLen;
    }
};

int main() {

    string s;
    Solution solve;
    while(cin >> s){
        cout << solve.lengthOfLongestSubstring(s) << endl;
    }
    return 0;
}
