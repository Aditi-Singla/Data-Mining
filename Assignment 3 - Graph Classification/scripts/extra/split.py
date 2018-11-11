import os
import sys
import argparse
import subprocess


def getParser():
    parser = argparse.ArgumentParser(
        description='Split dataset into training and testing')
    parser.add_argument('inFile', help='Input Database of graphs')
    parser.add_argument('testFrac', type=float,
                        help='Fractions of testing samples')
    return parser


def split(inFile, numTestSamples, numTrainSamples):
    inFileParts = inFile.split('.')
    testFile = '{}_test.{}'.format(inFileParts[0], inFileParts[1])
    activeFile = '{}_active.{}'.format(inFileParts[0], inFileParts[1])
    inactiveFile = '{}_inactive.{}'.format(inFileParts[0], inFileParts[1])
    testSamples = 0
    with open(inFile, 'r') as inF, open(testFile, 'w+') as testF, open(activeFile, 'w+') as actF, open(inactiveFile, 'w+') as inactF:
        for line in inF:
            if numTrainSamples > 0 and numTrainSamples % 2 == 0 and line.startswith('#'):
                actF.write(line[1:])
                numTrainSamples -= 1
            elif numTrainSamples >= 0 and numTrainSamples % 2 == 1 and line.startswith('#'):
                inactF.write(line[1:])
                numTrainSamples -= 1
            elif numTrainSamples <= 0 and testSamples <= numTestSamples:
                if line.startswith('#'):
                    testF.write(line)
                    testSamples += 1
                elif testSamples > 0:
                    testF.write(line)


def Run(args):
    numGraphs = int(subprocess.check_output(
        'grep \# {} | wc -l'.format(args['inFile']), shell=True).strip())
    numTestSamples = int(round(numGraphs * args['testFrac']))
    numTrainSamples = numGraphs - numTestSamples
    split(args['inFile'], numTestSamples, numTrainSamples)


if __name__ == '__main__':
    args = vars(getParser().parse_args(sys.argv[1:]))
    Run(args)
