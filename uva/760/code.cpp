#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>
#include <string>
std::string print_lcs(int ,int );

enum From {
    LEFT, UP, LEFT_UP
};


const int LENGTH_MAX = 300;
char s1[LENGTH_MAX],s2[LENGTH_MAX];
int length[LENGTH_MAX+1][LENGTH_MAX+1];
From prev[LENGTH_MAX+1][LENGTH_MAX+1];

char output[LENGTH_MAX];

using std::cin;
#include <fstream>
int main(){
/*
    std::ifstream cin;
    cin.open ("in2");
*/
    bool init = false;

    for(int i = 0; i != LENGTH_MAX+1; i++) {
        length[0][i] = 0;
        length[i][0] = 0;
    }

    while(cin >> s1){
        cin >> s2;

        //if(init) printf("\n");
        init = true;

        int n1 = strlen(s1), n2=strlen(s2);
        //printf("n1: %d, n2: %d\n", n1,n2);
        for(int i = 1; i <= n1; i++){
            for(int j = 1; j <= n2; j++){

                if(s1[i-1] == s2[j-1]){

                    length[i][j] = length[i-1][j-1] + 1;
                    prev[i][j] = From::LEFT_UP;
                }else{

                    if(length[i-1][j] < length[i][j-1]){

                        length[i][j] = length[i][j-1];
                        prev[i][j] = From::LEFT;
                    }else{

                        length[i][j] = length[i-1][j];
                        prev[i][j] = From::UP;
                    }

                }
            }
        }

        for(int i = 0; i <= n1; i++){
            for(int j = 0; j <= n2; j++){
                printf("%d,%d ", prev[i][j],length[i][j]);
            }
            printf("\n");
        }

        std::set<std::string> outputs;

        int max_len = length[n1][n2];
        for(int i = 1; i <= n1; i++){
            for(int j = 1; j <= n2; j++){
                if(length[i][j] == max_len && prev[i][j] == From::LEFT_UP){
                    outputs.insert(print_lcs(i,j));
                }

            }
        }

        if(outputs.size() == 0){
            printf("No common sequence.\n");
        }
        for(auto i : outputs){
            std::cout << i << std::endl;
        }
        printf("\n");
    }
}
std::string print_lcs(int n1, int n2){
    int i=n1, j=n2;

    int current_len = length[i][j];
    while(current_len > 0){
        //printf("i:%d, j:%d, prev[i][j]:%d, l[i][j]:%d\n", i, j ,prev[i][j] ,  length[i][j]);
        switch (prev[i][j]) {
            case From::LEFT_UP:{
                current_len--;
                i--, j--;
                output[current_len] = s1[i];
                break;
            }
            case From::LEFT:{
                j--;
                break;
            }
            case From::UP:{
                i--;
                break;
            }

        }
    }

    std::string ret;
    for(int i = 0; i != length[n1][n2]; i++){
        ret.push_back(output[i]);
    }
    return ret;
}
