#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll unsigned long long
#define newl '\n'

using namespace std;

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
      ll width = abs(points[i].first - points[j].first) + 1;
      ll height = abs(points[i].second - points[j].second) + 1;

      answer = max(width * height, answer);
    }
  }

  cout << answer << newl;

  file.close();
}
