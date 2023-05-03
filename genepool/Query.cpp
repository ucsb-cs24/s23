#include "Query.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

// This file provides query parsing and execution.
// You can edit it if you want, but you shouldn't need to.
// Gradescope will use the original version.


// Helper function that throws an error if a read fails:
void read_term(std::istream& stream, std::string& term) {
  if(!(stream >> term)) {
    throw std::invalid_argument("Too few terms in query.");
  }
}

// Construct a query by parsing text:
Query::Query(const std::string& text) {
  std::istringstream stream(text);

  mPMod = PMod::ANY;
  mSMod = SMod::ANY;

  std::string term;
  read_term(stream, mName);

  // This is a special case:
  if(mName == "everyone") {
    if(stream >> term) {
      throw std::invalid_argument("Too many terms in query.");
    }

    mName = "Everyone";
    mRelationship = "everyone";
    return;
  }

  // Translate underscores to spaces and remove posessives:
  std::replace(mName.begin(), mName.end(), '_', ' ');

  size_t pos = mName.length() - 2;
  if(mName.find("'s", pos) == pos) {
    mName = mName.substr(0, pos);
  }

  read_term(stream, term);
  if(term == "maternal") {
    mPMod = PMod::MATERNAL;
    read_term(stream, term);
  }
  else if(term == "paternal") {
    mPMod = PMod::PATERNAL;
    read_term(stream, term);
  }

  if(term == "full") {
    mSMod = SMod::FULL;
    read_term(stream, term);
  }
  else if(term == "half") {
    mSMod = SMod::HALF;
    read_term(stream, term);
  }

  mRelationship = term;
  if(stream >> term) {
    throw std::invalid_argument("Too many terms in query.");
  }

  validate();
}

// Construct a query directly:
Query::Query(const std::string& name, const std::string& relationship, PMod pmod, SMod smod) {
  this->mName         = name;
  this->mRelationship = relationship;
  this->mPMod         = pmod;
  this->mSMod         = smod;

  validate();
}

// Run a query against a gene pool:
std::set<Person*> Query::run(const GenePool& pool) const {
  if(mRelationship == "everyone") {
    return pool.everyone();
  }

  Person* person = pool.find(mName);
  if(person == nullptr) {
    throw std::invalid_argument("No such person: " + mName);
  }

  if(mRelationship == "ancestors") {
    return person->ancestors(mPMod);
  }
  else if(mRelationship == "aunts") {
    return person->aunts(mPMod, mSMod);
  }
  else if(mRelationship == "brothers") {
    return person->brothers(mPMod, mSMod);
  }
  else if(mRelationship == "children") {
    return person->children();
  }
  else if(mRelationship == "cousins") {
    return person->cousins(mPMod, mSMod);
  }
  else if(mRelationship == "daughters") {
    return person->daughters();
  }
  else if(mRelationship == "descendants") {
    return person->descendants();
  }
  else if(mRelationship == "father") {
    Person* father = person->father();
    std::set<Person*> result;
    if(father != nullptr) {
      result.insert(father);
    }

    return result;
  }
  else if(mRelationship == "grandchildren") {
    return person->grandchildren();
  }
  else if(mRelationship == "granddaughters") {
    return person->granddaughters();
  }
  else if(mRelationship == "grandfathers") {
    return person->grandfathers(mPMod);
  }
  else if(mRelationship == "grandmothers") {
    return person->grandmothers(mPMod);
  }
  else if(mRelationship == "grandparents") {
    return person->grandparents(mPMod);
  }
  else if(mRelationship == "grandsons") {
    return person->grandsons();
  }
  else if(mRelationship == "mother") {
    Person* mother = person->mother();
    std::set<Person*> result;
    if(mother != nullptr) {
      result.insert(mother);
    }

    return result;
  }
  else if(mRelationship == "nephews") {
    return person->nephews(mPMod, mSMod);
  }
  else if(mRelationship == "nieces") {
    return person->nieces(mPMod, mSMod);
  }
  else if(mRelationship == "parents") {
    return person->parents(mPMod);
  }
  else if(mRelationship == "siblings") {
    return person->siblings(mPMod, mSMod);
  }
  else if(mRelationship == "sisters") {
    return person->sisters(mPMod, mSMod);
  }
  else if(mRelationship == "sons") {
    return person->sons();
  }
  else if(mRelationship == "uncles") {
    return person->uncles(mPMod, mSMod);
  }
  else {
    throw std::invalid_argument("Unknown relationship: " + mRelationship);
  }
}

void Query::validate(bool allow_pmod, bool allow_smod) const {
  if(allow_pmod == false && mPMod != PMod::ANY) {
    throw std::invalid_argument("Parent modifier is not allowed in " + mRelationship + " queries.");
  }

  if(allow_smod == false && mSMod != SMod::ANY) {
    throw std::invalid_argument("Sibling modifier is not allowed in " + mRelationship + " queries.");
  }
}

void Query::validate() const {
  if(mRelationship == "ancestors") {
    validate(true, false);
  }
  else if(mRelationship == "aunts") {
    validate(true, true);
  }
  else if(mRelationship == "brothers") {
    validate(true, true);
  }
  else if(mRelationship == "children") {
    validate(false, false);
  }
  else if(mRelationship == "cousins") {
    validate(true, true);
  }
  else if(mRelationship == "daughters") {
    validate(false, false);
  }
  else if(mRelationship == "descendants") {
    validate(false, false);
  }
  else if(mRelationship == "everyone") {
    return;
  }
  else if(mRelationship == "father") {
    validate(false, false);
  }
  else if(mRelationship == "grandchildren") {
    validate(false, false);
  }
  else if(mRelationship == "granddaughters") {
    validate(false, false);
  }
  else if(mRelationship == "grandfathers") {
    validate(true, false);
  }
  else if(mRelationship == "grandmothers") {
    validate(true, false);
  }
  else if(mRelationship == "grandparents") {
    validate(true, false);
  }
  else if(mRelationship == "grandsons") {
    validate(false, false);
  }
  else if(mRelationship == "mother") {
    validate(false, false);
  }
  else if(mRelationship == "nephews") {
    validate(true, true);
  }
  else if(mRelationship == "nieces") {
    validate(true, true);
  }
  else if(mRelationship == "parents") {
    validate(true, false);
  }
  else if(mRelationship == "siblings") {
    validate(true, true);
  }
  else if(mRelationship == "sisters") {
    validate(true, true);
  }
  else if(mRelationship == "sons") {
    validate(false, false);
  }
  else if(mRelationship == "uncles") {
    validate(true, true);
  }
  else {
    throw std::invalid_argument("Unknown relationship: " + mRelationship);
  }
}

// Generate a query string:
std::string Query::to_string() const {
  std::string result = mName + "'s ";

  if(mPMod == PMod::MATERNAL) {
    result += "maternal ";
  }
  else if(mPMod == PMod::PATERNAL) {
    result += "paternal ";
  }

  if(mSMod == SMod::FULL) {
    result += "full ";
  }
  else if(mSMod == SMod::HALF) {
    result += "half ";
  }

  result += mRelationship;
  return result;
}
