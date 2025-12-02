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
  int dial = 50;
  int password = 0;

  while (getline(file, line)) {
    char direction = line[0];
    int distance = stoi(line.substr(1, line.length()));

    switch (direction) {
    case 'L': {
      for (int i = 0; i < distance; i++) {
        dial -= 1;
        if (dial == 0) {
          password += 1;
        }
        if (dial < 0) {
          dial += 100;
        }
      }
      break;
    }
    case 'R': {
      for (int i = 0; i < distance; i++) {
        dial += 1;
        if (dial == 100) {
          password += 1;
        }
        if (dial >= 100) {
          dial -= 100;
        }
      }
      break;
    }
    default: {
      cout << "error: unknown direction" << newl;
      return 1;
    }
    }
  }

  cout << password << '\n';

  file.close();
}
