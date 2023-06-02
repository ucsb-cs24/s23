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
./lookup data/100reports.txt data/100suspects.txt 100solves.txt
```

_Caveat:_  When generating N solves,  the script will always generate solves for
reports 1 through N.  If you want to delete  some reports first,  and then other
reports later, you'll need to edit/split your data files.
