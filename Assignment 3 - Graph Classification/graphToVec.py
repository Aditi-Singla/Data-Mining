import os
import sys
import argparse
import subprocess
import numpy as np
import networkx as nx
from networkx.algorithms import isomorphism


def getParser():
    parser = argparse.ArgumentParser(
        description='Convert graphs into feature vectors')
    parser.add_argument('train', help='Training database of graphs')
    parser.add_argument('test', help='Testing database of graphs')
    return parser


def runFSG(convFile, fsgOutputFile):
    numTrainGraphs = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(convFile), shell=True).strip())
    os.system('./libraries/gSpan -f {} -s 0.1 -i -o'.format(convFile))
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
    graph.add_edges_from(map(lambda x: (int(x[0]), int(x[1]), {'label': x[2]}), edges))
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
        Y = map(lambda x: int(x.strip()), lf.readlines())
    return X, Y, FSG


def getTestVectors(testConvFile, FSG):
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
                    for j in xrange(len(FSG)):
                        GM = isomorphism.GraphMatcher(testGraph, FSG[j])
                        if GM.subgraph_is_isomorphic():
                            X[i][j] = 1
                    i += 1
                currGraphStr = ""
            else:
                currGraphStr += line
    return X


def Run(args):
    trainParts = args['train'].split('.')
    convFile = '{}_converted.{}'.format(trainParts[0], trainParts[1])
    fsgOutputFile = '{}.fp'.format(convFile)
    labelFile = '{}_labels.{}'.format(trainParts[0], trainParts[1])

    numTrainGraphs, numFeatures = runFSG(convFile, fsgOutputFile)
    X_train, Y_train, FSG = getTrainVectors(
        fsgOutputFile, labelFile, numTrainGraphs, numFeatures)

    testParts = args['test'].split('.')
    trainConvFile = '{}_converted.{}'.format(testParts[0], testParts[1])
    X_test = getTestVectors(trainConvFile, FSG)
   
    from collections import defaultdict
    d = defaultdict(int)
    for row in X_test:
        d[sum(row)] += 1
    print d

    # GM = isomorphism.GraphMatcher(FSG[5], FSG[2])
    # print GM.subgraph_is_isomorphic()


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
