import os
import sys
import argparse


def getParser():
    parser = argparse.ArgumentParser(
        description='Create test set out of complete data')
    parser.add_argument('inFile', help='Input Database of graphs')
    parser.add_argument('--active', default="", help='Active graph IDs')
    return parser


def getLabels(activeFile):
    activeIDs = set()
    if activeFile != "":
        with open(activeFile, 'r') as actFile:
            activeIDs = set(map(lambda x: x[1:].strip(), actFile.readlines()))
    return activeIDs


def convert(inFile, trainFile, trainActFile, trainInactFile,
            testFile, testLabelFile, activeIDs):
    with open(inFile, 'r') as inF, open(trainFile, 'w+') as trainF, open(trainActFile, 'w+') as trainActF, open(trainInactFile, 'w+') as trainInactF, open(testFile, 'w+') as testF, open(testLabelFile, 'w+') as testLabelF:
        lines = inF.readlines()
        i, currID, labels, maxlab = 0, 0, {}, 0
        while (i < len(lines)):
            if (lines[i] == '\n'):
                i += 1
                continue
            graphID = lines[i][1:].strip()
            if (currID % 10 != 0):
                trainF.write(lines[i])
                if graphID in activeIDs:
                    trainActF.write('{}\n'.format(graphID))
                else:
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

            i += 1
            writestream.write(lines[i])
            V = int(lines[i].strip())
            i += 1
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

    activeIDs = getLabels(args['active'])
    convert(args['inFile'], trainFile, trainActFile, trainInactFile, testFile,
            testLabelFile, activeIDs)


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
