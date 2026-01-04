#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#define ll long long
#define newl '\n'

using namespace std;

void parse_lights(bitset<16> &lights, string &token) {
  int count = 0;

  for (char c : token) {
    switch (c) {
    case '.': {
      lights[count++] = 0;
      break;
    }
    case '#': {
      lights[count++] = 1;
      break;
    }
    }
  }
}

void parse_button(bitset<16> &button, string &token) {
  stringstream ss(token.substr(1, token.size() - 2));
  string index;

  while (getline(ss, index, ',')) {
    button[stoi(index)] = 1;
  }
}

int find_fewest_step(bitset<16> &lights, vector<bitset<16>> &buttons) {
  int answer = INT_MAX;
  int n_buttons = buttons.size();

  for (int m = 0; m < (1 << n_buttons); m++) {
    bitset<16> state;
    int step = 0;

    for (int i = 0; i < n_buttons; i++) {
      if (m & (1 << i)) {
        state ^= buttons[i];
        step += 1;
      }
    }

    if (state == lights) {
      answer = min(step, answer);
    }
  }

  return answer;
}

int main() {
  string filename = "input.txt";
  ifstream file(filename);

  if (!file.is_open()) {
    cout << "error: " << filename << " does not exist" << newl;
    return 1;
  }

  string line;
  int answer = 0;

  while (getline(file, line)) {
    stringstream ss(line);
    string token;
    bitset<16> lights;
    bitset<16> button;
    vector<bitset<16>> buttons;
    int step = 0;

    ss >> token;
    parse_lights(lights, token);

    while (ss >> token) {
      if (token[0] == '{') {
        break;
      }

      button.reset();
      parse_button(button, token);
      buttons.push_back(button);
    }

    step = find_fewest_step(lights, buttons);
    answer += step;
  }

  cout << answer << newl;

  file.close();
}
