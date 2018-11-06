import os
import sys
import argparse
from timeit import timeit
from matplotlib import pyplot as plt


def getParser():
    parser = argparse.ArgumentParser(
        description='Compare the running times of gSpan, FSG and Gaston')
    parser.add_argument('inputFile', help='Database of graphs')
    parser.add_argument('--supports', nargs='+', type=int,
                        required=True, help='Support thresholds to time for')
    return parser


def getTimes(input, supports=[5, 10, 25, 50, 95]):
    gSpanTimes, FSGTimes, GastonTimes = [], [], []
    for support in supports:
        # gSpanTimes.append(timeit(stmt="os.system('./graph {} {} {} output{}')".format(
        #     input, support, '-gspan', '-gspan'), setup="import os", number=1))
        # FSGTimes.append(timeit(stmt="os.system('./graph {} {} {} output{}')".format(
        #     input, support, '-fsg', '-fsg'), setup="import os", number=1))
        # GastonTimes.append(timeit(stmt="os.system('./graph {} {} {} output{}')".format(
        #     input, support, '-gaston', '-gaston'), setup="import os", number=1))
    return gSpanTimes, FSGTimes, GastonTimes


def plot(gSpanTimes, FSGTimes, GastonTimes, supports, scale='normal'):
    if scale == 'log':
        plt.yscale('log')
    plt.plot(supports, gSpanTimes, label='gSpan')
    plt.plot(supports, FSGTimes, label='FSG')
    plt.plot(supports, GastonTimes, label='Gaston')
    plt.title('Execution time vs support threshold for gSpan, FSG and Gaston')
    plt.xlabel('Support threshold(%)')
    plt.ylabel('Time taken(s)')
    plt.legend(loc='upper right')


def Run(args):
    gSpanTimes, FSGTimes, GastonTimes = getTimes(args['inputFile'], args['supports'])
    plot(gSpanTimes, FSGTimes, GastonTimes, args['supports'])
    plt.show()
    plot(gSpanTimes, FSGTimes, GastonTimes, args['supports'], 'log')
    plt.show()


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
