# Syllabus

## Overview

This is a class about data structures.  You learned the basics of coding in your
previous CS classes;  now we'll talk about  how your data  is laid out in memory
and  how to organize it efficiently.  We'll talk about  abstract data structures
like sequences,  heaps,  sets,  and maps;  the concrete data structures  used to
implement them, like vectors, binary trees, and hash tables;  the performance of
the concrete implementations; and how to use these structures to solve problems.

This is also a C++ class, but we won't focus too much on C++ syntax. You'll pick
that up for yourself as you do the programming assignments. Come to lab sections
or ask on Piazza if you have language questions!


## Materials

Everything in this class is optional except the programming assignments. I don't
take attendance. Lecture notes will be available on GitHub. There is no required
reading. There is no textbook.  Everything we talk about in this class is common
computer science  material,  and you can find it  online in  whatever format you
like best.  If you prefer learning from textbooks, here are some possibilities:

- **Data Structures and Other Objects Using C++** by Michael Main and Walter Savitch\
  This used to be the standard textbook for other CS 24 courses.
- **Problem Solving with C++** by Walter Savitch\
  This is an optional textbook for other CS 24 courses.  It's also the
  standard textbook for CS 32.
- **Data Structures and Algorithm Analysis in C++** by Mark Allen Weiss\
  This is the standard textbook for CS 130A.


## Grading

Your  entire grade  comes from programming assignments.  There will be about ten
programming assignments  over the quarter - one per week - all (roughly) equally
weighted.

You have  ten late days  to use over the course  of the quarter.  Any individual
programming assignment  may be turned in  up to five days late.  As long as your
total late time  does not exceed ten days  there is no penalty,  but  using more
than ten days will drop your final score by 10% per extra day used.

I may  decide to curve the class;  if I do,  this will apply to  your cumulative
scores at the end of the quarter, and will only be in your favor. Getting 90% of
the possible points guarantees you at least an A-, 80% a B-, and so on.


## Coding

This is a C++ class,  so you'll be coding in C++.  We'll be using C++ 17 (C++ 20
is the latest standard),  so compile your code with the `-std=c++17` flag.  Your
code must compile with no warnings.  Use the `-Wall`,  `-Wextra`,  and `-Werror`
flags to enforce this, and use Makefiles to save yourself some typing.

Your assignments will be  auto-graded on Gradescope,  which is currently running
GCC 11.2.0 in Ubuntu 22.04 containers.  Code written on other platforms may need
slight tweaking to compile correctly on Gradescope. In particular, Mac users may
need to include more header files.


## Piazza

We'll be using Piazza as a Q&A forum. If you have a question that might apply to
other people as well, it's better to ask on Piazza than to send an email.

If you ask coding questions on Piazza, please:

- Post the smallest section of code that fully describes your problem.
- Include any code as a code snippet, not a screenshot or cell phone photo.
- If you include more than a few lines of your code, make your question private.


## Cheating

All assignments are individual assignments. Write your own code.  In fact, since
this is a  high-level class  where we talk about  abstract data structures,  you
should be able to discuss everything we do without ever sharing any code! If you
do decide to share code, keep in mind:

- **First Offense:** Zero on the assignment _and_ final grade lowered by one letter.
- **Second Offense:** Fail the class.

The programming assignments  are involved enough  that it's virtually impossible
for anyone to have the same code as you  by accident.  As long as you write your
own code you have nothing to worry about.
