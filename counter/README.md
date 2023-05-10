# Counter

In  this lab,  you'll  implement the  _map_  abstract data type.  This map  uses
strings as keys and integers as values,  and supports  fast lookup and update by
key.  This makes it perfect for a very common programming task: counting things.

It also supports iteration  in insertion order:  when you iterate over this map,
you see its keys  in the same order  that they were added to the map.  This is a
convenient feature in many cases -- especially for user-friendly output.

To support  both of  these operations  with a good runtime,  it's recommended to
use a _doubly linked list_ to store your key value pairs (allowing for efficient
iteration),  and to use a _hash table_ as an index into that list  (allowing for
efficient lookup and update).

Run `git pull upstream master` in your Git repo to get the starter code.


## Your Assignment

- Implement the `Counter` class in `Counter.cpp`.
- Implement the `Counter::Iterator` class in `Iterator.cpp`.
- You can't use any container types from the standard library.
- Make sure your final code doesn't print anything.
- Make sure you don't have any memory leaks.
- Make your code run as fast as you can.


## The Counter

This counter is a map  from `std::string`s  to `int`s.  Any strings that are not
stored in the counter have an implicit count of zero,  and will not show up when
iterating over the counter. Strings that are stored in the counter have explicit
counts, and always show up when iterating, even if their counts are zero.

The following  functions allow  users to interact with  the counter.  All of the
non-`const` functions  except `del()`  add keys  to the counter  if they are not
already present.  The `del()` function  removes a key.  The `const` functions do
not modify the counter in any way.

- `inc(k, d)` increments a count by a given value (default one).
- `dec(k, d)` decrements a count by a given value (default one).
- `del(k)` removes a key from the counter, setting its count to (implicit) zero.
- `get(k)` looks up a count by key.  If the key isn't present, it returns zero.
- `set(k, v)` sets a count by key.

Your counter should support the following functions:

- The default constructor creates an empty `Counter`.
- The destructor cleans up any allocated memory.
- `begin()` returns an iterator to the first-inserted item in the counter.
- `count()` returns the number of keys stored in the counter.
- `end()` returns an invalid "end" iterator (see below).
- `total()` returns the sum of all counts in the counter.


## The Counter Iterator

The counter iterator  is a lightweight iterator class,  similar to the iterators
from the C++ standard library.  It's essentially a reference to a key-value pair
stored  in a `Counter`.  You can use its  getter functions to access the key and
the value, and you can increment it to move it to the next key.

Additionally, there's a special "end" iterator. This is an invalid iterator used
to indicate  that there are  no more key-value pairs  to iterate over.  Only the
`==` and `!=` operators may be used on an "end" iterator.

Your iterator must support the following functions and operators.  A constructor
is recommended, but not required.

- The `key()` function gets the key from the key-value pair that the iterator
  is currently referencing.
- The `value()` function gets the value from the key-value pair that the
  iterator is currently referencing.
- The  `++`  operator increments the iterator,  moving it to the  next key-value
  pair in the `Counter`.  If an iterator currently refers to the  last key-value
  pair, incrementing it should make it equal to the "end" iterator.
- The `==` and `!=` operators compare two iterators.


## Performance

Part of your grade on this lab comes from performance. To make sure your counter
is implemented  efficiently,  the autograder will make sure it can process large
amounts of data in a  reasonable time frame.  This time is measured in  seconds,
not big-O, but with large data sets, the better your big-O runtime is the better
your real-time runtime will be.

There is extra credit available  for the fastest implementations!  The five best
programs will receive  10, 8, 6, 4, and 2  points of extra credit, respectively.
Only submissions made before the due date are eligible for extra credit.


## Hints

- All `int`s are valid counts, including negative numbers.
- When a key is removed from a counter, it should no longer show up when
  iterating over that counter.  If it gets re-inserted later, it should show
  up at the end of the iteration (not in its previous position).
- The `++` operator returns a reference to the object it operated on.
- When running performance tests, the grader will compile your code with the
  `-O3` option to enable compile-time optimization.
