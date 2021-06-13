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


using std::cin;
using std::vector;
using std::string;
using std::set;

#include <fstream>

vector<string> LCS(string X, string Y, int m, int n)
{
    // if the end of either sequence is reached
    if (m == 0 || n == 0)
    {
        // create a vector with 1 empty string and return
        vector<string> v(1);
        return v;
    }

    // if the last character of `X` and `Y` matches
    if (X[m - 1] == Y[n - 1])
    {
        // ignore the last characters of `X` and `Y` and find all LCS of substring
        // `X[0…m-2]`, `Y[0…n-2]` and store it in a vector
        vector<string> lcs = LCS(X, Y, m - 1, n - 1);

        // append current character `X[m-1]` or `Y[n-1]` to all LCS of
        // substring `X[0…m-2]` and `Y[0…n-2]`
        for (string &str: lcs) {        // don't remove `&`
            str.push_back(X[m - 1]);
        }

        return lcs;
    }

    // we reach here when the last character of `X` and `Y` don't match

    // if a top cell of the current cell has more value than the left cell,
    // then ignore the current character of string `X` and find all LCS of
    // substring `X[0…m-2]`, `Y[0…n-1]`

    if (length[m - 1][n] > length[m][n - 1]) {
        return LCS(X, Y, m - 1, n);
    }

    // if a left cell of the current cell has more value than the top cell,
    // then ignore the current character of string `Y` and find all LCS of
    // substring `X[0…m-1]`, `Y[0…n-2]`

    if (length[m][n - 1] > length[m - 1][n]) {
        return LCS(X, Y, m, n - 1);
    }

    // if the top cell has equal value to the left cell, then consider
    // both characters

    vector<string> top = LCS(X, Y, m - 1, n);
    vector<string> left = LCS(X, Y, m, n - 1);

    // merge two vectors and return
    top.insert(top.end(), left.begin(), left.end());
    // copy(left.begin(), left.end(), back_inserter(top));

    return top;
}

vector<string> print_lcs_recursive(int i, int j){

    if(i == 0 || j == 0){

        vector<string> v(1);
        return v;
    }

    if(prev[i][j] == From::LEFT_UP){

        vector<string> lcs = print_lcs_recursive(i-1, j-1);
        for (string &str: lcs) {
            str.push_back(s1[i - 1]);
        }

        return lcs;
    }else if(prev[i][j] == From::UP){

        return print_lcs_recursive(i-1, j);
    }else if(prev[i][j] == From::LEFT){

        return print_lcs_recursive(i, j-1);
    }else{

        vector<string> top = print_lcs_recursive(i-1, j);
        vector<string> left = print_lcs_recursive(i, j-1);

        top.insert(top.end(), left.begin(), left.end());
        return top;
    }
}

int main(){
/*
    std::ifstream cin;
    cin.open ("in3");
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


        vector<string> output_origin = print_lcs_recursive(n1, n2);
        //vector<string> output_origin = LCS(s1, s2 ,n1, n2);

        set<string> outputs(make_move_iterator(output_origin.begin()),
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
