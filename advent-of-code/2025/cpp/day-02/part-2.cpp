#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

bool is_invalid(string id) {
  int len = id.length();

  for (int pattern_len = 1; pattern_len < len; pattern_len++) {
    if (len % pattern_len != 0) {
      continue;
    }

    int pattern_count = len / pattern_len;
    for (int i = 1; i < pattern_count; i++) {
      string first = id.substr((i - 1) * pattern_len, pattern_len);
      string second = id.substr(i * pattern_len, pattern_len);
      if (first != second) {
        break;
      }
      if (i == pattern_count - 1) {
        return true;
      }
    }
  }

  return false;
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
