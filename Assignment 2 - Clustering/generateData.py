import os
import sys
import argparse
import numpy as np
from collections import defaultdict
from matplotlib import pyplot as plt
from sklearn import datasets, cluster

Dataset, Dataset_name = None, None

def getParser():
    parser = argparse.ArgumentParser(
        description='Generate dataset and check the clusters')
    parser.add_argument('numSamples', type=int,
                        help='Number of data points')
    parser.add_argument('clusters', type=int,
                        help='Number of clusters')
    parser.add_argument('numTries', type=int,
                        help='Number of different random seeds')
    return parser


def saveData(event):
    if event.key == 'w':
        np.savetxt(Dataset_name + '.txt', Dataset, delimiter=' ')
    plt.close(event.canvas.figure)


def clusterPoints(X, n, mode='kmeans'):
    if mode == 'kmeans':
        pred = cluster.KMeans(n_clusters=n).fit_predict(X)
    elif mode == 'dbscan':
        pred = cluster.DBSCAN(eps=n).fit_predict(X)
    elif mode == 'optics':
        pred = cluster.OPTICS(n_jobs=n).fit_predict(X)

    clusters = defaultdict(list)
    for i in xrange(len(pred)):
        clusters[pred[i]].append(X[i])
    return clusters


def plotClusters(cl, title):
    for (i, points) in cl.iteritems():
        x, y = zip(*points)
        plt.plot(x, y, 'o', markersize=0.5)
        plt.title('{} clustering'.format(title))
    plt.show()


def generate(numSamples, numClusters, seed):
    std_dev = [0.25 + 0.25 * i * i for i in xrange(1, numClusters + 1)]
    X, y = datasets.make_blobs(
        n_samples=numSamples, centers=numClusters, cluster_std=std_dev, random_state=seed)

    cid = plt.gcf().canvas.mpl_connect('key_press_event', saveData)
    global Dataset, Dataset_name
    Dataset = X
    Dataset_name = '{}-{}-{}'.format(numSamples, numClusters, seed)

    kmeansClusters = clusterPoints(X, numClusters, 'kmeans')
    plotClusters(kmeansClusters, 'kmeans')
    dbscanClusters = clusterPoints(X, 0.04, 'dbscan')
    plotClusters(dbscanClusters, 'dbscan')
    # opticsClusters = clusterPoints(X, -1, 'optics')
    # plotClusters(opticsClusters, 'optics')


def Run(args):
    for i in xrange(args['numTries']):
        generate(args['numSamples'], args['clusters'], i)


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
