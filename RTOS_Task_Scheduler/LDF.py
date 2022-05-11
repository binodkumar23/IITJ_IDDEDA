#Importing Libraries
from collections import defaultdict
import networkx as nx
from heapq import *
from tabulate import tabulate
import matplotlib.pyplot as plt

# class for doing heap operations
class minHeap:
    def __init__(self):
        self.hea = []
    
    def push_heap(self,ele):
        heappush(self.hea,ele)
    
    def pop_heap(self):
        return heappop(self.hea)

    def get_top(self):
        return self.hea[0]

    def get_heap(self):
        return self.hea

    def isEmpty(self):
        return len(self.hea) == 0


# Input file reader

def input_file_reader():
    file = open("input/ldf_input.txt","r")
    for i in file.readlines():
        yield(i.strip())
x = input_file_reader()
n,m = map(int,next(x).split())
graph = defaultdict(list)
indegree = [0]*(n+1) 
edges = []
for _ in range(m):
    a,b = map(int,next(x).split())
    graph[b].append(a)
    edges.append([a,b])
    indegree[a]+=1

task = ["",]
deadline = [-1]
execution_time = [-1]
for _ in range(n):
    a,b,c = map(int,next(x).split())
    execution_time+=[b]
    deadline+=[c]
    task+=["T"+str(a)]

# utility to plot graph
def plot_graph(graph,edges):
    G = nx.DiGraph()
    G.add_edges_from(edges)
    pos = nx.spring_layout(G)
    nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'), node_size = 500)
    nx.draw_networkx_labels(G, pos,)
    nx.draw_networkx_edges(G, pos, edgelist=[edge for edge in G.edges()], edge_color='r', arrows=True,)
    plt.savefig("output/LDF_graph.png")
plot_graph(graph,edges)

hea = minHeap()
summary = []
time = 0

# intialise heap
for i in range(1,len(indegree)):
    if indegree[i]==0:
        hea.push_heap((-deadline[i],execution_time[i],i))

# main logic
while not hea.isEmpty():
    x,y,z = hea.pop_heap()
    summary.append(z)
    for i in graph[z]:
        indegree[i]-=1
        if indegree[i]==0:
            hea.push_heap((-deadline[i],execution_time[i],i))

# output file
file1 = open("output/ldf.txt", "w")
print("The task will be scheduled in following order:-",file=file1)
for i in summary[::-1]:
    print(task[i],end=" ",file=file1)
