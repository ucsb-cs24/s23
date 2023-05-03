#ifndef GENEPOOL_H
#define GENEPOOL_H

#include "Person.h"

#include <istream>
#include <set>
#include <string>
#include <map>

// This is the database class you need to implement.
// It stores a collection of people and supports lookup by name.
// It reads people from a TSV-like file in the constructor.

class GenePool {
  // Member Variables

  // Helper Functions

public:
  // Build a database of people from a TSV file.
  GenePool(std::istream& stream);

  // Clean it up.
  ~GenePool();

  // List all the people in the database.
  std::set<Person*> everyone() const;

  // Find a person in the database by name.
  // Return nullptr if there is no such person.
  Person* find(const std::string& name) const;
};

#endif
