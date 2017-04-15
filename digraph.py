# this module implements the dag part of lexis project
import sys
import subprocess
from sys import stdin
import networkx as nx
from _thread import _count

class CoreDAG(object):
    __intSequences = []             # contains converted string in int sequence form
    __symDic = {} 
    __adjList = {}
    __sequenceToSuffix = [] 
    __lexisGraph = nx.MultiDiGraph()
    __nodeString = {}               # string on each node
    __nodeTrack = []                # contains distinct node values with seperator
    __edgeToNode = []               # corresponding elements will have an edge to corresponding element of _nodeTrack
    __uniqueSymbols = []
    __uniqueSymbolids = []
    __newSymbol = 0
    
    def __init__(self, textData):
        tData = textData.read()
        _charDic = {}
        _countDic = {}
        _counter = 1
        _processedSeq = ''
        for i in range(len(tData)):
            if tData[i] not in _countDic:
                _countDic[tData[i]] = _counter
                _charDic[_counter] = tData[i]
                _counter +=1
            _processedSeq += str(_countDic[tData[i]]) + ' '
        self.__symDic = _charDic
        self.__intSequences = _processedSeq
        self.__newSymbol = _counter
        
        # initializing nodetrack from the intSequences
        self.__nodeTrack.extend(map(int, self.__intSequences.split()))
        self.__edgeToNode.extend(0 for val in range(len(self.__nodeTrack)))
        self.__nodeTrack.append(self.__newSymbol)
        self.__edgeToNode.append(self.__newSymbol)
        self.__newSymbol += 1
        print (self.__nodeTrack)
        print (self.__edgeToNode)
        
               
    def printSeq(self):
        print (self.__intSequences)
        
     
    def getMaximalRepeats(self):
        cprocess = subprocess.Popen(["./suffixtree/Suffix.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
        allreapts = ''
        while cprocess.poll() is None:
            allreapts += (cprocess.communicate(input=' '.join(map(str,self.__nodeTrack)))[0])
            #print (cprocess.communicate(input=' '.join(map(str,self.__nodeTrack)))[0])
        #print (allreapts)
        return allreapts
    
    def lexisFunc(self):
        repeats = self.getMaximalRepeats()
        maxGain = -1
        while True:
            #checking which repeat to use
            for repString in repeats.split('\n'):
                repString.strip('\n')
                #print ("a" + repString+"b")
                if repString != "":
                    rp,rpoccs = (repString.split('#')[0],repString.split('#')[1])
                    if  len(rp.split())>=2:
                       print (rp)
                       print (rpoccs)
            if maxGain<0:
                break 

if __name__ == "__main__":
    
    # need to convert sequence chars into integer sequence so that a new symbol can be added always
    
    #cprocess.stdin.write("aabcdeaabxfd")
    #while cprocess.poll()==None:
    #    print (cprocess.communicate(input=)[0])      #communicates param passes string to stdin of child process
    
    fileStream = open('input.txt', 'r')
    g = CoreDAG(fileStream)
    g.printSeq()
    #g.getMaximalRepeats()
    g.lexisFunc()
    
    