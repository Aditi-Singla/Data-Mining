import os
import sys
import argparse


def getParser():
    parser = argparse.ArgumentParser(
        description='Create test set out of complete data')
    parser.add_argument('inFile', help='Input Database of graphs')
    parser.add_argument('--active', default="", help='Active graph IDs')
    parser.add_argument('--inactive', default="", help='Inactive graph IDs')
    return parser


def getLabels(activeFile, inactiveFile):
    activeIDs, inactiveIDs = set(), set()
    if activeFile != "" and inactiveFile != "":
        with open(activeFile, 'r') as actFile:
            activeIDs = set(map(lambda x: x.strip(), actFile.readlines()))
        with open(inactiveFile, 'r') as inactFile:
            inactiveIDs = set(map(lambda x: x.strip(), inactFile.readlines()))
    return activeIDs, inactiveIDs


def convert(inFile, trainFile, trainActFile, trainInactFile,
            testFile, testLabelFile, activeIDs, inactiveIDs):
    with open(inFile, 'r') as inF, open(trainFile, 'w+') as trainF, open(trainActFile, 'w+') as trainActF, open(trainInactFile, 'w+') as trainInactF, open(testFile, 'w+') as testF, open(testLabelFile, 'w+') as testLabelF:
        lines = inF.readlines()
        i, currID, labels, maxlab = 0, 0, {}, 0
        while (i < len(lines)):
            graphID = lines[i][1:].strip()
            if graphID not in activeIDs and graphID not in inactiveIDs:
                trainF.write(lines[i])
                writestream = trainF
            else:
                if (currID % 5 != 0):
                    trainF.write(lines[i])
                    if graphID in activeIDs:
                        trainActF.write('{}\n'.format(graphID))
                    elif graphID in inactiveIDs:
                        trainInactF.write('{}\n'.format(graphID))
                    writestream = trainF
                else:
                    testF.write(lines[i])
                    if graphID in activeIDs:
                        testLabelF.write('1\n')
                    else:
                        testLabelF.write('2\n')
                    writestream = testF
                currID += 1
        
            writestream.write(lines[i + 1])
            V = int(lines[i + 1].strip())
            i += 2
            for j in range(V):
                writestream.write(lines[i + j])
            i += V

            writestream.write(lines[i])
            E = int(lines[i].strip())
            i += 1
            for j in range(E):
                writestream.write(lines[i + j])
            i += E


def Run(args):
    inFileParts = args['inFile'].split('.')
    trainFile = '{}_train.{}'.format(inFileParts[0], inFileParts[1])
    trainActFile = '{}_train_active.{}'.format(inFileParts[0], inFileParts[1])
    trainInactFile = '{}_train_inactive.{}'.format(
        inFileParts[0], inFileParts[1])
    testFile = '{}_test.{}'.format(inFileParts[0], inFileParts[1])
    testLabelFile = '{}_test_labels.{}'.format(inFileParts[0], inFileParts[1])

    activeIDs, inactiveIDs = getLabels(args['active'], args['inactive'])
    convert(args['inFile'], trainFile, trainActFile, trainInactFile, testFile,
            testLabelFile, activeIDs, inactiveIDs)


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
