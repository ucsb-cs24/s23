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

def gen_range(mean, cv):
    base  = gen_value(mean, cv)
    error = random.uniform(0.00, 0.075)
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

def gen_value(mean, cv):
    # return max(0.0, random.gauss(mean, cv*mean))
    delta = 2 * mean * cv
    return random.uniform(max(0, mean - delta), mean + delta)


def print_report(population):
    age, height, weight = random.choice(population)
    print('report\t%d\t%s\t%s\t%s' % (
        gen_report_id(),
        gen_range(*age),
        gen_range(*height),
        gen_range(*weight)
    ))

def print_solved():
    print('solved\t%d' % pop_report_id())

def print_suspect(population):
    age, height, weight = random.choice(population)
    print('suspect\t%d\t%.3f\t%.3f\t%.3f' % (
        gen_query_id(),
        gen_value(*age),
        gen_value(*height),
        gen_value(*weight)
    ))


def print_mixed(population, n, ceiling, query_chance):
    for _ in range(n):
        if ceiling and random.randrange(ceiling) < len(REPORT_IDS):
            print_solved()
        else:
            print_report(population)
        if random.random() < query_chance:
            print_suspect(population)


HUMANS = [
    # Data taken from a random paper about the trachea...
    # https://www.researchgate.net/publication/257769120
    ((43, 0.30), (171, 0.06), (75, 0.20)), # males
    ((38, 0.30), (150, 0.07), (62, 0.18))  # females
]

FANTASY = [
    # Add some fantasy races for data diversity...
    (( 10, 0.20), ( 12, 0.17), (   1, 0.15)), # pixies
    ((230, 0.25), ( 50, 0.12), (   6, 0.25)), # brownies
    (( 20, 0.25), ( 80, 0.25), (  20, 0.29)), # goblins
    ((100, 0.20), (100, 0.10), (  48, 0.12)), # dwarves
    (( 50, 0.20), (160, 0.20), (  70, 0.20)), # humans
    (( 50, 0.25), (175, 0.33), ( 100, 0.27)), # orcs
    ((700, 0.33), (180, 0.14), (  60, 0.14)), # elves
    ((300, 0.40), (250, 0.20), ( 450, 0.22)), # trolls
    ((150, 0.30), (600, 0.23), (1000, 0.22)), # giants
]


def coldcase(reports, queries):
    """Lots of queries against a pre-built database."""
    for _ in range(reports):
        print_report(FANTASY)
    for _ in range(queries):
        print_suspect(FANTASY)

def density(n, ceiling, query_chance):
    """All suspects are about the same weight."""
    population = [((50, 0.30), (160, 0.30), (60, 0.02))]
    print_mixed(population, n, ceiling, query_chance)

def evolution(n, ceiling, query_chance):
    """Suspects get older, taller, and heavier as time goes on."""
    for i in range(n):
        if ceiling and random.randrange(ceiling) < len(REPORT_IDS):
            print_solved()
            continue

        population = ((
            ( 20 +  80 * i/n, 0.10),
            (100 + 100 * i/n, 0.10),
            ( 40 +  40 * i/n, 0.10)
        ),)

        print_report(population)
        if random.random() < query_chance:
            print_suspect(population)

def humans(n, ceiling, query_chance):
    print_mixed(HUMANS, n, ceiling, query_chance)

def stretch(n, ceiling, query_chance):
    """Suspects are all about the same height."""
    population = [((50, 0.30), (180, 0.02), (70, 0.30))]
    print_mixed(population, n, ceiling, query_chance)

def timeless(n, ceiling, query_chance):
    """Suspects are all about the same age."""
    population = [((100, 0.02), (140, 0.30), (65, 0.30))]
    print_mixed(population, n, ceiling, query_chance)

def turnover(n, ceiling, query_chance):
    """Cases come in quickly and get solved quickly."""
    print_mixed(FANTASY, n, ceiling, query_chance)


TESTS = [
    'coldcase',
    'density',
    'evolution',
    'humans',
    'stretch',
    'timeless',
    'turnover'
]

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-s', '--seed', type=int, help='random seed')
    parser.add_argument('testcase', choices=TESTS)
    args = parser.parse_args()

    if args.seed is None:
        args.seed = random.randrange(sys.maxsize)
    random.seed(args.seed)
    sys.stderr.write('Random seed: %d\n' % args.seed)

    if args.testcase == 'coldcase':
        coldcase(20000, 100000)
    if args.testcase == 'density':
        density(100000, None, 0.15)
    if args.testcase == 'evolution':
        evolution(200000, 200000, 0.15)
    if args.testcase == 'humans':
        humans(1000, 2000, 0.02)
    if args.testcase == 'stretch':
        stretch(100000, None, 0.15)
    if args.testcase == 'timeless':
        timeless(100000, None, 0.15)
    if args.testcase == 'turnover':
        turnover(1000000, 50000, 0.05)


if __name__ == '__main__':
    main()
