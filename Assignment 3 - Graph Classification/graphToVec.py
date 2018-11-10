import os
import sys
import argparse
import subprocess
import numpy as np
from timeit import timeit
from matplotlib import pyplot as plt


def getParser():
    parser = argparse.ArgumentParser(
        description='Convert graphs into feature vectors')
    parser.add_argument('train', help='Training database of graphs')
    parser.add_argument('active', help='Active set of graphs')
    parser.add_argument('inactive', help='Inactive set of graphs')
    parser.add_argument('test', help='Testing database of graphs')
    return parser


def runFSG(input):
    inputParts = input.split('.')
    input = '{}_converted.{}'.format(inputParts[0], inputParts[1])
    numGraphs = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(input), shell=True).strip())

    os.system('./libraries/gSpan -f {} -s 10 -i -o')
    outFile = '{}_converted.fp'.format(inputParts[0])
    numFeatures = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(outFile), shell=True).strip())
    return outFile, numGraphs, numFeatures


def getFeatures(FSGFile, numGraphs, numFeatures):
    X = np.zeroes((numGraphs, numFeatures))
    with open(FSGFile, 'r') as fsg:
        i = 0
        for line in fsg:
            if line.startswith('x'):
                for graph in map(int, line[2:].strip().split()):
                    X[graph][i] = 1
                i += 1
            continue
    return X


def Run(args):
    FSGFile, numGraphs, numFeatures = runFSG(args['train'])
    X = getFeatures(FSGFile, numGraphs, numFeatures)
    # TODO - look into labelling test set


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
