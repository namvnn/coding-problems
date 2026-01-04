#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define ll unsigned long long
#define newl '\n'

struct point {
  int x;
  int y;
  int z;
};

struct edge {
  ll distance;
  int from;
  int to;
};

ll calculate_distance(point a, point b) {
  return pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2);
}

bool all(vector<int> vec, int num) {
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i] != num) {
      return false;
    }
  }

  return true;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  vector<point> points;
  vector<edge> edges;
  vector<int> circuits;
  int LIMIT = 1000;
  int n = 0;
  ll answer;

  string line;

  while (getline(file, line)) {
    stringstream coord(line);
    string x, y, z;
    point pt;

    getline(coord, x, ',');
    getline(coord, y, ',');
    getline(coord, z, ',');

    pt.x = stoi(x);
    pt.y = stoi(y);
    pt.z = stoi(z);
    points.push_back(pt);

    circuits.push_back(n++);
  }

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      edges.push_back({
          .distance = calculate_distance(points[i], points[j]),
          .from = i,
          .to = j,
      });
    }
  }

  sort(edges.begin(), edges.end(),
       [](edge &a, edge &b) { return a.distance < b.distance; });

  for (int i = 0; i < edges.size(); i++) {
    edge e = edges[i];
    int circuit_to_keep = circuits[e.from];
    int circuit_to_replace = circuits[e.to];

    for (int j = 0; j < circuits.size(); j++) {
      if (circuits[j] == circuit_to_replace) {
        circuits[j] = circuit_to_keep;
      }
    }

    if (all(circuits, circuit_to_keep)) {
      answer = points[e.from].x * points[e.to].x;
      break;
    }
  }

  cout << answer << newl;

  file.close();
}
