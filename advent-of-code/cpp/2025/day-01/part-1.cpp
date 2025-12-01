#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist\n";
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
      dial -= distance;
      int times = abs(dial) / 100;
      dial += times * 100;
      break;
    }
    case 'R': {
      dial += distance;
      int times = abs(dial) / 100;
      dial -= times * 100;
      break;
    }
    default: {
      cout << "error: unknown direction" << '\n';
      return 1;
    }
    }

    if (dial == 0) {
      password += 1;
    }
  }

  cout << password << '\n';

  file.close();
}
