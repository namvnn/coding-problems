#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

ll convert_str_to_ll(string num) {
  ll r = 0;
  int len = num.length();
  for (int i = 0; i < len; i++) {
    r += (num[len - i - 1] - '0') * pow(10, i);
  }
  return r;
}

// Source: https://codeshare.io/aVy838
bool merge_ranges(vector<pair<ll, ll>> &ranges) {
  for (int i = 0; i < ranges.size(); i++) {
    for (int j = 0; j < ranges.size(); j++) {
      if (i == j) {
        continue;
      }

      pair<ll, ll> range_1 = ranges[i];
      pair<ll, ll> range_2 = ranges[j];

      if (max(range_1.first, range_2.first) <=
          min(range_1.second, range_2.second)) {
        ranges.erase(find(ranges.begin(), ranges.end(), range_1));
        ranges.erase(find(ranges.begin(), ranges.end(), range_2));
        ranges.push_back(make_pair(min(range_1.first, range_2.first),
                                   max(range_1.second, range_2.second)));

        return true;
      }
    }
  }

  return false;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string line;
  vector<pair<ll, ll>> ranges;

  while (getline(file, line)) {
    if (line == "") {
      break;
    }

    stringstream range_ss(line);
    string from;
    string to;

    getline(range_ss, from, '-');
    getline(range_ss, to, '-');

    ranges.push_back(make_pair(convert_str_to_ll(from), convert_str_to_ll(to)));
  }

  while (merge_ranges(ranges)) {
  }

  ll result = 0;

  for (int i = 0; i < ranges.size(); i++) {
    pair<ll, ll> range = ranges[i];
    ll from = range.first;
    ll to = range.second;
    result += to - from + 1;
  }

  cout << result << newl;

  file.close();
}
