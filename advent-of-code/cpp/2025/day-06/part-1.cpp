#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll long long
#define newl '\n'

#define vector_int vector<int>

using namespace std;

ll calculate_col(vector<vector_int> table, string op, int col) {
  ll result;

  if (op == "*") {
    result = 1;

    for (int row = 0; row < table.size(); row++) {
      result *= table[row][col];
    }
  } else if (op == "+") {
    result = 0;

    for (int row = 0; row < table.size(); row++) {
      result += table[row][col];
    }
  }

  return result;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string line;
  vector<vector_int> table;
  vector<string> ops;

  while (getline(file, line)) {
    stringstream ss(line);
    string num_or_op;
    vector<int> nums;
    bool is_ops_line = false;

    while (getline(ss, num_or_op, ' ')) {
      if (num_or_op == "") {
        continue;
      }

      if (num_or_op == "*" || num_or_op == "+") {
        is_ops_line = true;
        ops.push_back(num_or_op);
      } else {
        nums.push_back(stoi(num_or_op));
      }
    }

    if (!is_ops_line) {
      table.push_back(nums);
    }
  }

  ll result = 0;

  for (int col = 0; col < table[0].size(); col++) {
    string op = ops[col];
    result += calculate_col(table, op, col);
  }

  cout << result << newl;

  file.close();
}
