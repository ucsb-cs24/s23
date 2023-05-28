#! /usr/bin/env python3

import argparse
import random
import sys

class DisjointSet:
    def __init__(self):
        self.parent = self

    def find(self):
        if self.parent is not self:
            self.parent = self.parent.find()

        return self.parent

    def union(self, other):
        srep = self.find()
        orep = other.find()

        if srep is not orep:
            srep.parent = orep


def coord(c, n):
    """Converts numbers to maze coordinates (with a maximum of n)."""
    return ''.join(chr((c + i) // n % 26 + 97) for i in range(n))


def generate_labyrinth(width, height, cycle_chance, verbose):
    """Generates a maze using Kruskal's Algorithm with extra back-edges."""
    print('# Labyrinth: height=%d, width=%d, cycle_chance=%f' % (
        width,
        height,
        cycle_chance
    ))

    selected = []
    vertices = {}
    edges    = []

    # Add all "rooms"; make list of "doors":
    for x in range(width):
        for y in range(height):
            v = (x*2, y*2)
            vertices[v] = DisjointSet()
            selected.append(v)

            if x > 0:
                edges.append((x*2 - 1, y*2))
            if y > 0:
                edges.append((x*2, y*2 - 1))

    # Add "doors" at random to connect everything:
    random.shuffle(edges)
    for edge in edges:
        if edge[0] & 1 == 0:
            v1 = vertices[(edge[0], edge[1] - 1)]
            v2 = vertices[(edge[0], edge[1] + 1)]
        else:
            v1 = vertices[(edge[0] - 1, edge[1])]
            v2 = vertices[(edge[0] + 1, edge[1])]

        if v1.find() is not v2.find() or random.random() < cycle_chance:
            selected.append(edge)
            v1.union(v2)

    # The number of letters needed to represent each dimension:
    xn = (width  * 2 - 1) // 25 + 2
    yn = (height * 2 - 1) // 25 + 2

    # Encode as "words" and print:
    random.shuffle(selected)
    for point in selected:
        print(coord(point[0], xn) + coord(point[1], yn))

    # Print a 2D representation to stderr:
    if verbose:
        selset = set(selected)
        for y in range(height*2 - 1):
            for x in range(width*2 - 1):
                if (x, y) in selset:
                    sys.stderr.write(coord(x, xn) + coord(y, yn))
                    # sys.stderr.write(coord(x, xn) + '-' * yn)
                    # sys.stderr.write('-' * xn + coord(y, yn))
                else:
                    sys.stderr.write(' ' * (xn + yn))
            sys.stderr.write('\n')


def generate_hypercube(dimensions, side_length, fill_ratio):
    """Selects random points in a s^d hypercube."""
    print('# Hypercube: dimensions=%d, side_length=%d, fill_ratio=%f' %(
        dimensions,
        side_length,
        fill_ratio
    ))

    remaining = round(fill_ratio * side_length ** dimensions)
    selected  = set()

    # Select points at random until we've found enough:
    while remaining > 0:
        point = tuple(random.randrange(side_length) for _ in range(dimensions))
        if point not in selected:
            selected.add(point)
            remaining -= 1

    # Randomize using the random seed (not the secret set key):
    selected = sorted(list(selected))
    random.shuffle(selected)

    for point in selected:
        print(''.join(chr(c + 97) for c in point))


def main():
    parser     = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest='command', help='generation method')

    parser.add_argument('-s', '--seed', type=int, help='random seed')

    hypercube = subparsers.add_parser('hypercube')
    hypercube.add_argument('-d', '--dimensions',  type=int,   required=True, help='number of dimensions')
    hypercube.add_argument('-s', '--side-length', type=int,   required=True, help='length of each side')
    hypercube.add_argument('-f', '--fill-ratio',  type=float, default=0.10,  help='density')

    labyrinth = subparsers.add_parser('labyrinth', add_help=False)
    labyrinth.add_argument('-w', '--width',         type=int,   required=True, help='number of columns')
    labyrinth.add_argument('-h', '--height',        type=int,   required=True, help='number of rows')
    labyrinth.add_argument('-c', '--cycle-chance',  type=float, default=0.20,  help='probability of adding a back-edge')
    labyrinth.add_argument('-v', '--verbose',       action='store_true',       help='print the 2d layout to stderr')
    labyrinth.add_argument('-?', '--help',          action='help',             help='print this help message')

    args = parser.parse_args()

    if args.command is None:
        parser.print_help()
        exit(1)
    elif args.command not in ('hypercube', 'labyrinth'):
        sys.stderr.write('Unknown command: "%s"\n' % args.command)
        exit(1)

    if args.seed is None:
        args.seed = random.randrange(sys.maxsize)
    random.seed(args.seed)
    print('# Random seed: %d' % args.seed)

    if args.command == 'hypercube':
        if args.side_length > 26:
            sys.stderr.write('Side length must be 26 or less.\n')
            exit(1)
        generate_hypercube(args.dimensions, args.side_length, args.fill_ratio)
    elif args.command == 'labyrinth':
        generate_labyrinth(args.width, args.height, args.cycle_chance, args.verbose)


if __name__ == '__main__':
    main()
