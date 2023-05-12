#include "Counter.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

// This is the main function for the Character Count test cases.
// It runs through a list of files, reads whitespace-separated words,
// normalizes them by upcasing and stripping punctuation, and counts them.
// It prints per-file results, and the cumulative result for all files.
// You can modify this, but Gradescope will use the original.

std::string sanitize(const std::string& word) {
  std::string result;
  for(char c: word) {
    if(isalpha(c)) {
      result += toupper(c);
    }
  }

  return result;
}

void print_header() {
  std::cout << "  Tokens   Words  Unique  Filename\n";
}

void print_results(const char* filename, const Counter& counter) {
  int tokens = counter.get("[tokens]");
  int words  = counter.total() - tokens;
  int unique = counter.count() - 1;

  std::cout << std::setw(8) << tokens;
  std::cout << std::setw(8) << words;
  std::cout << std::setw(8) << unique;
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

    Counter counter;
    std::string token;

    while(stream >> token) {
      counter.inc("[tokens]");

      std::string word = sanitize(token);
      if(word.length() == 0) {
        continue;
      }

      int count = counter.get(word);
      counter.set(word, count + 1);

      // These lines are uncommented in the autograder to stress-test iteration.
      // Every 4095 words, this prints all words occurring one hundred times or more.
      // If you uncomment this, run with 2> /dev/null to de-clutter the output.
      // int ntokens = counter.get("[tokens]");
      // if((ntokens & 0x0fff) == 0) {
      //   std::cerr << "tokens: " << ntokens << "; count: " << counter.count() << "; total: " << counter.total() << '\n';
      //   for(auto itr = counter.begin(); itr != counter.end(); ++itr) {
      //     if(itr.value() >= 100) {
      //       std::cerr << itr.key() << ':' << itr.value() << ' ';
      //     }
      //   }
      //   std::cerr << '\n';
      // }
    }

    print_results(argv[argi], counter);
    for(auto itr = counter.begin(); itr != counter.end(); ++itr) {
      totals.inc(itr.key(), itr.value());
    }
  }

  print_results("TOTAL", totals);
  return 0;
}
