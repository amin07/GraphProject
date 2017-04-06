# this module implements the dag part of lexis project
import subprocess
cprocess = subprocess.Popen(["./suffixtree/Suffix.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

# need to convert sequence chars into integer sequence so that a new symbol can be added always
while cprocess.poll()==None:
    print cprocess.communicate("aabcdeaabxfd")[0]      #communicates param passes string to stdin of child process

print "done finding maximal repeats"
