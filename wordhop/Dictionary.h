#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <istream>
#include <string>
#include <vector>

class Dictionary {
  // Member Variables

  // Helper Functions

public:
  // The create function used by the autograder:
  static Dictionary* create(std::istream& stream);

public:
  // The function that does all the work:
  std::vector<std::string> hop(const std::string& from, const std::string& to);
};

#endif
