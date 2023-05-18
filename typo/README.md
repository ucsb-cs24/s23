# Typo

In this lab, you'll write a touchscreen keyboard typo corrector.  You'll read in
a  series of points  where the user  touched the screen,  compare these with the
positions of the keys on the screen, and determine which words that the user was
most likely trying to type.

The  simplest algorithm to collect the  top N items from a list uses a min-heap.
You'll need to write one of these as well. You'll then be able to use it in your
typo-correcting algorithm.


## Your Assignment

- Implement the heap described below in `Heap.cpp`.
- Implement the word list described below in `WordList.cpp`.
- You may not use any container classes from the standard library.
  - The one exception is the `std::vector` type, which is allowed.
- You may not use any functions from the `algorithm` header.
- Make sure you don't print anything that isn't explicitly allowed.
- Make sure you don't have any memory leaks.


## The Heap

Your heap is declared for you in  `Heap.h`.  It stores  instances of an  `Entry`
type. These contain two member variables: a string (the word you're storing) and
a number (the score of that word). You'll use the scores to order entries within
the heap.

Your heap should be a binary min-heap.  When you want to add a high-scoring word
to a full heap,  you'll use `pop()` to make room,  so you want `pop()` to remove
the word with the lowest score.


### Storage

The `Heap` class has a single `Entry*` to hold all of its data. Fortunately, you
can store binary heaps in arrays very efficiently.  The top of the heap lives at
index zero, its left child lives at index one, and so on. The entry at index `i`
has the following neighbors (if they exist):

- Its parent is at index `(i - 1) / 2`.
- Its left child is at index `i * 2 + 1`.
- Its right child is at index `i * 2 + 2`.

There's a nice visualization on Wikipedia:
<https://en.wikipedia.org/wiki/Binary_tree#Arrays>

Your heap  should not resize.  It learns its capacity when it's constructed, and
it will never hold more entries than that.


### Percolation

A min-heap has the property that every item is smaller than its children.  So if
you add or remove items from your heap,  you'll need to move them around to keep
this property.

When you push an item onto the heap,  put it in the first available slot.  Then,
if its parent has a higher score, swap it with its parent. Keep doing this until
you find a parent with a lower score, or the new item becomes the new top.  This
is called "percolating up."

When you pop an item off the heap, you remove the entry at index zero.  Then you
need to fill the gap. Take the last entry in the array and put it at index zero;
then,  if it has any children with lower scores, swap it with the child with the
lowest score.  If both children have the same lower score, swap it with the left
child.  Keep doing this  as long as it has  any lower-scoring children.  This is
known as "percolating down."


### Functions

Implement the `Heap` member functions in `Heap.cpp`.

- The constructor creates an empty heap with the given capacity.
- The copy constructor makes a copy of an existing heap.
- The move constructor steals the memory from an existing heap.
- The `capacity()` function returns the maximum capacity of the heap.
- The `count()` function returns the number of items in the heap.
- The `lookup()` function returns a reference to the entry at a given index.
  If the index is invalid, it throws a `std::out_of_range` exception.
- The `pop()` function removes the entry with the lowest score and returns it.
  If there are no items in the heap, it throws a `std::underflow_error`.
- The `push()` function adds a new entry to the heap.  If there is no space for
  the new item, it throws a `std::overflow_error`.
- The `pushpop()` function is a more efficient version of a `pop()` followed by
  a `push()`.  Instead of replacing the popped entry with the last entry in the
  vector, it replaces it with the pushed entry, and then percolates that down.
  If there are no items in the heap, it throws a `std::underflow_error`.
- The `top()` function returns a reference to the entry with the lowest score.
  If there are no items in the heap, it throws a `std::underflow_error`.


## The Word List

Your word list is  declared for you  in `WordList.h`.  It's a  simple class with
two important jobs: it holds a list of all valid words, and owns the `correct()`
function that translates sequences of points into probable words.


### Functions

Implement the `WordList` member functions in `WordList.cpp`.

- The constructor creates a word list from a words file.  Each line of this file
  is a single word.  It ignores words that are not entirely lower case ASCII.

- The `correct()` function  is where the important stuff happens.  It takes in a
  sequence of points; these are the points where the user touched the screen. It
  then finds all the words of the  correct length,  scores them according to the
  scoring algorithm below, and uses a `Heap` with capacity `maxcount` to collect
  the most likely words.  Words with scores lower than `cutoff` are not included
  in the output.


### Scoring

For every sequence  of touch points,  we can calculate  a similarity score for a
word of the same length.  To do this, first use the `QWERTY` map  in `Point.cpp`
to look up the location of the letters in the word on a QWERTY keyboard. You now
have two sequences of points:  one sequence of touch points, and one sequence of
key locations.

Then, calculate the Euclidean distance `d` between the first touch point and the
first key location.  Then convert this to a score `s` using the scoring equation
`s = 1 / (10 d² + 1)`. Repeat this for the second touch point and the second key
location, and then the third, and so on.

The score for a word is the average (mean) score of all its letters;  these will
range from near-zero to one.  The higher the score, the better the match.

For example, to score the word `was` (the user was trying to type `wax`):

| Touch Point  | Letter | Key Location | `d`   | `s`   |
|--------------|:------:|--------------|------:|------:|
| (0.98, 0.02) | `w`    | (1.00, 0.00) | 0.028 | 0.992 |
| (0.28, 0.95) | `a`    | (0.25, 1.00) | 0.058 | 0.967 |
| (1.71, 2.03) | `s`    | (1.25, 1.00) | 1.128 | 0.073 |

In this case, the word score is (0.992 + 0.967 + 0.073) / 3 = 0.677.


## Hints

- Write your heap first and make sure it passes all the heap tests.
- Heaps are lazy!  If a parent entry and a child entry have the same score,
  there's no need to swap them.
- The `Entry` structure is nested inside the `Heap` class, so from outside the
  `Heap` class you'll need to refer to it as `Heap::Entry`.
- The `islower()` function in `cctype` is only guaranteed to return zero or
  non-zero, _not_ a `bool`.  So checking `if(islower(c) == true)` may not do
  what you expect!  Use `if(islower(c))` or `if(islower(c) != 0)` instead.
- The interactive program in `main.cpp` expects numbers as its input.  Want to
  type words instead?  Try piping (`|`) the output of the `helper.py` script to
  the input of the interactive program:
  ```
  [wendy@neverland typo]$ ./helper.py | ./a.out /usr/share/dict/words
  > holster
   - 0.524: holster
   - 0.493: hoister
   - 0.483: bolster
   - 0.454: booster
   - 0.451: fooster
   - 0.451: toaster
   - 0.450: jouster
   - 0.450: rooster
  ```
