 
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

double PI = acos(-1);

class pie{
public:
    pie():cake_amount(0){
            cin >> cake_amount >> ppl;
            ppl++;

            double max = 0;
            for(int i = 0; i != cake_amount; i++){

                double t = 0;
                cin >> t;
                t=t*t*PI;

                if(max < t) max = t;
                cakes.push_back(t);
            }

            double lower_bound = 0,upper_bound = max;

            while(upper_bound - lower_bound > 0.0001){

                double half = (lower_bound + upper_bound)/2;

                if(check(half)) lower_bound = half;
                else upper_bound = half;
            }
            printf("%.4f\n",lower_bound);
}

private:
    vector<double> cakes; //store by area(volume)
    int ppl;
    int cake_amount;

    bool check(double test_vol){

        int pieces_need = 0;

            vector<double> copy = cakes;
            for(double &i : copy){
                while(i >= test_vol){
                    i-=test_vol;
                    pieces_need++;
                    if(pieces_need == ppl) return true;
                }
            }
            return false;
    }
};

int main(){

    int cases = 0;
    cin >> cases;
    while(cases--)  pie p;
}
