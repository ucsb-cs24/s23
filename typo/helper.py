#! /usr/bin/env python3
import random
import sys

# This program reads words from standard input, one per line.
# It then converts each letter to a key location with added Gaussian noise.
# It prints the key locations in the format expected by main.cpp.

QWERTY = (
    (0.25, 1.00), # A
    (4.75, 2.00), # B
    (2.75, 2.00), # C
    (2.25, 1.00), # D
    (2.00, 0.00), # E
    (3.25, 1.00), # F
    (4.25, 1.00), # G
    (5.25, 1.00), # H
    (7.00, 0.00), # I
    (6.25, 1.00), # J
    (7.25, 1.00), # K
    (8.25, 1.00), # L
    (6.75, 2.00), # M
    (5.75, 2.00), # N
    (8.00, 0.00), # O
    (9.00, 0.00), # P
    (0.00, 0.00), # Q
    (3.00, 0.00), # R
    (1.25, 1.00), # S
    (4.00, 0.00), # T
    (6.00, 0.00), # U
    (3.75, 2.00), # V
    (1.00, 0.00), # W
    (1.75, 2.00), # X
    (5.00, 0.00), # Y
    (0.75, 2.00)  # Z
)


if __name__ == '__main__':
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', '--echo',  action='store_true',      help='print points to stderr as well as stdout')
    parser.add_argument('-s', '--sigma', type=float, default=0.25, help='standard deviation to use when adding noise')
    parser.add_argument('filename',      nargs='?',                help='file to read words from (instead of stdin)')
    args = parser.parse_args()

    if args.filename:
        file = open(args.filename)
    else:
        file = sys.stdin

    for line in file:
        line = line.lower().strip()
        text = []
        for c in line:
            if 'a' <= c <= 'z':
                point = QWERTY[ord(c) - 97]
                x = point[0] + random.gauss(0, args.sigma)
                y = point[1] + random.gauss(0, args.sigma)
                text.append('%.3f %.3f' % (x, y))

        text = '  '.join(text)
        if args.echo:
            sys.stderr.write(text + '\n')
        print(text, flush=True)
