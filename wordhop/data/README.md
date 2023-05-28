# Data File and Query Generation

The "hypercube" and "labyrinth" data files can be automatically generated; see
the `generate.py` script for details.

Given any data file, you can use the `querygen.py` script to generate input for
it.  Each pair of output lines is a query, and the two words will always be the
same length.


## Word Files

These are lists of English words, of various sizes.  There's no easy way to
automatically generate these; I found them in various places on the internet.
The autograder uses `1000.txt` and `370000.txt`.


## Hypercubes

```sh
./generate.py hypercube -d dimensions -s side-length [-f fill-ratio=0.10]
````

These `d`-letter "words" are vectors (the math kind) in `d`-dimensional space.
Each letter position is an axis, and the letter there is a value.  For example,
the vector `<0, 3, 2>` could be represented by the "word" `adc`.  You can jump
between points by changing one coordinate at a time.

These files tend to have many neighbors per "word", so BFS runs slowly on them.
To go faster, use a smarter search that prefers to explore words closer to the
target word first.


## Mazes

```sh
./generate.py labyrinth -w width -h height [-c cycle-chance=0.20]
````

If you encode things properly, your program can solve mazes!  Laid out in two
dimensions, the words from the `maze.txt` file form the following maze:

```
aaaa abaa bbaa      ccaa cdaa ddaa deaa eeaa      ffaa      ggaa ghaa hhaa
aaab      bbab      ccab      ddab                ffab      ggab
aabb      bbbb bcbb ccbb      ddbb debb eebb      ffbb      ggbb ghbb hhbb
          bbbc      ccbc                eebc      ffbc      ggbc      hhbc
aacc abcc bbcc      cccc cdcc ddcc      eecc efcc ffcc fgcc ggcc ghcc hhcc
          bbcd      cccd      ddcd                ffcd      ggcd
aadd abdd bbdd      ccdd cddd dddd      eedd efdd ffdd      ggdd ghdd hhdd
                    ccde      ddde      eede                          hhde
aaee abee bbee bcee ccee      ddee      eeee      ffee fgee ggee ghee hhee
aaef      bbef      ccef                          ffef      ggef      hhef
aaff      bbff bcff ccff cdff ddff deff eeff      ffff fgff ggff ghff hhff
          bbfg      ccfg                eefg      fffg                hhfg
aagg abgg bbgg      ccgg cdgg ddgg degg eegg efgg ffgg fggg gggg      hhgg
          bbgh                ddgh      eegh      ffgh                hhgh
aahh abhh bbhh bchh cchh      ddhh      eehh efhh ffhh fghh gghh ghhh hhhh
                    cchi                eehi                gghi
aaii abii bbii bcii ccii cdii ddii deii eeii      ffii fgii ggii ghii hhii
aaij      bbij                ddij      eeij      ffij      ggij
aajj abjj bbjj bcjj ccjj cdjj ddjj dejj eejj      ffjj      ggjj      hhjj
aajk      bbjk      ccjk                                    ggjk      hhjk
aakk abkk bbkk      cckk cdkk ddkk dekk eekk efkk ffkk fgkk ggkk ghkk hhkk
aakl                cckl      ddkl      eekl      ffkl      ggkl
aall abll bbll      ccll      ddll      eell      ffll fgll ggll ghll hhll
```

Each "word" is a pair of two-letter coordinates concatenated together (the
number of letters required per coordinate increases as the maze gets bigger).
The first few three-letter coordinates would be `aaa`, `aab`, `abb`, `bbb`,
`bbc`, `bcc`, and so on.  This format prevents words from being connected
unless they are directly next to each other.


## Notes

I picked the data file sizes and number of queries to give consistent runtimes
on my Mac: about 15 seconds to load each file (with a dumb algorithm) and about
25 seconds to run the queries, for a total of about 40 seconds per test.
