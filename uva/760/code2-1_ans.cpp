#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>
#include <string>
#include <algorithm>
#include <vector>
std::string print_lcs(int ,int );

enum From {
    LEFT, UP, LEFT_UP, SAME
};


const int LENGTH_MAX = 300;
char s1[LENGTH_MAX],s2[LENGTH_MAX];
int length[LENGTH_MAX+1][LENGTH_MAX+1];
From prev[LENGTH_MAX+1][LENGTH_MAX+1];

std::vector<std::string> output_origin;

char output[LENGTH_MAX];

using std::cin;
#include <fstream>


void print_lcs_recursive(std::string lcs, int i, int j, int max_len){

    if(i == 0 || j == 0){

        std::reverse(lcs.begin(), lcs.end());
        if(lcs.length() == max_len){

            output_origin.push_back(lcs);
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
        print_lcs_recursive(lcs, i-1, j, max_len);
        print_lcs_recursive(lcs, i, j-1, max_len);
    }
}

int main(){

    std::ifstream cin;
    cin.open ("in2");


    for(int i = 0; i != LENGTH_MAX+1; i++) {
        length[0][i] = 0;
        length[i][0] = 0;
    }


    while(cin >> s1){
        cin >> s2;


        int n1 = strlen(s1), n2=strlen(s2);
        for(int i = 1; i <= n1; i++){
            for(int j = 1; j <= n2; j++){

                if(s1[i-1] == s2[j-1]){

                    length[i][j] = length[i-1][j-1] + 1;
                    prev[i][j] = From::LEFT_UP;
                }else{

                    if(length[i-1][j] < length[i][j-1]){

                        length[i][j] = length[i][j-1];
                        prev[i][j] = From::LEFT;
                    }else if(length[i][j-1] < length[i-1][j]){

                        length[i][j] = length[i-1][j];
                        prev[i][j] = From::UP;
                    }else{

                        length[i][j] = length[i-1][j];
                        prev[i][j] = From::SAME;
                    }
                }
            }
        }

        output_origin.clear();

        int max_len = length[n1][n2];


        print_lcs_recursive("", n1, n2, max_len);

        std::set<std::string> outputs(make_move_iterator(output_origin.begin()),
                        make_move_iterator(output_origin.end()));


        for(auto i : outputs){
            if(i.length() == 0){
                printf("No common sequence.\n");
                break;
            }
            std::cout << i << std::endl;
        }
        printf("\n");
    }
}
