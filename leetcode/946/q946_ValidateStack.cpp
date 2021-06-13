#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stack_push, stack_pop;

        for(auto iter = popped.rbegin(); iter != popped.rend(); iter++){
            stack_pop.push(*iter);
        }


        for(int i = 0; i != pushed.size(); i++){

            if(pushed[i] == stack_pop.top()){

                stack_pop.pop();

                while( !stack_push.empty() ){
                    if(stack_push.top() == stack_pop.top()){
                        stack_push.pop();
                        stack_pop.pop();
                    }else{
                        break;

                    }
                }
            }else{
                stack_push.push(pushed[i]);
            }
        }
        if(stack_pop.size()) return false;

        return true;
    }
};

int main(){

    digits = new int(n);

    Solution s;


    vector<int> push = {0,2,1,3}, pop = {0,3,2,1};
    cout << ((s.validateStackSequences(push, pop)) ? "true" : "false") << endl;

}
