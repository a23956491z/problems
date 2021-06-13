#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>
#include <string>
#include <algorithm>
std::string print_lcs(int ,int );

enum From {
    LEFT, UP, LEFT_UP, SAME
};


const int LENGTH_MAX = 300;
char s1[LENGTH_MAX],s2[LENGTH_MAX];
int length[LENGTH_MAX+1][LENGTH_MAX+1];
From prev[LENGTH_MAX+1][LENGTH_MAX+1];
std::set<std::string> outputs;

bool touched[LENGTH_MAX+1][LENGTH_MAX+1];
char output[LENGTH_MAX];

using std::cin;
#include <fstream>


void print_lcs_recursive(std::string lcs, int i, int j, int max_len){
    //printf("(%d, %d)\n", i,j);
    touched[i][j] = true;
    if(i == 0 || j == 0){
        if(lcs.length() == max_len){
            std::reverse(lcs.begin(), lcs.end());
            outputs.insert(lcs);
        }
        return;
    }

    if(prev[i][j] == From::LEFT_UP){
        lcs.push_back(s1[i-1]);
        print_lcs_recursive(lcs, i-1, j-1, max_len);

    }else if(prev[i][j] == From::UP){
        print_lcs_recursive(lcs, i-1, j, max_len);
    }else if(prev[i][j] == From::LEFT){
        print_lcs_recursive(lcs, i, j-1, max_len);
    }else if(prev[i][j] == From::SAME){
        if(!touched[i-1][j]) print_lcs_recursive(lcs, i-1, j, max_len);
        if(!touched[i][j-1]) print_lcs_recursive(lcs, i, j-1, max_len);
    }
}

int main(){

    std::ifstream cin;
    cin.open ("in2");

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
                    }else if(length[i-1][j] < length[i][j-1]){

                        length[i][j] = length[i-1][j];
                        prev[i][j] = From::UP;
                    }else{

                        length[i][j] = length[i-1][j];
                        prev[i][j] = From::SAME;
                    }

                }
            }
        }
/*
        for(int i = 0; i <= n1; i++){
            for(int j = 0; j <= n2; j++){
                printf("%d,%d ", prev[i][j],length[i][j]);
            }
            printf("\n");
        }
*/
        outputs.clear();

        int max_len = length[n1][n2];
        for(int i = 1; i <= n1; i++){
            for(int j = 1; j <= n2; j++){
                if(length[i][j] == max_len && prev[i][j] == From::LEFT_UP){

                    for(int i = 0; i != LENGTH_MAX+1; i++){
                        for(int j = 0; j != LENGTH_MAX+1; j++){
                            touched[i][j] = false;
                        }
                    }
                    print_lcs_recursive("", i, j, max_len);
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
