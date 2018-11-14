import os
import sys
import argparse
import subprocess
import numpy as np
import networkx as nx
from collections import defaultdict
from sklearn.svm import LinearSVC
from sklearn.preprocessing import normalize
from sklearn.preprocessing import StandardScaler
from networkx.algorithms import isomorphism as iso

ACTIVE_LABEL = 1
INACTIVE_LABEL = 2


def getParser():
    parser = argparse.ArgumentParser(
        description='Convert graphs into feature vectors')
    parser.add_argument('trainData', help='Training database of graphs')
    parser.add_argument('trainLabels', help='Labels of training graphs')
    parser.add_argument('testData', help='Testing database of graphs')
    parser.add_argument('testLabels', help='Labels of test graphs')
    parser.add_argument('--support', default=0.2, type=float,
                        help='Support threshold for gSpan')
    return parser


def runFSG(convFile, fsgOutputFile, support):
    os.system('./libraries/gBolt -input_file {} -output_file {} -support {} -pattern'.format(
        convFile, fsgOutputFile[:-3], support))


def convGraphStr(graphStr):
    graphList = graphStr.strip().split('\n')
    vertices, edges = [], []
    for line in graphList:
        if line.startswith('v'):
            vertices.append(line[2:].split())
        else:
            edges.append(line[2:].split())
    graph = nx.Graph()
    graph.add_nodes_from(map(lambda x: (int(x[0]), {'label': x[1]}), vertices))
    graph.add_edges_from(
        map(lambda x: (int(x[0]), int(x[1]), {'label': x[2]}), edges))
    return graph


def getTrainVectors(fsgOutputFile, labelFile, numGraphs, numFeatures):
    X = np.zeros((numGraphs, numFeatures))
    FSG = []
    with open(fsgOutputFile, 'r') as fsgF:
        i = 0
        currGraphStr = ""
        for line in fsgF:
            if line.startswith('x'):
                for graph in map(int, line[3:].strip().split()):
                    if graph >= 0 and graph < numGraphs:
                        X[graph][i] = 1
                i += 1
                FSG.append(convGraphStr(currGraphStr))
            elif line.startswith('t'):
                currGraphStr = ""
                continue
            else:
                currGraphStr += line

    with open(labelFile, 'r') as lf:
        Y = list(map(lambda x: int(x.strip()), lf.readlines()))
    return X, Y, FSG


def getTestGraphs(testConvFile, labelFile):
    testGraphs = []
    with open(testConvFile, 'r') as testConvF:
        i = 0
        currGraphStr = ""
        for line in testConvF:
            if line.startswith('t'):
                if currGraphStr != "":
                    testGraphs.append(convGraphStr(currGraphStr))
                    i += 1
                currGraphStr = ""
            else:
                currGraphStr += line
        testGraphs.append(convGraphStr(currGraphStr))

    with open(labelFile, 'r') as lf:
        Y = list(map(lambda x: int(x.strip()), lf.readlines()))
    return testGraphs, Y


def getTestVectors(testGraphs, FSG):
    X = np.zeros((len(testGraphs), len(FSG)))
    for i in range(len(testGraphs)):
        for j in range(len(FSG)):
            GM = iso.GraphMatcher(
                testGraphs[i], FSG[j], node_match=lambda x, y: x['label'] == y['label'], edge_match=lambda x, y: x['label'] == y['label'])
            if GM.subgraph_is_isomorphic():
                X[i][j] = 1
    return X


def getFrequencyMaps(X_train, Y_train):
    numActive, numInactive = 0.0, 0.0
    for i in Y_train:
        if i == ACTIVE_LABEL:
            numActive += 1
        else:
            numInactive += 1

    numActive = sum([1 for y in Y_train if y == 1])
    numInactive = len(X_train) - numActive
    featFreqActive, featFreqInactive = defaultdict(int), defaultdict(int)
    for i in range(len(X_train)):
        for j in range(len(X_train[i])):
            if X_train[i][j] == 1:
                if Y_train[i] == ACTIVE_LABEL:
                    featFreqActive[i] += (1.0 / numActive)
                else:
                    featFreqInactive[i] += (1.0 / numInactive)
    return featFreqActive, featFreqInactive


def getTopKDiscriminativeFeatures(numFeatures, featFreqActive, featFreqInactive, k=100):
    diffList = []
    for i in range(numFeatures):
        diffList.append((i, abs(featFreqActive[i] - featFreqInactive[i])))
    cols, freq = zip(*(sorted(diffList, key=lambda x: x[1])[-k:]))
    return cols


def idfTransform(X_train, featFreqActive, featFreqInactive):
    numFeatures = len(X_train[0])
    for i in range(len(X_train)):
        for j in range(numFeatures):
            if X_train[i][j] == 1:
                X_train[i][j] = featFreqActive[j] - featFreqInactive[j]
    X_train = normalize(X_train, axis=1, norm='l2')
    scaler = StandardScaler().fit(X_train)
    return X_train, scaler


def libSVMformat(X, Y, out_file):
    with open(out_file, 'w') as out:
        for i in range(len(X)):
            out.write(str(Y[i]))
            for j in range(1, len(X[i]) + 1):
                if X[i][j - 1] != 0:
                    out.write(str(' '))
                    out.write(str(j) + ':' + str(X[i][j - 1]))
            if (i < len(X) - 1):
                out.write('\n')


def RunClassify(k, support, numTrainGraphs, args):
    print('Support : {} Features : {}'.format(support, k))

    fsgOutputFile = '{}.fp.t0'.format(args['trainData'])
    runFSG(args['trainData'], fsgOutputFile, support)
    numFeatures = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(fsgOutputFile), shell=True).strip())

    X_train, Y_train, FSG = getTrainVectors(
        fsgOutputFile, args['trainLabels'], numTrainGraphs, numFeatures)

    featFreqActive, featFreqInactive = getFrequencyMaps(X_train, Y_train)
    cols = getTopKDiscriminativeFeatures(
        numFeatures, featFreqActive, featFreqInactive, k)
    X_train, FSG = X_train[:, cols], np.array(FSG).take(cols)

    testGraphs, Y_test = getTestGraphs(args['testData'], args['testLabels'])
    X_test = getTestVectors(testGraphs, FSG)

    acc = LinearSVC(max_iter=10000).fit(X_train, Y_train).score(X_test, Y_test)

    return acc, X_train, Y_train, X_test, Y_test


def Run(args):
    numTrainGraphs = int(subprocess.check_output(
        'cat {} | wc -l'.format(args['trainLabels']), shell=True).strip())

    mAcc, mX_train, mY_train, mX_test, mY_test = 0, None, None, None, None
    for k in range(50, 200, 50):
        supp = int(args['support'] * 100)
        for s in range(supp, supp + 1):
            acc, X_train, Y_train, X_test, Y_test = RunClassify(
                k, s / 100.0, numTrainGraphs, args)
            if acc > mAcc:
                mAcc, mX_train, mY_train, mX_test, mY_test = acc, X_train, Y_train, X_test, Y_test

    libSVMformat(mX_train, mY_train, 'train.txt')
    libSVMformat(mX_test, mY_test, 'test.txt')


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
