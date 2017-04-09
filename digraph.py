# this module implements the dag part of lexis project
import sys
import subprocess
from sys import stdin
import networkx as nx

class CoreDAG(object):
    __intSequences = []             # contains converted string in int sequence form
    __symDic = {} 
    __adjList = {}
    __sequenceToSuffix = [] 
    __lexisGraph = nx.MultiDiGraph()
    __nodeString = {}               # string on each node
    __nodeTrack = []
    __uniqueSymbols = []
    __uniqueSymbolids = []
    __newSymbol = 0
    
    def __init__(self, textData):
        tData = textData.read()
        _charDic = {}
        _countDic = {}
        _counter = 0
        _processedSeq = ''
        for i in range(len(tData)):
            if tData[i] not in _countDic:
                _countDic[tData[i]] = _countDic
                _charDic[_counter] = tData[i]
                _counter +=1
            _processedSeq += str(_countDic[tData[i]]) + ' '
        self.__symDic = _charDic
        self.__intSequences = _processedSeq
               
    def printSeq(self):
        for i in self.__intSequences:
            print (i)    
        
        

if __name__ == "__main__":
    #cprocess = subprocess.Popen(["./suffixtree/Suffix.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    # need to convert sequence chars into integer sequence so that a new symbol can be added always
    
    #cprocess.stdin.write("aabcdeaabxfd")
    #while cprocess.poll()==None:
    #    print (cprocess.communicate(input="paacpaab")[0])      #communicates param passes string to stdin of child process
    
    fileStream = open('input.txt', 'r')
    g = CoreDAG(fileStream)
    g.printSeq()
    
    