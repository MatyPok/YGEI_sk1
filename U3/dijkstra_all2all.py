
from math import inf
from queue import PriorityQueue
from queue import Empty


# From cv 7
# find path between two poins from given predecessors
def rPath(u,v,P):
    path = []
    # path shortening
    while v != u and v != (-1):
        path.append(v)
        v = P[v]
    path.append(v)
    #if v != u:
        #print('Incorrect path')
    return path

# compute the total cost of path from the weights of edges of the path
def sum_of_weights(path, G):
    w = 0
    for i in range(len(path)-1):
        w = w + G[path[i]][path[i+1]]
    return w


def dijkstra(G, start, end):
    
    n = len(G)+1 # lenght of graph
    d = [inf]*n # all nodes to infinity
    P = [-1]*n # predecessors to -1
    
    PQ = PriorityQueue()
    PQ.put((0, start)) # adding the start vertex into queue
    d[start] = 0
    
    while not PQ.empty():
        du, u  = PQ.get() # get the first element
        
        # iterate through the neighbours, edge relaxation
        for v, wuv in G[u].items():
            if d[v] > d[u] + wuv: # if the path through u is better
                d[v] = d[u] + wuv 
                P[v] = u # the path is not through v, but u instead
                PQ.put((d[v], v)) # putting v into the queue
    
    path = rPath(start,end,P)
    return path, d[v]



'''# Test Graph
G = {
    1 : {2:8, 3:4, 5:2},
    2 : {1:8, 3:5, 4:2, 7:6, 8:7},
    3 : {1:4, 2:5, 6:3, 7:4},
    4 : {2:2, 9:3},
    5 : {1:2, 6:5},
    6 : {3:3, 5:5, 7:5, 8:7, 9:10},
    7 : {2:6, 3:4, 6:5, 8:3},
    8 : {2:7, 6:7, 7:3, 9:1},
    9 : {4:3, 6:10, 8:1}
}'''


'''P, D = dijkstra(G, 1)
print(P,D)

path = rPath(1,9,P)
print(path)'''


# Import pyplot for plot and our function for Geopackage to graph conversion
from ygei_lines2graph import lines2graph_gpkg
from matplotlib import pyplot as plt

# Call the gpkg2graph function, as an argument select one of 3 options of cost metric,
# and the .gpkg file for conversion, the default file silnice.gpkg
G, C = lines2graph_gpkg(type_of_weight='Euclidean distance')

# call the dijkstra algorithm for every pair of nodes
all_paths = []
for start, neigbors in G.items():
    for end, neigbors in G.items():
        if start != end:
            path, D = dijkstra(G, start, end)
            all_paths.append([path,D])

print(all_paths)



