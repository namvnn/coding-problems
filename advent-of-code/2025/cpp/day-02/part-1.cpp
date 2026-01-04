#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

bool is_invalid(string id) {
  int len = id.length();

  if (len % 2 == 1) {
    return false;
  }

  int mid = len / 2;

  for (int i = 0; i < mid; i++) {
    if (id[i] != id[mid + i]) {
      return false;
    }
  }

  return true;
}

ll convert_str_to_ll(string num) {
  ll r = 0;
  int len = num.length();
  for (int i = 0; i < len; i++) {
    r += (num[len - i - 1] - '0') * pow(10, i);
  }
  return r;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string line;
  ll sum = 0;

  while (getline(file, line)) {
    string range;
    stringstream range_ss(line);

    while (getline(range_ss, range, ',')) {
      string first_str;
      string second_str;
      stringstream id_ss(range);

      getline(id_ss, first_str, '-');
      getline(id_ss, second_str, '-');

      ll first = convert_str_to_ll(first_str);
      ll second = convert_str_to_ll(second_str);

      for (ll id = first; id <= second; id++) {
        if (is_invalid(to_string(id))) {
          sum += id;
        }
      }
    }
  }

  cout << sum << newl;

  file.close();
}
