import os
import sys
import argparse
import subprocess
import numpy as np
import networkx as nx
from timeit import timeit
from matplotlib import pyplot as plt
from networkx.algorithms import isomorphism


def getParser():
    parser = argparse.ArgumentParser(
        description='Convert graphs into feature vectors')
    parser.add_argument('train', help='Training database of graphs')
    parser.add_argument('test', help='Testing database of graphs')
    return parser


def runFSG(convFile, fsgOutputFile):
    numGraphs = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(convFile), shell=True).strip())
    os.system('./libraries/gSpan -f {} -s 0.7 -i -o'.format(convFile))
    numFeatures = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(fsgOutputFile), shell=True).strip())
    return numGraphs, numFeatures


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


def readFSGFile(fsgOutputFile, labelFile, numGraphs, numFeatures):
    X = np.zeros((numGraphs, numFeatures))
    FSG = []
    with open(fsgOutputFile, 'r') as fsg:
        i = 0
        currGraphStr = ""
        for line in fsg:
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


def Run(args):
    trainParts = args['train'].split('.')
    convFile = '{}_converted.{}'.format(trainParts[0], trainParts[1])
    fsgOutputFile = '{}.fp'.format(convFile)
    labelFile = '{}_labels.{}'.format(trainParts[0], trainParts[1])

    numGraphs, numFeatures = runFSG(convFile, fsgOutputFile)
    X_train, Y_train, FSG = readFSGFile(
        fsgOutputFile, labelFile, numGraphs, numFeatures)

    # TODO - look into labelling test set
    GM = isomorphism.GraphMatcher(FSG[5], FSG[2])
    print GM.subgraph_is_isomorphic()


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
