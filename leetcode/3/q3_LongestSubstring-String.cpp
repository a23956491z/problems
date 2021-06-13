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

        size_t maxLen = 0;
        string str;

        for(int i = 0; i != s.length(); i++){

            size_t found = str.find(s[i]);
            if(found == string::npos){
                str.push_back(s[i]);
                maxLen = max(maxLen, str.length());

            }else{
                str.erase(0,found+1);
                str.push_back(s[i]);
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
