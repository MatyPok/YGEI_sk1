
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
    if v != u:
        print('Incorrect path')
    return path

# compute the total cost of path from the weights of edges of the path
def sum_of_weights(path, G):
    w = 0
    for i in range(len(path)-1):
        w = w + G[path[i]][path[i+1]]
    return w


def dijkstra(G, CO, town_start, town_end):
    
    start = CO[town_start]
    end = CO[town_end]

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
    
    path = rPath(start, end, P)

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
G, C = lines2graph_gpkg(type_of_weight='Transport time with deviality')

from obce_load import obcefromgpkg, obec2node_of_graph, node2obec_of_graph
O = obcefromgpkg()
OC = obec2node_of_graph(O,C)
CO = node2obec_of_graph(O,C)

# 5 Stříbrské nádraží (rozc.)
# 83 sjezd 107 na D5
# 267 Stará voda, 270 Okrouhlá
# 268 sjezd 162 na D6

# call the dijkstra algorithm for a starting point
path, D = dijkstra(G, CO, 'Stříbro', 'Cheb')
#print(P)

# Create path from the list of predecessors (from the dijkstra al.) with the same starting point and given end point
#path = rPath(83, 268, P)

# compute the cost of path
cost = sum_of_weights(path, G)
print(path, cost/60)
#print(G)

# graphically display the network and the computed path (greed)
for node, neighbors in G.items():
        x, y = C[node]
        if node in path:
            plt.plot(x, y, 'go')
        else:
            plt.plot(x, y, 'ro')
        #plt.text(x, y, str(node), fontsize=8, ha='right', va='bottom', color='black')
        for neighbor in neighbors:
            nx, ny = C[neighbor]
            if node in path and neighbor in path:
                plt.plot([x, nx], [y, ny], 'g-')
            else:
                plt.plot([x, nx], [y, ny], 'b-')
        try:
            name = OC[node]
            plt.text(x, y, str(name), fontsize=8, ha='right', va='bottom', color='black')
        except:
            continue
plt.show()