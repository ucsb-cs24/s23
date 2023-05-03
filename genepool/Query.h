#ifndef QUERY_H
#define QUERY_H

#include "Enums.h"
#include "GenePool.h"
#include "Person.h"

// This file provides query parsing and execution.
// You can edit it if you want, but you shouldn't need to.
// Gradescope will use the original version.


class Query {
  std::string mName;
  std::string mRelationship;
  PMod        mPMod;
  SMod        mSMod;

  void validate() const;
  void validate(bool allow_pmod, bool allow_smod) const;

public:
  Query(const std::string& text);
  Query(
    const std::string& name,
    const std::string& relationship,
    PMod pmod = PMod::ANY,
    SMod smod = SMod::ANY
  );

  std::set<Person*> run(const GenePool& pool) const;
  std::string to_string() const;
};

#endif
