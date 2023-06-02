#! /usr/bin/env python3

import argparse
import random
import sys

REPORT_IDS = []
REPORT_MAX = 0

QUERY_ID = 0

def gen_query_id():
    global QUERY_ID
    QUERY_ID += 1
    return QUERY_ID

def gen_range(mu, sigma):
    base  = gen_value(mu, sigma)
    error = random.uniform(0.05, 0.25)
    delta = base * error

    lo = max(0, base - delta)
    hi = max(0, base + delta)
    return '%.3f-%.3f' % (lo, hi)

def gen_report_id():
    global REPORT_MAX
    REPORT_MAX += 1

    REPORT_IDS.append(REPORT_MAX)
    return REPORT_MAX

def pop_report_id():
    i = random.randrange(len(REPORT_IDS))
    temp = REPORT_IDS[i]

    REPORT_IDS[i] = REPORT_IDS[-1]
    REPORT_IDS.pop()
    return temp

def gen_value(mu, sigma):
    return max(0.0, random.gauss(mu, sigma))


def print_report(population):
    age, height, weight = random.choice(population)
    print('report\t%d\t%s\t%s\t%s' % (
        gen_report_id(),
        gen_range(*age),
        gen_range(*height),
        gen_range(*weight)
    ))

def print_solved(report_id):
    print('solved\t%d' % report_id)

def print_suspect(population):
    age, height, weight = random.choice(population)
    print('suspect\t%d\t%.3f\t%.3f\t%.3f' % (
        gen_query_id(),
        gen_value(*age),
        gen_value(*height),
        gen_value(*weight)
    ))


HUMANS = [
    # Data taken from a random paper about the trachea...
    # https://www.researchgate.net/publication/257769120 ...
    ((43, 15), (171, 10), (75, 15)), # males
    ((38, 14), (150, 11), (62, 11))  # females
]

def print_reports(n):
    for _ in range(n):
        print_report(HUMANS)

def print_solves(n):
    report_ids = list(range(1, n+1))
    random.shuffle(report_ids)

    for rid in report_ids:
        print_solved(rid)

def print_suspects(n):
    for _ in range(n):
        print_suspect(HUMANS)


TYPES = [
    'reports',
    'suspects',
    'solves'
]


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--seed', type=int, help='random seed')

    parser.add_argument('n',    type=int,      help='number of lines to generate')
    parser.add_argument('type', choices=TYPES, help='type of lines to generate')

    args = parser.parse_args()

    if args.seed is None:
        args.seed = random.randrange(sys.maxsize)
    random.seed(args.seed)
    sys.stderr.write('Random seed: %d\n' % args.seed)

    if args.type == 'reports':
        print_reports(args.n)
    elif args.type == 'solves':
        print_solves(args.n)
    elif args.type == 'suspects':
        print_suspects(args.n)
    else:
        sys.stderr.write('Unknown line type: "%s"' % args.type)


if __name__ == '__main__':
    main()
