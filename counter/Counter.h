#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>
#include <string>

// This is the Counter class you need to implement.
// It includes the Counter::Iterator as a nested class.
// If you want more space to implement helper classes,
// you can use the DataStore.* and Index.* files.

class Counter {
public:
  class Iterator {
    // Member Variables

  public:
    const std::string& key() const;
    int value() const;

    Iterator& operator ++ ();
    bool      operator == (const Iterator& other) const;
    bool      operator != (const Iterator& other) const;
  };

private:
  // Member Variables

private:
  // Helper Functions

public:
  Counter();
  ~Counter();

  size_t count() const;
  int    total() const;

  void inc(const std::string& key, int by = 1);
  void dec(const std::string& key, int by = 1);
  void del(const std::string& key);
  int  get(const std::string& key) const;
  void set(const std::string& key, int count);

  Iterator begin() const;
  Iterator end() const;
};

#endif
