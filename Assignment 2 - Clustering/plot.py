import os
import sys
import argparse
from matplotlib import pyplot as plt
from collections import defaultdict


def getParser():
    parser = argparse.ArgumentParser(
        description='Plot the points and view clusters')
    parser.add_argument('--input', help='Input database of points')
    parser.add_argument('--clusters', nargs='*',
                        help='Output files containing clusters')
    parser.add_argument('--reachability',
                        help='Output file containing reachability information')
    return parser


def readData(inputFile):
    with open(inputFile) as inFile:
        pts = map(lambda x: map(float, x.strip().split()), inFile.readlines())
        return zip(*pts)


def readClusterData(inputFile):
    with open(inputFile) as inFile:
        lines = map(lambda x: x.strip(), inFile.readlines())
        clusters = defaultdict(list)
        currCluster = 0
        for line in lines:
            if line.startswith('#'):
                currCluster = int(line[1:])
            else:
                clusters[currCluster].append(int(line))
        return clusters


def plot(X, Y, title, xlabel, ylabel, typ='-'):
    plt.plot(X, Y, typ)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)


def plotClusters(clusters, X, Y):
    for (clusterID, pointIDs) in clusters.iteritems():
        x, y = [], []
        for pointID in pointIDs:
            x.append(X[pointID])
            y.append(Y[pointID])
        plt.plot(x, y, 'o', label='Cluster {}'.format(clusterID), markersize=0.5)
    plt.legend(loc='upper right')


def Run(args):
    attributes = readData(args['input'])
    if len(attributes) == 2:
        X, Y = attributes[0], attributes[1]
        # plot(X, Y, 'Data points', '', '', 'o')
        # plt.show()
        if args['clusters']:
            for clusterFile in args['clusters']:
                clusters = readClusterData(clusterFile)
                plotClusters(clusters, X, Y)
                plt.show()

    if args['reachability']:
        reachabilityInfo = readData(args['reachability'])
        plot(reachabilityInfo[0], reachabilityInfo[1],
             'Reachability Distances for points', 'Point ID', 'Reachability Distances')
        plt.show()


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
