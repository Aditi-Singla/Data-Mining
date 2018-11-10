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
    parser.add_argument('test', help='Testing database of graphs')
    return parser


def runFSG(convFile, fsgOutputFile):
    numGraphs = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(convFile), shell=True).strip())
    os.system('./libraries/gSpan -f {} -s 0.1 -i -o'.format(convFile))
    numFeatures = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(fsgOutputFile), shell=True).strip())
    return numGraphs, numFeatures


def convertTrain(fsgOutputFile, labelFile, numGraphs, numFeatures):
    X = np.zeros((numGraphs, numFeatures))
    with open(fsgOutputFile, 'r') as fsg:
        i = 0
        for line in fsg:
            if line.startswith('x'):
                for graph in map(int, line[2:].strip().split()):
                    X[graph][i] = 1
                i += 1
            continue
    with open(labelFile, 'r') as lf:
        Y = map(lambda x: int(x.strip()), lf.readlines())
    return X, Y


def Run(args):
    trainParts = args['train'].split('.')
    convFile = '{}_converted.{}'.format(trainParts[0], trainParts[1])
    fsgOutputFile = '{}.fp'.format(convFile)
    labelFile = '{}_labels.{}'.format(trainParts[0], trainParts[1])

    numGraphs, numFeatures = runFSG(convFile, fsgOutputFile)
    X_train, Y_train = convertTrain(
        fsgOutputFile, labelFile, numGraphs, numFeatures)

    # TODO - look into labelling test set


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
