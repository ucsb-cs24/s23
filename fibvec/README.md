# FibVec

In this assignment,  you'll implement the _sequence_ abstract data type  using a
_vector_ as the underlying concrete data type.  Unlike more traditional vectors,
which grow by a constant factor when full, your vector will always resize to the
next larger (or smaller) Fibonacci number.

Run `git pull upstream master` in your Git repo to get the starter code.


## Fibonacci Numbers

The  Fibonacci numbers are  a sequence of numbers  where each term is the sum of
the previous two terms.  The `n`th Fibonacci number is denoted `f(n)`:

```
f(0) = 0
f(1) = 1
f(2) = 1
f(n) = f(n-1) + f(n-2)
```

The first few Fibonacci numbers are: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...


## Your Assignment

- Implement a vector that stores a sequence of `int`s.
- You can't use any container types from the standard library.
- Make sure your final code doesn't print anything.
- Make sure you don't have any memory leaks.


## The FibVec Class

Implement your vector in a class called `FibVec`.  Write the class definition in
`FibVec.h` and implement the member functions in `FibVec.cpp`.  Your vector must
obey the following rules:

- The vector must always have a capacity that is a Fibonacci number.
- The vector must always have a capacity greater than or equal to `f(2) = 1`.
- When inserting into a vector with capacity `f(n)`: if there is no room for the
  item, the vector must resize its capacity to the next Fibonacci number (`f(n+1)`).
- When removing from a vector with capacity `f(n)`: if the number of items drops
  below `f(n-2)`, the vector must resize its capacity to `f(n-1)`.


## Member Functions

Your `FibVec` class must implement all of the following public member functions.
You can add private helper functions as well if it makes your life easier.

Values should be represented as `int`s  and sizes, indices, and counts should be
represented as `size_t`s. If a function doesn't modify your vector, mark it as a
`const` member function.

- The default constructor creates an empty vector with a capacity of `f(2) = 1`.
- The destructor cleans up all allocated memory owned by the class.
- The `capacity` function returns the total size of the storage buffer.
- The `count` function returns the number of items stored in the vector.
- The `insert` function takes two arguments: the first is a value and the
  second is an index.  It stores the value at the given index.  If the index
  is invalid, it throws a `std::out_of_range` exception.
- The `lookup` function takes one argument: an index.  It returns the value
  stored at that index. If the index is invalid, it throws a `std::out_of_range`
  exception.
- The `pop` function takes no arguments.  It removes and returns the last value
  in the vector.  If the vector is empty, it throws a `std::underflow_error`.
- The `push` function takes one argument: a value.  It inserts that value at
  the end of the vector.  It has no return value.
- The `remove` function takes one argument: an index.  It removes the value
  stored at that index and returns it.  If the index is invalid, it throws a
  `std::out_of_range` exception.


## Hints

- Your vector should never resize by more than one step per function call.
- Write stubs for all the required member functions first. If your code compiles
  on Gradescope, you have the correct function signatures (regardless of whether
  or not you pass any of the other tests).
- If you get linker errors, you likely have the wrong function signatures.  Make
  sure that your class and function names are correct, and that you're using the
  correct parameter types and `const` qualifiers.
- Include `cstddef` in `FibVec.h` to get the `size_t` type.  Include `stdexcept`
  in `FibVec.cpp` to get the exception types.
- Note that `size_t` is an unsigned integer type.  Don't subtract from zero!
