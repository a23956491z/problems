#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

//#define FILE
class solution{
public:
    solution(vector<int>& _vec): vec(_vec){
        size = _vec.size();
/*
        #ifdef FILE
        cout << size << endl;
       print_vec(vec);
        #endif
*/
        cout << wavio_len(vec) << endl;

    }

private:

    void print_vec(vector<int> &out_vec){
        for(int i = 0; i != out_vec.size(); i++){
            if(out_vec[i] == -1) cout << '-' << " ";
            else cout << out_vec[i] << " ";
        }cout << endl;
    }

    int wavio_len(vector<int> &vec){
        vector<int> LIS(vec.size(), 0), LIS_stack(vec.size(), 0);
        vector<int> LDS(vec.size(), 0), LDS_stack(vec.size(), 0);;

        int increa = 0, decrea = 0;

        for (int i = 0; i <  vec.size(); ++i) {
            int j = 0;
            while (vec[i] > LIS_stack[j] && j < increa) ++j;
            if (j == increa) {
                LIS_stack[increa] = vec[i];
                ++increa;
            }
            else if (vec[i] < LIS_stack[j])
                LIS_stack[j] = vec[i];

            LIS[i] = j;
        }
        for (int i = vec.size()-1; i >= 0; --i) {
            int j = 0;
            while (vec[i] > LDS_stack[j] && j < decrea) ++j;
            if (j == decrea) {
                LDS_stack[decrea] = vec[i];
                decrea++;
            }
            else if (vec[i] < LDS_stack[j])
                LDS_stack[j] = vec[i];

            LDS[i] = j;
        }

        //print_vec(LIS);
        //print_vec(LDS);

        int middle_size = 0;
        for(int i = 0; i != vec.size(); i++){

            int len = min(LIS[i], LDS[i]);
            if(len > middle_size) middle_size = len;
        }
        return middle_size*2 + 1;

    }
    int size;
    vector<int> &vec;
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
