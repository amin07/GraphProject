# this module implements the dag part of lexis project
import sys
import subprocess
from sys import stdin
import networkx as nx
from _thread import _count
import matplotlib.pyplot as plt


class CoreDAG(object):
    __intSequences = []             # contains converted string in int sequence form
    __symDic = {} 
    __adjList = {}
    __sequenceToSuffix = [] 
    __lexisGraph = nx.MultiDiGraph()
    __nodeString = {}               # string on each node
    __nodeTrack = []                # contains distinct node values with seperator
    __edgeToNode = []               # corresponding elements will have an edge to corresponding element of _nodeTrack
    __uniqueSymbols = []            # unique symbols list who differentiate between sequences
    __uniqueSymbolids = []
    __newSymbol = 0
    
    # non private variables for printing purpose
    _uniqueSymCnt = 0
    _totSymCnt = 0
    
    
    def __init__(self, textData):
        tData = self.dataSetup(textData, 'igem');
        #tData = self.dataSetup(textData, 'simple_input');
        #tData = self.dataSetup(textData, 'yeast');

        # this section was for preparing data, but they now transfered to dataSetup method
#         _charDic = {}
#         _countDic = {}
#         _counter = 1
#         _processedSeq = ''
#         for i in range(len(tData)):
#             if tData[i] not in _countDic:
#                 _countDic[tData[i]] = _counter
#                 _charDic[_counter] = tData[i]
#                 _counter +=1
#             _processedSeq += str(_countDic[tData[i]]) + ' '
#         self.__symDic = _charDic
#         self.__intSequences = _processedSeq
#         self.__newSymbol = _counter
        
        # initializing nodetrack from the intSequences
#         self.__nodeTrack.extend(map(int, self.__intSequences.split()))
#         self.__edgeToNode.extend(0 for val in range(len(self.__nodeTrack)))
#         self.__nodeTrack.append(self.__newSymbol)
#         self.__edgeToNode.append(self.__newSymbol)
#         self.__uniqueSymbols.append(self.__newSymbol)
#         self.__uniqueSymbolids.append(len(self.__nodeTrack)-1)
#         self.__newSymbol += 1
#         print (self.__nodeTrack)
#         print ([j for j in range(len(self.__nodeTrack))])
#         print (self.__edgeToNode)

        # updated initialization considering the case of multiple targets

        for val in self.__intSequences.split():
            if int(val) in self.__uniqueSymbols:
                self.__nodeTrack.append(int(val))
                self.__edgeToNode.append(int(val))
            else :
                self.__nodeTrack.append(int(val))
                self.__edgeToNode.append(0)
        self.__nodeTrack.append(self.__newSymbol)
        self.__edgeToNode.append(self.__newSymbol)
        self.__uniqueSymbols.append(self.__newSymbol)
        self.__newSymbol += 1
        print (self.__nodeTrack)
        print ([j for j in range(len(self.__nodeTrack))])
        print (self.__edgeToNode)
        
    def dataSetup(self, fStream,dataType):
        #fStream = open('test_data/igem.txt','r');
        tData = fStream.read()
        if dataType=='igem':
            print ('igem Processing')       # this processing for multiple target nodes
            _brickDic = {}
            _countDic = {}
            _counter = 1
            _processedSeq = ''
            sepflag = False 
            for seq in tData.split('\n')[:787]:
                if sepflag == True:
                # this code is for multiple targets handling
                    _processedSeq += str(_counter) + ' '
                    self.__uniqueSymbols.append(_counter);
                    _counter += 1
                sepflag = True
            
                for bb in seq.split(' '):
                    self._totSymCnt += 1
                    if bb not in _countDic:
                        _countDic[bb] = _counter
                        _brickDic[_counter] = bb
                        _counter +=1
                        self._uniqueSymCnt += 1
                    _processedSeq += str(_countDic[bb]) + ' '
                         
            self.__symDic = _brickDic
            self.__intSequences = _processedSeq
            self.__newSymbol = _counter
        elif dataType == 'simple_input':
            print ("simple input processing")
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
        elif dataType=='yeast':
            print ('yeast processing')
            
        return tData  
    def getTheGraph(self):
        return self.__lexisGraph           
    def printSeq(self):
        print (self.__intSequences)
    def getNodeLabels(self):
        return self.__nodeString
    def getIntSequences(self):
        return self.__intSequences;    
     
    def getMaximalRepeats(self):
        cprocess = subprocess.Popen(["./suffixtree/Suffix.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
        allreapts = ''
        while cprocess.poll() is None:
            allreapts += (cprocess.communicate(input=' '.join(map(str,self.__nodeTrack)))[0])
            #print (cprocess.communicate(input=' '.join(map(str,self.__nodeTrack)))[0])
        #print (allreapts)
        return allreapts
    def updateNodeTrack(self, rp, rpoccs):
        print ("updating node track...")
        tempNodeTrack = []
        tempEdgeTrack = []
        lastId = 0
        for i in rpoccs:
            tempNodeTrack += self.__nodeTrack[lastId:i] + [self.__newSymbol]
            tempEdgeTrack += self.__edgeToNode[lastId:i] + [self.__edgeToNode[i]]
            lastId = i+len(rp)
            
        self.__nodeTrack = tempNodeTrack + self.__nodeTrack[lastId:]
        self.__edgeToNode = tempEdgeTrack + self.__edgeToNode[lastId:]
        self.__nodeTrack = self.__nodeTrack + rp
        self.__edgeToNode = self.__edgeToNode + [self.__newSymbol for j in range(len(rp))]
        self.__newSymbol += 1
        
        self.__nodeTrack = self.__nodeTrack + [self.__newSymbol]
        self.__edgeToNode = self.__edgeToNode + [self.__newSymbol]
        self.__uniqueSymbols.append(self.__newSymbol)
        self.__uniqueSymbolids = set([])
        for i in range(len(self.__nodeTrack)):
            if self.__nodeTrack[i] in self.__uniqueSymbols:
                self.__uniqueSymbolids.add(i)
        self.__newSymbol += 1
        print (self.__nodeTrack)
        print (self.__edgeToNode)
        print (self.__uniqueSymbols)
        print (self.__uniqueSymbolids)
    def constructDAG(self):
        print ("constructing dag....")
        sepFlag = False
        for i in range(len(self.__nodeTrack)):
            if i not in self.__uniqueSymbolids:
                currnode = self.__edgeToNode[i]       
                if sepFlag and currnode==0:
                    sepFlag = False
                    self.__adjList[currnode].append([])
                    
                if self.__nodeTrack[i] not in self.__adjList:
                    self.__adjList[self.__nodeTrack[i]]=[]

#                 if currnode not in self.__adjList:
#                     self.__adjList[currnode]=[self.__nodeTrack[i]]
#                 else :
#                     self.__adjList[currnode].append(self.__nodeTrack[i])
                if currnode not in self.__adjList:
                    if currnode == 0:
                        self.__adjList[currnode] = [[self.__nodeTrack[i]]]
                    else :
                        self.__adjList[currnode] = [self.__nodeTrack[i]]
                else:
                    if currnode == 0:
                        self.__adjList[currnode][-1].append(self.__nodeTrack[i])
                    else :
                        self.__adjList[currnode].append(self.__nodeTrack[i])
            else :
                sepFlag = True;
        print ("print adjacency list..")
        print (self.__adjList)
         
        # constructing actual DAG
        for target_node in self.__adjList:
            if target_node == 0:
                for target_list in self.__adjList[target_node]:
                    for e in target_list:
                        self.__lexisGraph.add_edge(target_node, e)
            else :
                for e in self.__adjList[target_node]:
                    self.__lexisGraph.add_edge(target_node, e)
                    
        print (self.__lexisGraph.nodes())
        print (self.__lexisGraph.edges()) 
        #print (self.__lexisGraph.edges())
#             #if target_node not in self.__lexisGraph:
#             #        self.__lexisGraph.add_node(target_node)
#             for edge2thisnode in self.__adjList[target_node]:
#             #    if edge2thisnode not in self.__lexisGraph:
#             #        self.__lexisGraph.add
#                 self.__lexisGraph.add_edge(edge2thisnode, target_node)      # adding nodes automatically
#                 
#         #nx.draw(self.__lexisGraph, pos = nx.spring_layout(self.__lexisGraph))
#         #plt.axis('off')
        
#         print ("printing source nodes(should be equal to distinct # of characters)")
#         for i in (self.__lexisGraph.nodes()):
#             if self.__lexisGraph.in_degree(i)==0:
#                 print (self.__symDic[i])
    
    # recursive function for assigning string label of each node
    def stringOnEachNode(self, currnode):
        #print ('calculating string on each node...')
        if len(self.__adjList[currnode])==0:
            self.__nodeString[currnode]=self.__symDic[currnode]
            return self.__nodeString[currnode]
        self.__nodeString[currnode]='';
        for in_edge in self.__adjList[currnode]:
            #print ("currnode %d, edge %d" % (currnode,in_edge[0]))
            self.__nodeString[currnode] += self.stringOnEachNode(in_edge)
            #print (in_edge[0])
        return self.__nodeString[currnode] 
    
    def stringOnEachNodeUpdated(self, currnode):  
        
        if currnode == 0:
            self.__nodeString[currnode]=[]     
            for node_list in self.__adjList[currnode]:
                tempString = ''
                for e in node_list:
                    tempString += self.stringOnEachNodeUpdated(e)
                self.__nodeString[currnode].append(tempString)
        else :  
            if len(self.__adjList[currnode])==0:
                self.__nodeString[currnode]=self.__symDic[currnode]
                return self.__nodeString[currnode]
            self.__nodeString[currnode]='';
            for node_list in self.__adjList[currnode]:
                #print ("currnode %d, edge %d" % (currnode,in_edge[0]))
                self.__nodeString[currnode] += self.stringOnEachNodeUpdated(node_list)
                #print (in_edge[0])
        return self.__nodeString[currnode] 
    
    
       
    def lexisFunc(self):   
        while True:
            #checking which repeat to use
            repeats = self.getMaximalRepeats()
            #print ("repeats :")
            #print (repeats)
            maxGain = -1
            for repString in repeats.split('\n'):
                repString.strip('\n')
                #print ("a" + repString+"b")
                if repString != "":
                    rp,rpoccs = (repString.split('#')[0],repString.split('#')[1])
                    rplen = len(rp.split())
                    if  rplen>=2:
                       rpoccssorted = list(map(int, rpoccs.split()))
                       rpoccssorted.sort()
                       realoccs = [rpoccssorted[0]]
                       currIdx = rpoccssorted[0]
                       for j in range(len(rpoccssorted)-1):
                           if rpoccssorted[j+1] >= currIdx+rplen:
                               realoccs.append(rpoccssorted[j+1])
                               currIdx = rpoccssorted[j+1]
                       if len(realoccs)>=2 :
                           gainFromThisRp = (rplen-1) * (len(realoccs) - 1)
                           #print (gainFromThisRp)
                           #print (list(map(int, rp.split())))
                           if(gainFromThisRp > maxGain):
                               maxGain = gainFromThisRp
                               maxGainRp = list(map(int, rp.split()))
                               maxGainRpOcss = rpoccssorted
            # no candidate repeats found of len more than 1   
            if maxGain<0:
                break 
            self.updateNodeTrack(maxGainRp,maxGainRpOcss)
            
            #print (maxGain)
            #print (maxGainRp)
        self.constructDAG()
        self.stringOnEachNodeUpdated(0)
        print ("print string on each node..")
        print (self.__nodeString)

if __name__ == "__main__":
    
    # need to convert sequence chars into integer sequence so that a new symbol can be added always
    
    #cprocess.stdin.write("aabcdeaabxfd")
    #while cprocess.poll()==None:
    #    print (cprocess.communicate(input=)[0])      #communicates param passes string to stdin of child process
    
    fileStream = open('test_data/igem.txt', 'r')
    #fileStream = open('test_data/input.txt', 'r')
    g = CoreDAG(fileStream)
    g.printSeq()
    g.lexisFunc() 
    G = g.getTheGraph()
    print ("number of nodes {0}, number of edges {1}".format(G.number_of_nodes(), G.number_of_edges()))
    print ("number of unique symbols in whole text {0}".format(g._uniqueSymCnt))
    print ("number of total symbols in whole text {0}".format(g._totSymCnt))
#     nodeLabels = g.getNodeLabels()
#     print ([len(i) for i in nodeLabels.values()])
#     pos = nx.spring_layout(G)
#     nx.draw_networkx_nodes(G, pos, node_size=[300*len(i) for i in nodeLabels.values()])
#     nx.draw_networkx_edges(G, pos)
#     nx.draw_networkx_labels(G, pos, nodeLabels)
    #nx.draw_networkx_edges(G, pos, edgelist=black_edges, arrows=False)
    #plt.show()
     
    