#include <bits/stdc++.h>

using namespace std;

#define ll long long



struct Point{
    ll x,y;
};

Point bottom_most;

/*
If CP > 0: P3​ is to the "left" of the line segment P1​→P2​ (Counter-Clockwise turn).

If CP < 0: P3​ is to the "right" of the line segment (Clockwise turn).

If CP = 0: The area of the parallelogram is 0, meaning P1​,P2​, and P3​ form a perfectly straight line (Collinear).

*/
ll cross_product(Point p1, Point p2, Point p3){
    return (p2.x-p1.x)*(p3.y-p1.y) - (p2.y-p1.y)*(p3.x-p1.x);
}

ll dist_sq(Point p1,Point p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

bool compare_angle(Point p1,Point p2){

    ll cp = cross_product(bottom_most,p1,p2);
    //If colinear, then pick the point closeer to the reference point
    //Filter the intermediate colinear points later
    if(cp==0){
        return dist_sq(bottom_most,p1)<dist_sq(bottom_most,p2);
    }
    //returns true if p1 makes a counter clockwise turn relative to p2
    return cp>0; 

}

vector<Point> graham_scan(vector<Point>&points){

    ll n = points.size();
    if(n<3) return points; //convex hull is a polygon with at least 3 points

    ll min_y = points[0].y;
    ll min_idx = 0;



    //Finding bottom most point
    for(ll i =1;i<n;i++){

        if(points[i].y<min_y || points[i].y == min_y && points[i].x<points[min_idx].x){
            min_y = points[i].y;
            min_idx = i;
        }

    }

    swap(points[0],points[min_idx]);
    bottom_most = points[0];

    //Sort the points from index 1 to n-1 based on polar angle
    sort(points.begin()+1,points.end(),compare_angle);

    // Filter collinear points: If multiple points share the same angle, we only keep the furthest one.
    // This step safely strips them out so our main stack logic is clean.
    ll m = 1;
    for(ll i=1;i<n;i++){
        while(i<n-1 && cross_product(bottom_most,points[i],points[i+1])==0){
            i++;
        }
        points[m] = points[i];
        m++;
    }
    //If we stripped out so many colinear points that we have less than 3 left;
    if(m<3) return{};

    //using a vector as a stack

    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    hull.push_back(points[2]);

    for(ll i=3;i<m;i++){
        while(hull.size()>=2){
            // While the angle formed by the next-to-top, top, and current point makes a clockwise turn
        // (cross_product <= 0), pop the top point off the stack.
            Point top = hull.back();
            Point next_to_top = hull[hull.size()-2];

            if(cross_product(next_to_top, top, points[i])<=0){
                hull.pop_back();
            }
            else{
                break;
            }
        }
        hull.push_back(points[i]);
    }
    return hull;

}
int main(){

    ll num_points;
    cin>>num_points;


    vector<Point> points(num_points);

    for(ll i=0;i<num_points;i++){
        cin>>points[i].x>>points[i].y;
    }


    vector<Point> convex_hull = graham_scan(points);
    //----------------------------- Output Results -------------------------------------
    cout << "\nThe points in the Convex Hull are:\n";
    for (auto p : convex_hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}

/* =========================================
SAMPLE INPUT 
=========================================
8
0 3
1 1
2 2
4 4
0 0
1 2
3 1
3 3

=========================================
EXPECTED OUTPUT:
=========================================
The points in the Convex Hull are:
(0, 0)
(3, 1)
(4, 4)
(0, 3)
=========================================
*/

