#include "Database.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>

// This is the main loop; use the -i flag to get an interactive prompt.
// It doesn't do much error checking, so running it on
// an invalid data file may produce strange results.
// The autograder uses a very similar main loop.


// Helper for reading Range objects
std::istream& operator >> (std::istream& stream, Range& range) {
  // Stupid parsing trick: interpret the hyphen as a minus sign!
  float max;
  stream >> range.min >> max;
  range.max = -max;
  return stream;
}

// Helper for reading Report objects
std::istream& operator >> (std::istream& stream, Report& report) {
  return stream >> report.id >> report.age >> report.height >> report.weight;
}

// Helper for sorting reports
bool compare(const Report* lhs, const Report* rhs) {
  return lhs->id < rhs->id;
}

// Run and print the results of a case search
void search(Database* db, unsigned int id, float age, float height, float weight, bool header = true) {
  if(header) {
    std::cout << "Suspect " << id << ": age = " << age << "; height = " << height << "; weight = " << weight << ":\n";
  }

  std::vector<const Report*> reports = db->search(age, height, weight);
  // Sorted for convenience; the autograder skips this for speed.
  std::sort(reports.begin(), reports.end(), compare);

  for(const Report* report: reports) {
    std::cout << " - Report " << report->id << '\n';
  }
  if(reports.size() == 0) {
    std::cout << " - (no matches)\n";
  }
}

void read_data_file(Database* db, const char* filename) {
  float age;
  float height;
  float weight;

  unsigned int id;
  Report* report = nullptr;

  std::ifstream file(filename);
  if(file.fail()) {
    std::cerr << "Could not open file: " << filename << '\n';
    return;
  }

  std::string type;
  while(std::getline(file, type, '\t')) {
    try {
      if(type == "report") {
        report = new Report;
        file >> *report;
        db->insert(report);
        report = nullptr;
      }
      else if(type == "suspect") {
        file >> id >> age >> height >> weight;
        search(db, id, age, height, weight);
      }
      else if(type == "solved") {
        file >> id;
        db->remove(id);
      }
      else {
        std::cout << "Unknown line type: \"" << type << "\"\n";
      }
    }
    catch(const std::exception& error) {
      std::cout << "ERROR: " << error.what() << '\n';
    }

    // Clean up anything that was left behind.
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    delete report;
    report = nullptr;
  }
}

void read_user_queries(Database* db) {
  float age;
  float height;
  float weight;

  while(true) {
    std::cout << "Age:    ";
    if(!(std::cin >> age)) {
      break;
    }

    std::cout << "Height: ";
    if(!(std::cin >> height)) {
      break;
    }

    std::cout << "Weight: ";
    if(!(std::cin >> weight)) {
      break;
    }

    try {
      search(db, 0, age, height, weight, false);
    }
    catch(const std::exception& error) {
      std::cout << "ERROR: " << error.what() << '\n';
    }
  }
}


int main(int argc, char** argv) {
  int  argi = 1;
  bool interactive = false;

  if(argc > 1 && std::string(argv[1]) == "-i") {
    interactive = true;
    argi += 1;
  }

  if(argi >= argc) {
    std::cerr << "USAGE: " << argv[0] << " [-i] data-file [...]\n";
    return 1;
  }

  Database* db = Database::create();

  while(argi < argc) {
    read_data_file(db, argv[argi]);
    argi += 1;
  }

  if(interactive) {
    read_user_queries(db);
  }

  delete db;
  return 0;
}
