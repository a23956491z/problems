#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <fstream>

using namespace std;

class Coord{

public:
    double x, r;
    Coord(double _x, double _r){

        x = _x;
        r = _r;
    }
};

double sq(double a){
  return a*a;
}

int main(){
/*
    std::ifstream cin;
    cin.open ("in3");
*/
    int cases;
    double grass_length,grass_width;
    while(cin >> cases >> grass_length >> grass_width){

        vector<Coord> vec;
        while(cases--){
            double x1, x2;
            cin >> x1 >> x2;
            vec.emplace_back(x1, x2);
        }

        sort(vec.begin(), vec.end(),
            [](Coord &a, Coord &b){
                if(a.x < b.x) return 1;
                if(a.x == b.x){
                    if(a.r < b.r ) return 1;
                    return 0;
                }
                return 0;
            }
        );

        double p = 0;
        int counter = 0;

        bool founded = true;
        bool leave = false;
        while(founded){
            founded = false;

            for(int i = vec.size()-1; i >= 0; i--){

                Coord &coord = vec[i];
                if((sq(coord.x - p) + sq(grass_width/2)) <= sq(coord.r)){

                    counter++;
                    p = coord.x+sqrt(sq(coord.r) - sq(grass_width/2));
                    founded = true;

                    if((sq(grass_length - coord.x) + sq(grass_width/2)) <= sq(coord.r)){
                      leave = true;
                    }
                    vec.erase(vec.begin()+i);
                    break;
                }
            }
            if(leave) break;
        }

        if(leave){
            cout << counter << endl;
        }else{
            cout << -1 << endl;
        }

        // hi;
        // another test



    }
    return 0;
}
