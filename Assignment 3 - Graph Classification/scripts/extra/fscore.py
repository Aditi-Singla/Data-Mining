import os
import sys
import argparse
import numpy as np
from sklearn.metrics import f1_score


def getParser():
    parser = argparse.ArgumentParser(
        description='Calculate the f-score')
    parser.add_argument('actual', help='Actual labels')
    parser.add_argument('predicted', help='Predicted labels')
    return parser


def fScore(actualLabelFile, predictedLabelFile):
    with open(actualLabelFile, 'r') as alf:
        ay = list(map(lambda x: int(x.strip()), alf.readlines()))
    with open(predictedLabelFile, 'r') as plf:
        py = list(map(lambda x: int(x.strip()), plf.readlines()))
    return f1_score(ay, py)


def Run(args):
    actualLabelFile = args['actual']
    predictedLabelFile = args['predicted']
    fscore = fScore(actualLabelFile, predictedLabelFile)
    print("F-Score : {}".format(fscore))


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
