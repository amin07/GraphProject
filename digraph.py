# this module implements the dag part of lexis project
import subprocess




class CoreDAG(object):
    n = []

cprocess = subprocess.Popen(["./suffixtree/Suffix.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)

# need to convert sequence chars into integer sequence so that a new symbol can be added always

#cprocess.stdin.write("aabcdeaabxfd")
while cprocess.poll()==None:
    print (cprocess.communicate(input="aabcabaabxyzaab")[0])      #communicates param passes string to stdin of child process

print ("done finding maximal repeats")


