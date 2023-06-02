#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

#include "Report.h"

class Database {
  // Member Variables

  // Helper Functions

public:
  static Database* create();

public:
  Database();
  ~Database();

  void insert(const Report* report);
  std::vector<const Report*> search(float age, float height, float weight) const;
  void remove(unsigned int id);
};

#endif
