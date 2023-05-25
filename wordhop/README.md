# WordHop

In this lab,  you'll implement a program that can play a simple word game: given
any two words of the  same length,  it'll find a way to convert  one word to the
other by changing one letter at a time, generating valid words along the way.

```
[midas@gordium wordhop]$ ./wordhop data/words.txt
From: lead
To:   gold
 - lead
 - head
 - held
 - hold
 - gold
```


## Your Assignment

- Implement the `Dictionary` class described in `Dictionary.h`.
- You **may** use container classes from the standard library.
- Make sure you don't print anything that isn't explicitly allowed.
- Make sure you don't have any memory leaks.
- Make your program run as fast as possible.


## The Dictionary

The `Dictionary` class only has two required functions.  Implement these -- and
and helper functions you desire -- in `Dictionary.cpp`.

- `create(stream)` creates a `Dictionary` from an input stream. It will probably
  just call your constructor.
- `hop(from, to)` returns a vector containing a valid chain of words starting
  with `from` and ending with `to`.
  - If an argument is not a valid word, it throws an `Invalid Word` exception.
  - If no valid chain exists, it throws a `NoChain` exception.


### Data Files

Your program should take  exactly one command line argument:  the path to a data
file. This file will be passed to your `Dictionary` constructor as an `ifstream`
and will tell your program which strings are considered valid words.

The data files for this lab are standard word list files with one word per line.
When reading them, ignore blank lines and any lines that contain characters that
are not lower case ASCII letters.  All other lines are valid words.


### Word Chains

For a word chain to be valid, it needs to obey the following rules. Note that if
the source and destination words  are the same,  the only valid chain connecting
them has length one.

- All words in a chain must be valid words.
- All words in a chain must be the same length.
- Any two consecutive words must differ by exactly one letter.
- A chain may not contain the same word more than once.


## Challenge Labs

This is a challenge lab, and the rules are a little different:

- You may work in pairs if you choose to.  If you do, make sure you add both
  partners' names every time you submit to Gradescope.
- To get full credit, you need to generate correct output and also run at
  least as fast as the "baseline" solution.
- The five fastest solutions will get extra credit: twenty-five points for first
  place, twenty points for second place, fifteen points for third place, and so
  on.  All group members get the full bonus.


## Hints

- First make it work.  Then make it fast.
- Use the `-O3` flag to enable more compile-time optimizations.
- The timed tests run many `hop()`s per `Dictionary`.  So if you can do some
  extra work in your constructor to make your `hop()` function faster, it's
  probably worth it.
- <https://xkcd.com/2407/>
