#include <stack>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<int> small, med, big;
        unordered_set<int> unpair_small, unpair_med, unpair_big;

        int str_len = s.length();
        for(int i = 0; i != str_len; i++){
            if(s[i] == '('){
                small.push(i);
                unpair_small.insert(i);
            }else if(s[i] == '['){
                med.push(i);
                unpair_med.insert(i);
            }else if(s[i] == '{'){
                big.push(i);
                unpair_big.insert(i);
            }else{

                if(s[i] == ')'){

                    if(small.empty()) return false;
                    int left = small.top();
                    for(auto &un : unpair_med) if(un < i && un > left) return false;
                    for(auto &un : unpair_big) if(un < i && un > left) return false;

                    small.pop();
                    unpair_small.erase(left);
                }else if(s[i] == ']'){

                    if(med.empty()) return false;
                    int left = med.top();
                    for(auto &un : unpair_small) if(un < i && un > left) return false;
                    for(auto &un : unpair_big) if(un < i && un > left) return false;


                    med.pop();
                    unpair_med.erase(left);
                }

                else if(s[i] == '}'){

                    if(big.empty()) return false;
                    int left = big.top();
                    for(auto &un : unpair_small) if(un < i && un > left) return false;
                    for(auto &un : unpair_med) if(un < i && un > left) return false;

                    big.pop();
                    unpair_big.erase(left);
                }

            }
        }
        if(!small.empty() || !med.empty() || !big.empty()) return false;
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
