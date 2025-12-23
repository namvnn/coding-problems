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
  int answer = 0;

  while (getline(file, line)) {
    if (last_line == "") {
      last_line = line;
      continue;
    }

    for (int i = 0; i < line.size(); i++) {
      if (last_line[i] == 'S') {
        line[i] = '|';
        break;
      }

      if (last_line[i] == '|' && line[i] == '.') {
        line[i] = '|';
        continue;
      }

      if (last_line[i] == '|' && line[i] == '^') {
        if (i - 1 >= 0) {
          line[i - 1] = '|';
        }
        if (i + 1 <= line.size() - 1) {
          line[i + 1] = '|';
        }
        answer += 1;
        continue;
      }
    }

    last_line = line;
  }

  cout << answer << newl;

  file.close();
}
