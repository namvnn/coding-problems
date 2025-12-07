#include <fstream>
#include <iostream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

int find_largest_joltage(string bank) {
  int len = bank.length();
  int largest = 0;

  for (int i = 0; i < len - 1; i++) {
    for (int j = i + 1; j < len; j++) {
      int num = (bank[i] - '0') * 10 + (bank[j] - '0');
      largest = max(largest, num);
    }
  }

  return largest;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string bank;
  int sum = 0;

  while (getline(file, bank)) {
    sum += find_largest_joltage(bank);
  }

  cout << sum << newl;

  file.close();
}
