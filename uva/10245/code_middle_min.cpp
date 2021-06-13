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

    void print(){
        cout << x << ", " << y << endl;
    }

private:
    static double square(double x){
        return x*x;
    }
    double x, y;
};

double find_middle_line(vector<Point> &vec, int left , int right){

}
double find_closest_pair(vector<Point> &vec, int left , int right){

    //printf("(LEFT, RIGHT) = (%d, %d)\n", left, right);
    int middle = (left + right) / 2;
    double min = DBL_MAX;


    if((middle - left) >= 2){
        double left_part = find_closest_pair(vec, left, middle); //left side
        if(left_part < min) min = left_part;
    }
    if((right - middle) >= 2){
        double right_part = find_closest_pair(vec, middle+1, right); //right side
        if(right_part < min) min = right_part;
    }

    double break_weight = 1;
    for(int i = middle; i >= left; i--){
        for(int j = middle+1; j <= right; j++){
            //if(i == j) continue;
            if((Point::horizontal_distance(vec[i], vec[j])) > min) break;
            //printf("(i, j) = (%d, %d)\n", i, j);
            double dis = Point::distance(vec[i], vec[j]);
            if(dis < min) min = dis;
        }
    }
    //printf("(LEFT, RIGHT) = (%d, %d) min = %lf\n", left, right, min);
    return min;
}
int main(){
    /*
    ofstream output_file;
    output_file.open ("output.txt");
*/

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



        if(_min >= 10000) cout << "INFINITY" << endl;
        else cout << fixed<< setprecision(4) << _min << endl;

    }
    //output_file.close();
}
