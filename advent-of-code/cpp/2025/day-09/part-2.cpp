#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll unsigned long long
#define newl '\n'

using namespace std;

// Even–odd rule
// Reference: https://en.wikipedia.org/wiki/Even%E2%80%93odd_rule
bool is_point_in_area(pair<int, int> &point, vector<pair<int, int>> &poly) {
  int x = point.first;
  int y = point.second;
  int n = poly.size();
  bool inside = false;

  for (int i = 0; i < n; i++) {
    int ax = poly[i - 1].first;
    int ay = poly[i - 1].second;
    int bx = poly[i].first;
    int by = poly[i].second;

    if ((x == ax) && (y == ay)) {
      // point is a corner
      return true;
    }
    if ((ay > y) != (by > y)) {
      ll slope = (x - ax) * (by - ay) - (bx - ax) * (y - ay);

      if (slope == 0) {
        // point is on boundary
        return true;
      }
      if ((slope < 0) != (by < ay)) {
        inside = !inside;
      }
    }
  }

  return inside;
}

bool is_eligible(pair<int, int> &point1, pair<int, int> &point2,
                 vector<pair<int, int>> &poly) {
  pair<int, int> intersect_point1 = {point1.first, point2.second};
  pair<int, int> intersect_point2 = {point2.first, point1.second};

  return is_point_in_area(intersect_point1, poly) &&
         is_point_in_area(intersect_point2, poly);
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string line;
  vector<pair<int, int>> points;
  int n = 0;
  ll answer = 0;

  while (getline(file, line)) {
    stringstream coord(line);
    string x, y;

    getline(coord, x, ',');
    getline(coord, y, ',');
    points.push_back(make_pair(stoi(x), stoi(y)));

    n += 1;
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      pair<int, int> point1 = points[i];
      pair<int, int> point2 = points[j];

      if (!is_eligible(point1, point2, points)) {
        continue;
      }

      ll width = abs(point1.first - point2.first) + 1;
      ll height = abs(point1.second - point2.second) + 1;

      if (width * height > answer) {
        // cout << "First " << point1.first << ',' << point1.second << newl;
        // cout << "Second " << point2.first << ',' << point2.second << newl;
        // cout << "Area " << width * height << newl;
        // cout << newl;
      }

      answer = max(width * height, answer);
    }
  }

  // || First 94693,50233
  // || Second 5570,68792
  // || Area 1654141440

  cout << answer << newl;

  file.close();
}
