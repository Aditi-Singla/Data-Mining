import os
import sys
import sets
import argparse


def getParser():
    parser = argparse.ArgumentParser(
        description='Check the validity of the output(s)')
    parser.add_argument('inputFile', help='Database of transactions')
    parser.add_argument(
        'outputFile1', help='Output file 1 containing frequent item sets')
    parser.add_argument(
        'outputFile2', help='Output file 2 containing frequent item sets')
    parser.add_argument(
        'suppThold', help='Support threshold as percentage', type=float)
    return parser


def readOutput(outFile):
    with open(outFile) as outF:
        return map(lambda x: set(map(int, x.strip().split())), outF.readlines())


def checkSets(inFile, frequentItemsets):
    numTransactions = 0
    frequencies = [0 for itemset in frequentItemsets]
    with open(inFile) as inF:
        for line in inF:
            tempset = set(map(int, line.strip().split()))
            numTransactions += 1
            for i in xrange(len(frequentItemsets)):
                if frequentItemsets[i].issubset(tempset):
                    frequencies[i] += 1
    return frequencies, numTransactions


def checkSupport(frequencies, supp, numTransactions):
    for i in xrange(len(frequencies)):
        if frequencies[i] < (supp * 100.0) / numTransactions:
            print 'The itemset no. {} is infrequent'.format(i)
    print 'All itemsets reported are frequent'


def Run(args):
    # check output 1
    frequentItemsets1 = readOutput(args['outputFile1'])
    frequencies, numTransactions = checkSets(
        args['inputFile'], frequentItemsets1)
    checkSupport(frequencies, args['suppThold'], numTransactions)

    # check output 2, if any
    if (len(args['outputFile2'])):
        frequentItemsets2 = readOutput(args['outputFile2'])
        frequencies, numTransactions = checkSets(
            args['inputFile'], frequentItemsets2)
        checkSupport(frequencies, args['suppThold'], numTransactions)

        # check equality of sets
        for frequentItemset in frequentItemsets1:
            if frequentItemset not in frequentItemsets2:
                print '{} present in output 1, but missing in output 2'.format(
                    frequentItemset)

        for frequentItemset in frequentItemsets2:
            if frequentItemset not in frequentItemsets1:
                print '{} present in output 2, but missing in output 1'.format(
                    frequentItemset)


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
