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
    parser.add_argument('--active', default="",
                        help='Active graph IDs')
    parser.add_argument('--inactive', default="",
                        help='Inactive graph IDs')
    return parser


def getLabels(activeFile, inactiveFile):
    activeIDs, inactiveIDs = set(), set()
    if activeFile != "" and inactiveFile != "":
        with open(activeFile, 'r') as actFile:
            activeIDs = set(map(lambda x: x.strip(), actFile.readlines()))
        with open(inactiveFile, 'r') as inactFile:
            inactiveIDs = set(map(lambda x: x.strip(), inactFile.readlines()))
    return activeIDs, inactiveIDs


def convert(inputFile, outputFile, activeIDs, inactiveIDs):
    chkID = False
    if len(activeIDs) > 0 and len(inactiveIDs) > 0:
        chkID = True
    with open(inputFile, 'r') as inFile:
        with open(outputFile, 'w+') as outFile:
            lines = inFile.readlines()
            i, labels, maxlab = 0, {}, 0
            while (i < len(lines)):
                graphID = lines[i][1:].strip()
                if chkID and graphID not in activeIDs and graphID not in inactiveIDs:
                    i += 1
                    while i < len(lines) and not(lines[i].startswith('#')):
                        i += 1
                else:
                    outFile.write('t # {}\n'.format(graphID))
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
    activeIDs, inactiveIDs = getLabels(args['active'], args['inactive'])
    convert(args['inFile'], args['outFile'], activeIDs, inactiveIDs)


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
