import os
import sys
import argparse


def getParser():
    parser = argparse.ArgumentParser(
        description='Convert the input graph database into the format required by gSpan, FSG and Gaston')
    parser.add_argument('inFile', help='Input Database of graphs')
    parser.add_argument('outFile', help='Output Database of graphs')
    parser.add_argument('--labels', default="",
                        help='Output Labels of graphs')
    parser.add_argument('--active', default="",
                        help='Active graph IDs')
    parser.add_argument('--inactive', default="",
                        help='Inactive graph IDs')
    parser.add_argument('--filter', action='store_true',
                        help='Filter out unlabelled graph')
    return parser


def getLabels(activeFile, inactiveFile):
    activeIDs, inactiveIDs = set(), set()
    if activeFile != "" and inactiveFile != "":
        with open(activeFile, 'r') as actFile:
            activeIDs = set(map(lambda x: x.strip(), actFile.readlines()))
        with open(inactiveFile, 'r') as inactFile:
            inactiveIDs = set(map(lambda x: x.strip(), inactFile.readlines()))
    return activeIDs, inactiveIDs


def convert(inFile, outFile, labelFile, activeIDs, inactiveIDs, filter):
    chkID = False
    if labelFile != "" and len(activeIDs) > 0 and len(inactiveIDs) > 0:
        chkID = True
        labF = open(labelFile, 'w+')

    i, currID, labels, maxlab = 0, 0, {}, 0
    with open(inFile, 'r') as inF, open(outFile, 'w+') as outF:
        lines = inF.readlines()
        while (i < len(lines)):
            graphID = lines[i][1:].strip()
            if chkID and graphID not in activeIDs and graphID not in inactiveIDs:
                if not(filter):
                    outF.write('t # {}\n'.format(10 * int(graphID)))

                V = int(lines[i + 1].strip())
                i += 2
                if not(filter):
                    for j in range(V):
                        label = lines[i + j]
                        if not(label in labels):
                            labels[label] = maxlab
                            maxlab += 1
                        label = labels[label]
                        outF.write('v {} {}\n'.format(j, label))
                i += V

                E = int(lines[i].strip())
                i += 1
                if not(filter):
                    for j in range(E):
                        outF.write('e {}'.format(lines[i + j]))
                i += E

            else:
                outF.write('t # {}\n'.format(currID))
                if chkID:
                    if graphID in activeIDs:
                        labF.write('1\n')
                    elif graphID in inactiveIDs:
                        labF.write('2\n')
                currID += 1

                V = int(lines[i + 1].strip())
                i += 2
                for j in range(V):
                    label = lines[i + j]
                    if not(label in labels):
                        labels[label] = maxlab
                        maxlab += 1
                    label = labels[label]
                    outF.write('v {} {}\n'.format(j, label))
                i += V

                E = int(lines[i].strip())
                i += 1
                for j in range(E):
                    outF.write('e {}'.format(lines[i + j]))
                i += E

    if chkID:
        labF.close()


def Run(args):
    activeIDs, inactiveIDs = getLabels(args['active'], args['inactive'])
    convert(args['inFile'], args['outFile'], args['labels'],
            activeIDs, inactiveIDs, args['filter'])


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
