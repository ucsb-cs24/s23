#include "Counter.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

std::string read_key(std::istream& stream) {
  std::string key;

  stream.clear(); // reset the failbit
  if(std::getline(stream >> std::ws, key)) {
    return key;
  }

  throw std::runtime_error("Could not read key.");
}

int read_value(std::istream& stream) {
  int result;
  if(stream >> result) {
    return result;
  }

  throw std::runtime_error("Could not read value.");
}

int read_value(std::istream& stream, int dfault) {
  int result;
  if(stream >> result) {
    return result;
  }
  else {
    return dfault;
  }
}

void print(Counter& counter) {
  for(auto itr = counter.begin(); itr != counter.end(); ++itr) {
    std::cout << itr.key() << ": " << itr.value() << '\n';
  }
}


int main(int argc, char** argv) {
  bool interactive = true;
  if(argc > 1 && std::string(argv[1]) == "-q") {
    interactive = false;
  }
  else {
    std::cout << "> ";
  }

  Counter counter;

  std::string line;
  std::string command;
  std::string key;
  std::string overflow;
  while(std::getline(std::cin, line)) {
    if(line.length() == 0 || line[0] == '#') {
      continue;
    }

    try {
      std::stringstream stream(line);
      if(!(stream >> command)) {
        throw std::runtime_error("Could not read command.");
      }

      else if(command == "get" || command == "g") {
        key = read_key(stream);
        std::cout << "counter[" << key << "] = " << counter.get(key) << '\n';
      }
      else if(command == "count" || command == "c") {
        std::cout << "count = " << counter.count() << '\n';
      }
      else if(command == "dec" || command == "d") {
        int delta = read_value(stream, 1);
        key = read_key(stream);
        counter.dec(key, delta);
      }
      else if(command == "del" || command == "r") {
        key = read_key(stream);
        counter.del(key);
      }
      else if(command == "exit" || command == "x") {
        break;
      }
      else if(command == "inc" || command == "i") {
        int delta = read_value(stream, 1);
        key = read_key(stream);
        counter.inc(key, delta);
      }
      else if(command == "print" || command == "p") {
        print(counter);
      }
      else if(command == "set" || command == "s") {
        int value = read_value(stream);
        key = read_key(stream);
        counter.set(key, value);
      }
      else if(command == "stats" || command == "ct") {
        std::cout << "count = " << counter.count() << '\n';
        std::cout << "total = " << counter.total() << '\n';
      }
      else if(command == "total" || command == "t") {
        std::cout << "total = " << counter.total() << '\n';
      }
      else {
        throw std::runtime_error("Unknown command: " + command);
      }

      if(stream >> overflow) {
        throw std::runtime_error("Too many operands for command: " + command);
      }

      // if(interactive && command != "print") {
      //   print(counter);
      // }
    }
    catch(const std::out_of_range&) {
      std::cout << "Unknown key: " << key << '\n';
    }
    catch(const std::runtime_error& e) {
      std::cout << "ERROR: " << e.what() << '\n';
    }

    if(interactive) {
      std::cout << "> ";
    }
  }

  return 0;
}
