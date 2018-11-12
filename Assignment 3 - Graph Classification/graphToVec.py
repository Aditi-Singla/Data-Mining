import os
import sys
import argparse
import subprocess
import numpy as np
import networkx as nx
from collections import defaultdict
from sklearn.preprocessing import normalize
from sklearn import feature_selection as select
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
    numTrainGraphs = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(convFile), shell=True).strip())
    os.system('./libraries/gSpan -f {} -s {} -i -o'.format(convFile, support))
    numFeatures = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(fsgOutputFile), shell=True).strip())
    return numTrainGraphs, numFeatures


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
                for graph in map(int, line[2:].strip().split()):
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


def getTestVectors(testConvFile, labelFile, FSG):
    numGraphs = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(testConvFile), shell=True).strip())
    X = np.zeros((numGraphs, len(FSG)))
    with open(testConvFile, 'r') as testConvF:
        i = 0
        currGraphStr = ""
        for line in testConvF:
            if line.startswith('t'):
                if currGraphStr != "":
                    testGraph = convGraphStr(currGraphStr)
                    for j in range(len(FSG)):
                        GM = iso.GraphMatcher(
                            testGraph, FSG[j], node_match=lambda x, y: x['label'] == y['label'], edge_match=lambda x, y: x['label'] == y['label'])
                        if GM.subgraph_is_isomorphic():
                            X[i][j] = 1
                    i += 1
                currGraphStr = ""
            else:
                currGraphStr += line
    with open(labelFile, 'r') as lf:
        Y = list(map(lambda x: int(x.strip()), lf.readlines()))
    return X, Y


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
    cols, freq = zip(*(sorted(diffList, key=lambda x: -x[1])[:k]))
    # return select.SelectKBest(select.mutual_info_classif, k=k).fit(X_train, Y_train).get_support()
    return cols


def idfTransform(X_train, featFreqActive, featFreqInactive):
    numFeatures = len(X_train[0])
    for i in range(len(X_train)):
        for j in range(numFeatures):
            if X_train[i][j] == 1 and (featFreqActive[j] + featFreqInactive[j]):
                # X_train = 0
                # if featFreqActive[j]:
                #     X_train += 1.0 / featFreqActive[j]
                # if featFreqInactive[j]:
                #     X_train -= 1.0 / featFreqInactive[j]
                X_train[i][j] = 1.0 / (featFreqActive[j] + featFreqInactive[j])
            else:
                X_train[i][j] = 0
    return normalize(X_train, axis=1, norm='l2')
    

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


def Run(args):
    fsgOutputFile = '{}.fp'.format(args['trainData'])
    support = args['support']
    numTrainGraphs, numFeatures = runFSG(
        args['trainData'], fsgOutputFile, support)
    X_train, Y_train, FSG = getTrainVectors(
        fsgOutputFile, args['trainLabels'], numTrainGraphs, numFeatures)

    featFreqActive, featFreqInactive = getFrequencyMaps(X_train, Y_train)
    cols = getTopKDiscriminativeFeatures(numFeatures, featFreqActive, featFreqInactive, 100)
    X_train, FSG = X_train[:, cols], np.array(FSG).take(cols)
    # X_train = idfTransform(X_train, featFreqActive, featFreqInactive)
    
    X_test, Y_test = getTestVectors(args['testData'], args['testLabels'], FSG)
    # X_test = idfTransform(X_test, featFreqActive, featFreqInactive)

    libSVMformat(X_train, Y_train, 'train.txt')
    libSVMformat(X_test, Y_test, 'test.txt')


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
