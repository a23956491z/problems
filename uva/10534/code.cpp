#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define FILE
class solution{
public:
    solution(vector<int> _vec){
        size = _vec.size();
        vec = _vec;
/*
        #ifdef FILE
        cout << size << endl;
       print_vec(vec);
        #endif
*/
        set<int> s( vec.begin(), vec.end() );

        int max_len = 0;
        for(auto iter = s.rbegin(); iter != s.rend(); iter++){
            //cout <<"iter: "<< *iter << endl;

            vector<int> removed_dul(vec);

            do{
                int len = wavio_len(removed_dul, 0, *iter);

                if(len > max_len) max_len = len;

            }while(get_exists(removed_dul, *iter));

            //printf("num: %d len: %d\n", *iter, max_len);
            //if(max_len != 1) break;
        }
        cout << max_len << endl;

    }

private:

    void print_vec(vector<int> &out_vec){
        for(int i = 0; i != out_vec.size(); i++){
            if(out_vec[i] == -1) cout << '-' << " ";
            else cout << out_vec[i] << " ";
        }cout << endl;
    }

    int get_exists(vector<int> &vec, int target){
        int counter = 0;
        for(int &i : vec){
            if(i == target){
                if(counter == 0){
                    i = 100000;
                }
                counter++;
            }
        }
        return counter-1;
    }


    int wavio_len(vector<int> &vec, int start, int target){
        //cout << "TARGET : " << target << endl;
        vector<int> bigger(target+1, -1);
        vector<int> smaller(target+1, -1);

        int i = start;
        for(; i != size; i++){
            if(vec[i] == target) break;
            if(vec[i] > target) continue;

            if(bigger[vec[i]] == -1)  bigger[vec[i]] = 0;

            if(vec[i] == 0) continue;
            //printf("vec[i]: %d bigger: %d\n", vec[i], bigger[vec[i]]);
            int curr = vec[i]-1;
            int max = -1;
            while(curr >= 0){

                if(bigger[curr] != -1){
                    //printf("curr: %d bigger[curr]: %d\n",curr, bigger[curr]);
                    if(bigger[curr] > max) max = bigger[curr];
                }
                curr--;
            }
            bigger[vec[i]] = max+1;

            //printf("vec[i]: %d bigger: %d\n", vec[i], bigger[vec[i]]);
        }
        //print_vec(bigger);

        for(i++; i < size; i++){

            if(vec[i] >= target) continue;

            if(smaller[vec[i]] == -1)  smaller[vec[i]] = 0;

            int curr = vec[i]+1;
            int max = -1;
            while(curr < target+1){

                if(smaller[curr] != -1){
                    if(smaller[curr] > max) max = smaller[curr];
                }
                curr++;
            }
            smaller[vec[i]] = max+1;
        }
        //print_vec(smaller);

        while(1){
            auto bigger_max = max_element(begin(bigger), end(bigger));
            auto smaller_max = max_element(begin(smaller), end(smaller));

            if(*smaller_max == *bigger_max) return (*bigger_max+1)*2+1;
            if(*smaller_max > *bigger_max){
                *smaller_max = -1;
            }else{
                *bigger_max = -1;
            }

        }
        return -1;

    }
    int size;
    vector<int> vec;
};


int main(){

    #ifdef FILE
    ifstream cin;
    cin.open ("in2");
    #endif

    int n = 0;
    while(cin >> n && n != 0){

        vector<int> element_in(n, 0);
        for(int i = 0; i != n; i++){
            cin >> element_in[i];
        }

        solution s(element_in);
    }
    #ifdef FILE
    cin.close();
    #endif
}
