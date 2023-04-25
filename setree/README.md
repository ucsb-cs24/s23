# Setree

In this  lab,  you'll implement the  _set_  abstract data type  using a  _binary
search tree_ as the  concrete data type.  The set will store `std::string`s  and
order them asciibetically:  all the values in a node's left subtree will be less
than the value stored in that node, and all the values in the right subtree will
be greater.

This tree  is _not_ self-balancing.  There will be cases when it has poor (O(n))
performance.

Run `git pull upstream master` in your Git repo to get the starter code.


## Tree Notation

A binary tree might look something like this:

```
    d
   / \
  b   e
 / \   \
a   c   f
```

But we need an easy way  to print a tree to the console.  So we'll define a tree
notation that lets us write a tree structure as a single line. In this notation,
the tree pictured above would look like this:

```
((a b c) d (- e f))
```

More formally:
- The tree notation for a leaf node is simply its value.
- The tree notation for a non-existent node is a hyphen (`-`; ASCII value 45).
- The tree notation for a non-leaf node is:
  - A left parenthesis, followed by
  - the tree notation for its left subtree, followed by
  - a space, followed by
  - the node's value, followed by
  - a space, followed by
  - the tree notation for its right subtree, followed by
  - a right parenthesis.
- The tree notation for an empty tree is `-`.


## Your Assignment

- Implement a set in the `.h` and `.cpp` files provided:
  - Declare a binary tree node type called `Node` in `Node.h`.
  - Implement any `Node` member functions (or helper functions) in `Node.cpp`.
  - Implement the `Set` member functions declared in `Set.h` in `Set.cpp`.
  - Order the stored values asciibetically (`A` before `Z` before `a`).
- You can't use any container types from the standard library.
- Make sure your final code doesn't print anything.
- Make sure you don't have any memory leaks.


## Functions

Implement the following `Set` member functions in `Set.cpp`.

- The default constructor creates an empty set.
- The copy constructor creates a copy of an existing set.
- The move constructor takes nodes from a set that's about to be deleted.
- The destructor deletes all the nodes in the set.
- `clear()` removes all the values from the set. It returns the number of values
  that were removed.
- `contains(value)` checks if a value is present in the set.
- `count()` returns the total number of values in the set.
- `debug()` does whatever you want it to.  Implement this if you want some other
  output when testing locally; otherwise ignore it.  This function isn't tested.
- `insert(value)` adds a value to the set. If the value is already present, this
  function does nothing;  otherwise,  it adds the value  in a new leaf node.  It
  returns the number of values that were added.
- `lookup(n)` returns the value `value` such that there are exactly `n` values
  smaller than `value` in the set.  If no such element exists, it throws a
  `std::out_of_range` exception.
- `print()` prints the structure of the set in tree notation, as defined above.
- `remove(value)` removes a value from the set  and returns the number of values
  that were removed.
  - If the value to remove is on a node with less than two children,  it removes
    that node.  If the node had a child, the child takes its place.
  - If the value is on a node with two children, it finds the largest value `v`
    that is present in the set but smaller than `value`. It then copies `v` into
    the node containing `value` and removes the node that originally held `v`.
  - If `value` isn't present in the set, it doesn't remove anything.


## Hints

- Recursion works even better with trees than it does with linked lists.
- The standard string comparison operators will give you the correct ordering.
- Storing a `count` (the size of the subtree) on every node is recommended.
- The `insert()` and `remove()` functions will always return one or zero.
- If you get a segmentation fault and the stack trace shows that it's happening
  in a `std::string` function, you almost certainly have a dangling pointer to a
  node you `delete`d.  Check your `remove()` function and make sure you set any
  pointers to deleted nodes to `nullptr`!
