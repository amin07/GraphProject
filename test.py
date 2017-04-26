
import networkx as nx
import matplotlib.pyplot as plt
print ("hello world")


myfile = open('test_data/igem.txt', 'r')


tdata = myfile.read()

brickset = set([])
for line in tdata.split('\n'):
    print (line)
    for brk in line.split(' '):
        brickset.add(brk);

print (len(tdata.split('\n')))
print (len(brickset))

for i in brickset:
    if(i=='BBa_B0010'):
        print (i)