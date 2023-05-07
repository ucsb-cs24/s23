# Gene Pool

In this assignment,  you'll build a database program that stores a collection of
people and  their biological relatives.  You can then search this database based
on the relationships between the people it contains.

The "user interface" logic  is written for you.  The `main.cpp` file handles the
main input-output loop,  and the `Query.*` files handle parsing, validating, and
executing queries.  You can edit these files for testing, but you shouldn't need
to.  On Gradescope, your code will be run against the originals.

You'll need to figure out how to best store your data.  Try to make relationship
queries as easy as possible.  Write the  `GenePool` class and the basic `Person`
functions first - the things you'll need to read data from a file  and fill your
database with people.  Then implement the  relationship query  functions  in the
`Person` class.  As soon as you have some of these done, you can start testing:

```
[iris@olympus genepool]$ ./genepool data/Cunco.tsv
> Kind's mother
 - Rainbow Lake
> Kind's siblings
 - Danehill Dancer
> Saintly_Speech's maternal ancestors
 (no results)
> Well_Spoken's maternal ancestors
 - Saintly Speech
> Well_Spoken paternal ancestors
 - Fairy Bridge
 - Northern Dancer
 - Sadlers Wells
```


## Your Assignment

- Write a `GenePool` class that manages a database of people.
- Write a `Person` class that supports relationship queries.
- You **may** use container classes from the standard library.
- Make sure you don't print anything that isn't explicitly allowed.
- Make sure you don't have any memory leaks.


### Reading the Data

Your program  will be passed one argument on the command line.  This is the path
to  a file containing  some genealogical data.  The `main()` function  will open
this file and pass it as a `std::istream` to your `GenePool` constructor.

The data is in a slightly modified TSV (tab-separated values) format, one person
per line.  However, some lines should be ignored:

- Lines that start with the hash sign (`#`) are comments.
- Empty lines are included for spacing and readability.

All other lines are data.  They will consist of four strings,  separated by tabs
(the `'\t'` character in C, ASCII value 0x09). These strings may contain spaces.
They are, in order:

- The name of a person.
- The gender of the person, either `male` or `female`.
- The name of the person's mother, or `???` if unknown.
- The name of the person's father, or `???` if unknown.

You may assume  that data lines  will always be valid.  There will never be more
than one person with any given name,  and people will always appear later in the
file than their parents.


### Querying the Data

Once you've read in the entire data file,  your program will prompt the user and
then wait for input, which will come in this format (not all modifiers are valid
for all relationships; see the next section for details):

```
[name]'s [parent-modifier] [sibling-modifier] [relationship]
```

- `name` is the name of a person in the database; the `'s` is optional.
- `parent-modifier` is an optional relationship modifier; it can be either
  `maternal` or `paternal`.
- `sibling-modifier` is an optional relationship modifier; it can be either
  `full` or `half`.
- `relationship` is one of the relationships described in the next section.

Your program should parse the query,  execute it against your database, and then
print the result, listing the people it found in alphabetical order. If an error
occurs,  it should print the error message instead.  Finally, it should re-print
the prompt and wait for more input.  Repeat this loop until you reach the end of
the input stream.

The logic  to parse and validate queries  is written for you  (see the `Query.*`
files), but you'll need to write the functions that do the actual lookups within
your database (see the `Person.*` files).


## Relationships

All the relationships you'll be dealing with are biological ones. You can assume
that all people have exactly two biological parents - one mother and one father.
You can also ignore all non-biological relationships:  you won't need to support
queries for spouses, in-laws, step-siblings, etc.  The relationships you do need
to support are explained below.

- Your **mother** is your female parent.
- Your **father** is your male parent.
- Your **parents** are your mother and your father.
  - Your **maternal** parent is your mother.
  - Your **paternal** parent is your father.

- Your **grandparents** are the parents of your parents.
  - Your **maternal** grandparents are your mother's parents.
  - Your **paternal** grandparents are your father's parents.

- Your **children** are the people who have you as a parent.
- Your **sons** are your male children.
- Your **daughters** are your female children.

- Your **grandchildren** are your children's children.
- Your **grandsons** are your male grandchildren.
- Your **granddaughters** are your female grandchildren.

- Your **siblings** are people who share a parent with you, but are not you.
  - Your **maternal** siblings have the same mother as you.
  - Your **paternal** siblings have the same father as you.
  - Your **full** siblings have the same mother and father as you.
  - Your **half** siblings share only one parent with you.
- Your **brothers** are your male siblings.
- Your **sisters** are your female siblings.

- Your **nieces** are the daughters of your siblings.
  - Your **maternal** nieces are the daughters of your maternal siblings.
  - Your **paternal** nieces are the daughters of your paternal siblings.
  - Your **full** nieces are the daughters of your full siblings.
  - Your **half** nieces are the daughters of your half siblings.

- Your **nephews** are the sons of your siblings.
  - Your **maternal** nephews are the sons of your maternal siblings.
  - Your **paternal** nephews are the sons of your paternal siblings.
  - Your **full** nephews are the sons of your full siblings.
  - Your **half** nephews are the sons of your half siblings.

- Your **aunts** are your parents' sisters.
  - Your **maternal** aunts are your mother's sisters.
  - Your **paternal** aunts are your father's sisters.
  - Your **full** aunts your parents' full sisters.
  - Your **half** aunts your parents' half sisters.

- Your **uncles** are your parents' brothers.
  - Your **maternal** uncles are your mother's brothers.
  - Your **paternal** uncles are your father's brothers.
  - Your **full** uncles your parents' full brothers.
  - Your **half** uncles your parents' half brothers.

- Your **cousins** are the children of your aunts and uncles.
  - Your **maternal** cousins are the children of your mother's siblings.
  - Your **paternal** cousins are the children of your father's siblings.
  - Your **full** cousins are the children of your parents' full siblings.
  - Your **half** cousins are the children of your parents' half siblings.

- Your **ancestors** are your parents, your parents' parents, and so on.
  - Your **maternal** ancestors are your mother and her ancestors.
  - Your **paternal** ancestors are your father and his ancestors.
- Your **descendants** are your children, your children's children, and so on.


### Edge Cases

People can only have relationships through known parents. People with completely
unknown parents should never be considered  siblings.  People need  at least one
known parent in common before they can be treated as siblings.

People who have an unknown father have no paternal siblings. The same applies to
maternal siblings  when the mother is unknown.  You can only have  a maternal or
paternal relationship through a known parent.

Siblings who share one known parent and have the other parent unknown  should be
considered half siblings. For example, if Alice and Bob are both the children of
Eve and an unknown father, they should be treated as half siblings.

People can show up in multiple relationships. If Alice and Bob from the previous
paragraph  had a child named Carol,  Alice would be both  Carol's mother and her
aunt.  Bob would be Carol's father and her uncle.  Eve would be Carol's maternal
and paternal grandparent.  Carol would be her own cousin.

Unknown people (those represented with `???` in the input file)  should never be
included in the output of any relationship queries.  Alice's `father()` function
should return `nullptr`;  a query for her parents should return a set containing
only Eve.


## Hints

- Look at all the starter code.  See what's written for you, and how the parts
  you need to write fit into the existing code.
- Write your `GenePool` functions first, and just enough of the `Person` class
  to get it to compile.  Then you can use the  special query `everyone` to see
  everyone in your database and make sure you read the data file correctly.
- The `std::getline()` function takes an optional third `delimiter` argument -
  you can use this to parse tab-delimited strings from a `std::istringstream`.
- You can use `mymap[key] = value` to insert things into a `std::map` (there's
  an `insert()` function too, but it's a pain to work with).
- You can use `myset.merge(other)` to move items from `other` into `myset`, but
  beware! This function removes items from `other` when it moves them, so don't
  pass in a set you need to keep intact.
- You can use `for(Person* person: myset)` (also known as a range-based for
  loop) to iterate over all the people in a set.
- Write stubs for all the relationship functions first, then implement and test
  them one by one.  It's a lot easier to debug one function than twenty.
- Think before you start coding!  There are a lot of relationships you need to
  support, but if you're smart about re-using functions you won't actually have
  to write much code.
