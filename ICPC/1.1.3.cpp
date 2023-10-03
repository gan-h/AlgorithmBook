#include <bits/stdc++.h>
#include <numeric>

using namespace std;

/*

  Given a list of 2 * N points, pair the points into N disjoint/seperate groups.
  What's the smallest distance sum we can get, if for every group, we take note of the distance between the 
  two points, and then calculate the total distance across each group combined ("the distance sum")?
  
  In this file is a backtracking with pruning solution.
  The main idea is that if you pick all pairs of two points from the 16, 
  and then calculate the distance sum for the 14 remaining points. 
  Your best distance sum is the minimum quantitiy: (a distance sum from the 14 points + the distance between the remaining two points)

  Note that this has overlapping subproblems and can be optimized further with dynamic programming
*/

class Main {
  
  double bestDistance;
  double currentDistance = 0;
  double helper(vector<pair<double, double>>& points, int startIndex) {
    //Pick two points
    if(startIndex == points.size()) return 0;
    for(int i = startIndex; i < points.size()-1; i++) {
      for(int k = startIndex+1; k < points.size(); k++) {
        double xd = points[i].first - points[k].first;
        double yd = points[i].second - points[k].second;
        double pointDistance = std::sqrt(xd * xd + yd * yd);
        currentDistance += pointDistance;
        std::swap(points[i], points[0]);
        std::swap(points[k], points[1]);

        if(currentDistance < bestDistance) {
          bestDistance = std::min(currentDistance + helper(points, startIndex + 2), bestDistance);
        }

        std::swap(points[i], points[0]);
        std::swap(points[k], points[1]);
        currentDistance -= pointDistance;
      }
    }

    return bestDistance;
  }
  public:
  double bestDistanceSolver(vector<pair<double, double>> points) {
    bestDistance = std::numeric_limits<double>::max();
    currentDistance = 0;
    
    return helper(points, 0);
  }

  Main() {

  }

};




int main() {
  Main main;
  cout << main.bestDistanceSolver({{2.3, 10.7}, {1.8, 15.2}, {7.1, 12.5}, {4.2, 18.8}, {0.5, 9.9}, {3.6, 14.0}, {9.2, 7.7}, {6.4, 11.1}, {8.7, 13.3}, {2.1, 10.8}, {5.9, 15.0}, {1.4, 17.2}, {6.8, 10.3}, {3.5, 19.8}, {7.6, 14.9}, {0.2, 15.5}
}) << endl;

  return 0;
}