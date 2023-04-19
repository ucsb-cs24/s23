# TicTac

In this lab,  you'll implement a program that can read recordings of tic-tac-toe
games  and determine the results.  The games are saved as text, similar to chess
notation.  For example, one possible recording is:

```
1 X B2
2 O C2 # Oops...
3 X C3
4 O A1
5 X B3
6 O A3
7 X B1
```

Your program will parse this record and understand that it represents this game,
and that Player X won:

```
   1   2   3
A  O |   | O
  ---+---+---
B  X | X | X
  ---+---+---
C    | O | X
```

There are two parts to this lab.  The first part is the move parser; this parses
a single line of text  and validates a single `Move` object.  The second part is
the game validator.  This reads a full game file  and ensures that all the moves
are valid; if they are, it prints the outcome of the game.  These two parts will
create separate executables.

Run `git pull upstream master` in your Git repo to get the starter code.


## Your Assignment

- Implement the move parser in `check-move.cpp`. A possible `main()` function is
  written for you,  but you'll need to implement the  `Move` helper functions in
  `Move.cpp` to make it work.
- Implement the game evaluator in `check-game.cpp`.  Writing a `Board` class to
  manage your game state is recommended;  `Board.h` and `Board.cpp` files are
  provided to make this easier.
- Test your code locally!  Only the basic tests are visible on Gradescope; to
  earn full credit, think of and deal with all the corner cases.


## The Move Parser

The move parser reads a single line from standard input. It then parses the line
into a `Move` object  according to the formatting rules below.  If the line does
not obey the formatting rules  exactly,  the parser should print  `Parse error.`
and exit with status code 1. If the line is correctly formatted, it should print
the `Move` object that it parsed and exit with status code 0.

### Move Format

A move is represented as a single line of text in the following format. The term
"whitespace"  means one  or more  characters  that are  considered spaces by the
`isspace()` function from the `cctype` header  and/or  the `std::ws` helper from
the `istream` header.

- The move number.  This is an integer between 1 and 9, inclusive, with no sign.
- Whitespace.
- The player code.  This is either an `X` or an `O`; lower case is also allowed.
- Whitespace.
- The square code. This is a letter followed by a digit. Letters represent rows,
  with row `A` being the top row, `B` the middle, and `C` the bottom; lower case
  is also allowed. Digits represent columns, with 1 being the left column, 2 the
  middle, and 3 the right.
- Optionally, whitespace.
- Optionally, a comment.  This is any text beginning with the `#` character and
  extending to the end of the string.  If a comment is present, the preceding
  whitespace is required.

When printing moves, your program should use the same format. When whitespace is
required, it should always print a single space character. It should never print
comments or the whitespace that precedes them. Player and row codes should be in
upper case.


## The Game Evaluator

The evaluator reads an entire game from standard input. It considers one line at
a time.  If the line  cannot be parsed  as a move,  it prints `Parse error.` and
exits with  status code 1.  If the move is  invalid according to the game rules,
as defined below, it prints `Invalid move.` and exits with status code 2.

If the evaluator reaches the end of its input  without encountering an error, it
prints the result of the game and exits with status code 0. The possible results
are:

- `Game in progress: New game.`  If no moves have been made.
- `Game in progress: X's turn.`  If it is Player X's turn to play.
- `Game in progress: O's turn.`  If it is Player O's turn to play.
- `Game over: X wins.`  If the game is over and Player X won.
- `Game over: O wins.`  If the game is over and Player O won.
- `Game over: Draw.`  If the game is over and neither player won.

### Game Format

A game  is represented as text.  Every line contains exactly one move.  The text
may or may not end with a newline.

### Game Rules

- There are two players, Player X and Player O.
- There are nine squares, arranged in a 3x3 grid.
- The game begins with all nine squares unclaimed.
- Either player may play first; after this, the players must alternate.
- The first move is move number one, the second move is move number two, and so
  on; each move has a number one higher than the previous move.
- Each move must claim an unclaimed square.
- If any player claims three squares that form a line horizontally, vertically,
  or diagonally, that player wins and the game is over; no further moves are
  allowed.
- If all squares are claimed but no player has formed a line, the game is a
  draw; no further moves are allowed.


## Hints

- All of the test input is ASCII text.
- The expected output is always one line of text followed by a newline.
- A `std::istringstream` may be helpful when parsing moves.
- Use `Ctrl+D` on Linux and Mac (or `Ctrl+Z` then `Enter` on Windows) to send an
  "end of input" to your evaluator when testing manually.
- Save your test cases in text files so you don't have to type them every time!
  - Use `echo "some text" | ./program` to send arbitrary text to `program`'s
    standard input.
  - Use `cat some/file | ./program` to send the contents of `some/file` to
    `program`'s standard input.
  - Use a shell script for loop to loop over your test files.
- The autograder will  always run your programs  with no command line arguments,
  so you can use a command line flag to enable extra output for debugging.
