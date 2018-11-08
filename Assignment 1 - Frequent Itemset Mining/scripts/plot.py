import os
import sys
import argparse
from timeit import timeit
from matplotlib import pyplot as plt


def getParser():
    parser = argparse.ArgumentParser(
        description='Compare the times of A Priori and FP tree')
    parser.add_argument('inputFile', help='Database of transactions')
    parser.add_argument('--supports', nargs='+', type=int,
                        required=True, help='Support thresholds to time for')
    return parser


def getTimes(input, supports=[1, 5, 10, 25, 50, 90]):
    apTimes, fpTimes = [], []
    for support in supports:
        apTimes.append(timeit(stmt="os.system('./fpm {} {} {} output{}')".format(
            input, support, '-apriori', '-apriori'), setup="import os", number=1))
        fpTimes.append(timeit(stmt="os.system('./fpm {} {} {} output{}')".format(
            input, support, '-fptree', '-fptree'), setup="import os", number=1))
    return apTimes, fpTimes


def plot(apTimes, fpTimes, supports, scale='normal'):
    if scale == 'log':
        plt.yscale('log')
    plt.plot(supports, apTimes, label='A Priori')
    plt.plot(supports, fpTimes, label='FP-Tree')
    plt.title('Execution time vs support threshold for a-priori and fp-tree')
    plt.xlabel('Support threshold(%)')
    plt.ylabel('Time taken(s)')
    plt.legend(loc='upper right')


def Run(args):
    apTimes, fpTimes = getTimes(args['inputFile'], args['supports'])
    print 'A priori', apTimes
    print 'FP-tree', fpTimes
    plot(apTimes, fpTimes, args['supports'])
    plt.show()
    plot(apTimes, fpTimes, args['supports'], 'log')
    plt.show()


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
