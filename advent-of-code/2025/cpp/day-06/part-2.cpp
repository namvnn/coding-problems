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

  string line;
  vector<string> tables;

  while (getline(file, line)) {
    tables.push_back(line);
  }

  ll result = 0;
  int nrows = tables.size();
  int ncols = tables[0].size();
  char op = ' ';
  ll cols_result = 0;

  for (int col = 0; col < ncols; col++) {
    ll num = 0;
    vector<char> cells;

    for (int row = 0; row < nrows; row++) {
      int c = tables[row][col];

      if (c == ' ') {
        continue;
      }

      if (c == '*') {
        cols_result = 1;
        op = c;
        continue;
      }
      if (c == '+') {
        cols_result = 0;
        op = c;
        continue;
      }

      cells.push_back(c);
    }

    int ncells = cells.size();

    // Empty column
    if (ncells == 0) {
      op = ' ';
      result += cols_result;
      cols_result = 0;
      continue;
    }

    // Non-empty columns
    for (int i = ncells - 1; i >= 0; i--) {
      num += (cells[ncells - 1 - i] - '0') * pow(10, i);
    }

    switch (op) {
    case '*': {
      cols_result *= num;
      break;
    }
    case '+': {
      cols_result += num;
      break;
    }
    }
  }

  result += cols_result;

  cout << result << newl;

  file.close();
}
