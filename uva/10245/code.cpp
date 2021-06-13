#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <cfloat>
#include <algorithm>
#include <iomanip>
#include <fstream>



using namespace std;

class Point{
public:
    Point(double init_x, double init_y){
        x = init_x;
        y = init_y;
    }

    static double distance(Point &a, Point &b){

        double res = sqrt(square(a.x-b.x) + square(a.y-b.y));
        return sqrt(square(a.x-b.x) + square(a.y-b.y));
    }
    static double horizontal_distance(Point &a, Point &b){

        return abs(a.x - b.x);
    }
    static double cmp(Point &a, Point &b){
        return a.x < b.x;
    }

    static double find_middle_line(vector<Point> &vec, int left , int right){

        if(left == right) return vec[left].x;
        int middle = (left + right) / 2;

        if((left-right+1)%2){
            return vec[middle].x;
        }else{
            return (vec[middle].x + vec[middle+1].x )/2;
        }
    }

    void print(){
        cout << x << ", " << y << endl;
    }

    double get_x(){
        return x;
    }

private:
    double x, y;
    static double square(double x){
        return x*x;
    }

};

//#define DEBUG
double find_closest_pair(vector<Point> &vec, int left , int right){

    #ifdef DEBUG
    printf("(LEFT, RIGHT) = (%d, %d)\n", left, right);
    #endif
    int middle = (left + right) / 2;
    double middle_line = Point::find_middle_line(vec, left, right);
    double min = DBL_MAX;


    if((middle - left) >= 2){
        double left_part = find_closest_pair(vec, left, middle); //left side
        if(left_part < min) min = left_part;
    }
    if((right - middle) >= 2){
        double right_part = find_closest_pair(vec, middle+1, right); //right side
        if(right_part < min) min = right_part;
    }

    for(int i = middle; i >= left; i--){
        for(int j = middle+1; j <= right ; j++){
            if(i == j) continue;

            #ifdef DEBUG
                printf("\t(i, j) = (%d, %d)\n", i, j);
            #endif

            double dis = Point::distance(vec[i], vec[j]);
            if(dis < min) min = dis;
        }
    }
    #ifdef DEBUG
    printf("(LEFT, RIGHT) = (%d, %d) min = %lf\n", left, right, min);
    #endif
    return min;
}

//#define FILE
int main(){

    #ifdef FILE
    ofstream output_file;
    output_file.open ("output.txt");
    #endif

    int n = 0;
    while(cin >> n && n != 0){

        vector<Point> coord;

        for(int i = 0 ;i != n; i++){
            double x,y;
            cin >> x >> y;

            coord.push_back(Point(x, y));
        }
        sort(coord.begin(), coord.end(), Point::cmp);
        //print();

        auto print_all = [&coord](){
            for(auto p : coord) p.print();
        };

        //print_all();

        double _min = find_closest_pair(coord, 0, n-1);


        #ifdef FILE
            if(_min >= 10000) output_file << "INFINITY" << endl;
            else output_file << fixed<< setprecision(4) << _min << endl;
        #else
            if(_min >= 10000) cout << "INFINITY" << endl;
            else cout << fixed<< setprecision(4) << _min << endl;
        #endif



    }
    #ifdef FILE
    output_file.close();
    #endif

}
