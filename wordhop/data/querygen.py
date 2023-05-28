#! /usr/bin/env python3

import argparse
import collections
import random

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--queries',   type=int, default=10, help='number of queries to generate')
    parser.add_argument('-m', '--min-words', type=int, default=2,  help='ignore lengths with this many words or fewer')
    parser.add_argument('datafile', help='path to a data file')
    args = parser.parse_args()

    # Load all the valid words in the data file.
    words = collections.defaultdict(list)
    with open(args.datafile) as file:
        for line in file:
            line = line.strip()
            if not line.isalpha():
                continue
            if not line.islower():
                continue
            words[len(line)].append(line)

    # Only consider lengths with at least min_words words.
    words = {k:v for k, v in words.items() if len(v) > args.min_words}
    total = sum(len(w) for w in words.values())

    for n in range(args.queries):
        # Pick a length, weighted by number of words.
        r = random.randrange(total)
        for l, w in words.items():
            if r < len(w):
                break
            r -= len(w)

        # Select two words for the query and print.
        src, dst = random.sample(w, 2)
        print(src)
        print(dst)


if __name__ == '__main__':
    main()
