#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

// Define the maximum possible length of string `X` and `Y`
#define MAX 300

// `lookup[i][j]` stores the length of LCS of substring `X[0…i-1]` and `Y[0…j-1]`
int lookup[MAX][MAX];

int counter = 0;
// Function to return all LCS of substrings `X[0…m-1]`, `Y[0…n-1]`
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

    if (lookup[m - 1][n] > lookup[m][n - 1]) {
        return LCS(X, Y, m - 1, n);
    }

    // if a left cell of the current cell has more value than the top cell,
    // then ignore the current character of string `Y` and find all LCS of
    // substring `X[0…m-1]`, `Y[0…n-2]`

    if (lookup[m][n - 1] > lookup[m - 1][n]) {
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

// Function to fill the lookup table by finding the length of LCS
// of substring `X[0…m-1]` and `Y[0…n-1]`
void LCSLength(string X, string Y, int m, int n)
{
    // first row and first column of the lookup table
    // are already 0 as `lookup[][]` is globally declared

    // fill the lookup table in a bottom-up manner
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // if current character of `X` and `Y` matches
            if (X[i - 1] == Y[j - 1]) {
                lookup[i][j] = lookup[i - 1][j - 1] + 1;
            }
            // otherwise, if the current character of `X` and `Y` don't match
            else {
                lookup[i][j] = max(lookup[i - 1][j], lookup[i][j - 1]);
            }
        }
    }
}

// Function to find all LCS of string `X[0…m-1]` and `Y[0…n-1]`
set<string> LCS(string X, string Y)
{
    int m = X.length(), n = Y.length();

    // fill lookup table
    LCSLength(X, Y, m, n);

    // find all the longest common sequences
    vector<string> v = LCS(X, Y, m, n);

    // since a vector can contain duplicates, "convert" it to a set
    set<string> lcs(make_move_iterator(v.begin()),
                    make_move_iterator(v.end()));

    // to copy a vector to a set use set<string> lcs(v.begin(), v.end())

    // return set containing all LCS
    return lcs;
}

#include <fstream>
int main()
{
    string X,Y;
/*
    std::ifstream cin;
    cin.open ("in3");
*/
    while(cin >> X >> Y){
        set<string> lcs = LCS(X, Y);

        // print set elements
        for (string str: lcs) {
            if(!str.length()){
                cout << "No common sequence.";
                break;
            }
            cout << str << endl;
        }
        cout << endl;
    }



    return 0;
}
