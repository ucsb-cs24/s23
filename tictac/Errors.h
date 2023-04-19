#ifndef ERRORS_H
#define ERRORS_H

// This file defines some useful exception classes.
// These are subclasses that inherit from std::runtime_error.
// The important thing is that there's one type per type of error, so
// you can write a separate catch statement for each type of error.
// You can edit this file, but you shouldn't need to.

#include <stdexcept>

// Throw one of these when you can't parse a Move.
class ParseError: public std::runtime_error {
public:
  ParseError(const std::string& message): std::runtime_error(message) {
    // Nothing else to do.
  }
};

// Throw one of these when a Move is illegal.
class InvalidMove: public std::runtime_error {
public:
  InvalidMove(const std::string& message): std::runtime_error(message) {
    // Nothing else to do.
  }
};

#endif
