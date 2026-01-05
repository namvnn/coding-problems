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

// Reference: https://cp-algorithms.com/data_structures/disjoint_set_union.html
struct disjoint_set_union {
  vector<int> parent;

  void init(int size) {
    parent.resize(size);

    for (int i = 0; i < size; i++) {
      parent[i] = i;
    }
  }

  int find(int i) {
    if (parent[i] == i) {
      return i;
    }

    return parent[i] = find(parent[i]);
  }

  bool unite(int i, int j) {
    int i_rep = find(i);
    int j_rep = find(j);

    if (i_rep != j_rep) {
      parent[i_rep] = j_rep;
      return true;
    }

    return false;
  }
};

ll calculate_distance(point a, point b) {
  return pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2);
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  disjoint_set_union dsu;
  string line;
  vector<point> points;
  vector<edge> edges;
  int LIMIT = 1000;
  int n = 0;
  ll answer;

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

    n += 1;
  }

  dsu.init(n);

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

  for (int i = 0, total = n; i < edges.size(); i++) {
    edge e = edges[i];

    if (dsu.unite(e.from, e.to)) {
      total -= 1;
    };

    if (total == 1) {
      answer = points[e.from].x * points[e.to].x;
      break;
    }
  }
  cout << answer << newl;

  file.close();
}
