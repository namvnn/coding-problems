#include <fstream>
#include <iostream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

bool is_accessible(vector<string> diagram, //
                   int nrows, int ncols, int row, int col) {
  if (diagram[row][col] == '.') {
    return false;
  }

  int rolls = 0;

  for (int y = row - 1; y <= row + 1; y++) {
    for (int x = col - 1; x <= col + 1; x++) {
      if (x < 0 || x > ncols) {
        continue;
      }
      if (y < 0 || y > nrows) {
        continue;
      }
      if (x == col && y == row) {
        continue;
      }

      if (diagram[y][x] == '@') {
        rolls += 1;
      }

      if (rolls == 4) {
        return false;
      }
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

  string line;
  vector<string> diagram;

  while (getline(file, line)) {
    diagram.push_back(line);
  }

  int nrows = diagram.size();
  int ncols = diagram[0].length();
  int result = 0;

  for (int row = 0; row < nrows; row++) {
    for (int col = 0; col < ncols; col++) {
      if (is_accessible(diagram, nrows, ncols, row, col)) {
        result += 1;
      }
    }
  }

  cout << result << newl;

  file.close();
}
