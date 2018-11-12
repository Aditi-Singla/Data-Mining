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
    return parser


def getLabels(activeFile, inactiveFile):
    activeIDs, inactiveIDs = set(), set()
    if activeFile != "" and inactiveFile != "":
        with open(activeFile, 'r') as actFile:
            activeIDs = set(map(lambda x: x.strip(), actFile.readlines()))
        with open(inactiveFile, 'r') as inactFile:
            inactiveIDs = set(map(lambda x: x.strip(), inactFile.readlines()))
    return activeIDs, inactiveIDs


def convert(inFile, outFile, labelFile, activeIDs, inactiveIDs):
    chkID = False
    if len(activeIDs) > 0 and len(inactiveIDs) > 0:
        chkID = True
    if labelFile != "":
        labF = open(labelFile, 'w+')
    with open(inFile, 'r') as inF, open(outFile, 'w+') as outF:
        lines = inF.readlines()
        i, currID, labels, maxlab = 0, 0, {}, 0
        while (i < len(lines)):
            graphID = lines[i][1:].strip()
            if chkID and graphID not in activeIDs and graphID not in inactiveIDs:
                i += 1
                while i < len(lines) and not(lines[i].startswith('#')):
                    i += 1
            else:
                outF.write('t # {}\n'.format(currID))
                if chkID and labelFile != "":
                    if graphID in activeIDs:
                        labF.write('1\n')
                    else:
                        labF.write('2\n')
                currID += 1

                V = int(lines[i + 1].strip())
                i += 2
                for j in xrange(V):
                    label = lines[i + j]
                    if not(label in labels):
                        labels[label] = maxlab
                        maxlab += 1
                    label = labels[label]
                    outF.write('v {} {}\n'.format(j, label))
                i += V

                E = int(lines[i].strip())
                i += 1
                for j in xrange(E):
                    outF.write('e {}'.format(lines[i + j]))
                i += E
    if labelFile != "":
        labF.close()


def Run(args):
    activeIDs, inactiveIDs = getLabels(args['active'], args['inactive'])
    convert(args['inFile'], args['outFile'],
            args['labels'], activeIDs, inactiveIDs)


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
