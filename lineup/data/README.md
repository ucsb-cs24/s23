# Lineup Data

## Quick Data Generation

Need a large data file for testing? The `quickgen.py` script is the simplest way
to generate one.  In this folder, run something like this:

```sh
./quickgen.py 100 reports > 100reports.txt
./quickgen.py 100 suspects > 100suspects.txt
./quickgen.py 100 solves > 100solves.txt
```

The `main()` function will read multiple files from the command line, so to run
inserts followed by lookups followed by removes, you could list those files one
after another on your `lookup` command.  From the parent folder:

```sh
./lookup data/100reports.txt data/100suspects.txt data/100solves.txt
```

_Caveat:_  When generating N solves,  the script will always generate solves for
reports 1 through N.  If you want to delete  some reports first,  and then other
reports later, you'll need to edit/split your data files.


## Gradescope Tests

The  `more-inserts.tsv` and  `more-removes.tsv` files are the same as those used
by the autograder  for the medium-sized test cases.  Test files similar to those
used for the performance tests can be created with the `generate.py` script. The
argument is the test name in lower case with no spaces, for example:

```sh
./generate.py evolution > evolution.tsv
```

I chose  the parameters so that  each test would run in  about ten seconds on my
2015 Macbook Pro  (using a rather dubious augment tree for report storage).  All
solutions that run in  under 180 seconds in total  (an average of 30 seconds per
test)  on Gradescope will get full credit.  Solutions under 360 seconds will get
partial credit.  Individual performance tests time out after ninety seconds.
