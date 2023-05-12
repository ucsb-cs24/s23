#include "Counter.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

// This is the main function for the Character Count test cases.
// It runs through a list of files, and either increments or decrements
// the count of each letter.  Every time it sees a whitespace character,
// it toggles between increment and decrement mode.  It prints per-file
// results, and the cumulative result for all files.
// You can modify this, but Gradescope will use the original.

const char* ALPHA = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
void print_header() {
  for(int i = 0; i < 26; ++i) {
    std::cout << "    " << ALPHA[i] << ALPHA[i + 26];
  }

  std::cout << "  Filename\n";
}

void print_results(const char* filename, const Counter& counter) {
  std::string str = "?";

  for(int i = 0; i < 26; ++i) {
    str[0]  = ALPHA[i];
    int cap = counter.get(str);

    str[0]  = ALPHA[i + 26];
    int low = counter.get(str);

    std::cout << std::setw(6) << (cap + low);
  }

  std::cout << "  " << filename << std::endl;
}

int main(int argc, char** argv) {
  if(argc < 2) {
    std::cerr << "USAGE: " << argv[0] << "[filename] [...]\n";
    return 1;
  }

  Counter totals;

  print_header();
  for(int argi = 1; argi < argc; ++ argi) {
    std::ifstream stream(argv[argi]);
    if(stream.fail()) {
      std::cerr << "ERROR: Could not open file: " << argv[argi] << '\n';
      continue;
    }

    char c;
    bool inc = true;
    std::string str = "?";
    Counter counter;

    while(stream.get(c)) {
      if(isspace(c)) {
        inc = !inc;
        continue;
      }
      else if(!isalpha(c)) {
        continue;
      }

      str[0] = c;
      if(inc) {
        counter.inc(str);
        totals.inc(str);
      }
      else {
        counter.dec(str);
        totals.dec(str);
      }

      if(counter.get(str) == 0) {
        counter.del(str);
      }

      if(totals.get(str) == 0) {
        totals.del(str);
      }
    }

    print_results(argv[argi], counter);
  }

  print_results("TOTAL", totals);
  return 0;
}
