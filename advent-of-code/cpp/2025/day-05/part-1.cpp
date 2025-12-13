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

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  int result = 0;
  string line;
  vector<pair<ll, ll> > ranges;

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

  while (getline(file, line)) {
    ll id = convert_str_to_ll(line);

    for (int i = 0; i < ranges.size(); i++) {
      pair<ll, ll> range = ranges[i];
      
      if (id >= range.first && id <= range.second) {
        result += 1;
        break;
      }
    }
  }

  cout << result << newl;

  file.close();
}
