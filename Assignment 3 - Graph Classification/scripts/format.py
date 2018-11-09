import os
import sys
import argparse
from timeit import timeit
from matplotlib import pyplot as plt


def getParser():
    parser = argparse.ArgumentParser(
        description='Convert the input graph database into the format required by gSpan, FSG and Gaston')
    parser.add_argument('inFile', help='Input Database of graphs')
    parser.add_argument('--outFile', default="",
                        help='Output Database of graphs')
    return parser


def convert(inputFile, outputFile):
    with open(inputFile, 'r') as inFile:
        with open(outputFile, 'w+') as outFile:
            lines = inFile.readlines()
            i, labels, maxlab = 0, {}, 0
            while (i < len(lines)):
                outFile.write('t # {}'.format(lines[i][1:]))
                V = int(lines[i + 1].strip())
                i += 2
                for j in xrange(V):
                    label = lines[i + j]
                    if not(label in labels):
                        labels[label] = maxlab
                        maxlab += 1
                    label = labels[label]
                    outFile.write('v {} {}\n'.format(j, label))
                i += V
                E = int(lines[i].strip())
                i += 1
                for j in xrange(E):
                    outFile.write('e {}'.format(lines[i + j]))
                i += E


def Run(args):
    if args['outFile'] == "":
        inFileParts = args['inFile'].split('/')[-1].split('.')
        args['outFile'] = '{}_converted.{}'.format(
            inFileParts[0], inFileParts[1])
    convert(args['inFile'], args['outFile'])


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
