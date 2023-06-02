# Lineup

In this lab,  you'll implement  a simple crime report database.  When a crime is
reported, you'll record the approximate  height, weight, and age of the suspect.
When a suspect is arrested, you'll get an exact height, weight, and age: you can
then search your database to find  all the cases involving people who match that
description.

```
[vimes@nightwatch lineup]$ ./lineup -i data/simple.tsv
Age:    27
Height: 150
Weight: 72
 - Report 1
 - Report 3
```


## Your Assignment

- Implement the `Database` class described in `Database.h`.
- You **may** use container classes from the standard library.
- Make sure you don't print anything that isn't explicitly allowed.
- Make sure you don't have any memory leaks.
- Make your program run as fast as possible.


## The Database

Your database has four required functions.  Implement these in `Database.cpp`.

- `create()` creates a `Database`.  It will probably just call your constructor.
- `insert(report)` adds a new police report to the database.  Each report has an
  ID,  and contains ranges of values  for each of the  suspect attributes.  If a
  report with that ID already exists, it throws a `DuplicateReport` exception.
- `remove(id)` finds a report by ID and removes it from the database. If no such
  report exists, it throws a `NoSuchReport` exception.
- `search(height, weight, age)`  searches the database for reports with suspects
  that match the given description.  It returns a vector containing  pointers to
  all matching reports; these can be in any order, but the list must not contain
  duplicates.

A report  is considered to match a suspect when  all of the suspect's attributes
fall within the ranges listed on the report. These ranges include the endpoints:
the range 10-20, for example, includes both 10 and 20.


### Input Data

The input data for this lab comes in TSV (tab-separated value) files.  Each file
has several columns:

- `Type` will be one of `report`, `suspect`, or `solved`.  A `report` contains
  data that should be added to the database.  A `suspect` has attributes that
  should be searched for in the database.  A `solved` case should be removed
  from the database.
- `ID` is a positive integer.  If the line type is `report` or `solved`, it will
  be a report ID,  used to identify police reports in the database.  If the line
  type is `suspect`, it will be a suspect ID, which is only used for reference.
- `Age` is an age in years.
- `Height` is a height in centimeters.
- `Weight` is a weight in kilograms.

Ages, heights, and weights are positive `float`s. On a `report` line, these will
be given as ranges, with two values separated by a dash; for example: `18.5-25`.
On a `suspect` line, these will be single values.  On a `solved` line, they will
be absent.


### Memory Management

The `main()` function will create `Report` objects on the heap, and then use the
`insert()` function  to hand them off to your database.  At this point,  reports
become owned by the database, and it's up to you to clean them up.  When reports
are removed  by the `remove()` function,  you should  `delete` them.  You should
also `delete` any cases remaining in the database when it gets destroyed.


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
- Use the `-O3` flag to enable more compile-time optimizations.  Gradescope will
  use this flag when compiling your code.
- Don't assume that the values are in the typical ranges for adult humans!
