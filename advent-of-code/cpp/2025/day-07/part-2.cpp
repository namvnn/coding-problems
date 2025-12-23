#include <fstream>
#include <iostream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string last_line;
  string line;
  vector<ll> last_timeline;
  vector<ll> timeline;

  while (getline(file, line)) {
    if (last_line == "") {
      for (int i = 0; i < line.size(); i++) {
        last_timeline.push_back(0);
        timeline.push_back(0);
      }
      last_line = line;
      continue;
    }

    for (int i = 0; i < line.size(); i++) {
      if (last_line[i] == 'S') {
        line[i] = '|';
        timeline[i] += 1;
        break;
      }

      if (last_line[i] == '|' && line[i] == '.') {
        line[i] = '|';
        continue;
      }

      if (last_line[i] == '|' && line[i] == '^') {
        if (i - 1 >= 0) {
          line[i - 1] = '|';
          timeline[i - 1] += last_timeline[i];
        }
        if (i + 1 <= line.size() - 1) {
          line[i + 1] = '|';
          timeline[i + 1] += last_timeline[i];
        }
        timeline[i] = 0;
        continue;
      }
    }

    for (int i = 0; i < timeline.size(); i++) {
      last_timeline[i] = timeline[i];
    }
    last_line = line;
  }

  ll answer = 0;

  for (int i = 0; i < timeline.size(); i++) {
    answer += timeline[i];
  }

  cout << answer << newl;

  file.close();
}
