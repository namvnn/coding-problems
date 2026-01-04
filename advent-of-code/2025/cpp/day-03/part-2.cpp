#include <fstream>
#include <iostream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

ll find_largest_joltage(string bank, int n_batteries) {
  int len = bank.length();
  ll largest_joltage = 0;

  for (int i = n_batteries - 1, next_j = 0; i >= 0; i--) {
    int largest_digit = -1;

    for (int j = next_j; j < len - i; j++) {
      int digit = bank[j] - '0';

      if (largest_digit < digit) {
        next_j = j + 1;
        largest_digit = digit;
      }
    }

    largest_joltage += pow(10, i) * largest_digit;
  }

  return largest_joltage;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string bank;
  int BATTERIES = 12;
  ll sum = 0;

  while (getline(file, bank)) {
    sum += find_largest_joltage(bank, BATTERIES);
  }

  cout << sum << newl;

  file.close();
}
