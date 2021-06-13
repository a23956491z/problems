#include <stack>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
private:
char right[3] = {')',']','}'};
public:
    bool isValid(string s) {
        stack<char> left_bra;

        int str_len = s.length();
        for(int i = 0; i != str_len; i++){

            if(s[i] == '(') left_bra.push(0);
            else if(s[i] == '[') left_bra.push(1);
            else if(s[i] == '{') left_bra.push(2);
            else{
                if(left_bra.empty() || right[static_cast<int>(left_bra.top())] != s[i]) return false;
                left_bra.pop();
            }

        }

        if(left_bra.size()) return false;
        return true;
    }
};
int main(){

    Solution s;

    string input;
    while(cin >> input){
        cout << (s.isValid(input) ? "true" : "false" ) << endl;
    }
}
