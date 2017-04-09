# this module implements the dag part of lexis project
import sys
import subprocess
from sys import stdin


class CoreDAG(object):
    __intSequences = []             # contains converted string in int sequence form
    n = []
    
    #def __init__(self, ):
        

if __name__ == "__main__":
    cprocess = subprocess.Popen(["./suffixtree/Suffix.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    
    # need to convert sequence chars into integer sequence so that a new symbol can be added always
    
    #cprocess.stdin.write("aabcdeaabxfd")
    while cprocess.poll()==None:
        print (cprocess.communicate(input="paacpaab")[0])      #communicates param passes string to stdin of child process
    
    print ("done finding maximal repeats")
    str = input("enter a line")
    f = stdin
    while True:
        _str = f.readline().rstrip('\n')
        if(_str=="hi"):
            break
        print (_str)