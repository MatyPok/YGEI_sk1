#Graph definition
V = [1, 2, 3, 4, 5, 6, 7, 8, 9]

E = [
    [1, 2, 8], 
    [1, 3, 4], 
    [1, 5, 2], 
    [2, 1, 8], 
    [2, 3, 5], 
    [2, 4, 2], 
    [2, 7, 6], 
    [2, 8, 7], 
    [3, 1, 4],  
    [3, 2, 5], 
    [3, 6, 3], 
    [3, 7, 4], 
    [4, 2, 2], 
    [4, 9, 3], 
    [5, 1, 2], 
    [5, 6, 5], 
    [6, 3, 3], 
    [6, 5, 5], 
    [6, 7, 5], 
    [6, 8, 7], 
    [6, 9, 10], 
    [7, 2, 6], 
    [7, 3, 4], 
    [7, 6, 5], 
    [7, 8, 3], 
    [8, 2, 7], 
    [8, 6, 7], 
    [8, 7, 3], 
    [8, 9, 1], 
    [9, 4, 3], 
    [9, 6, 10], 
    [9, 8, 1]
    ]


# Test Graph
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
}


def dict2lists(G):
    V = list(G.keys())
    E = []

    for v in V:
        K = list(G[v].keys())
        for k in K:
            e = [v,k,G[v][k]]
            E.append(e)
    return V,E

def find(u,P):
    # find parent node of u
    while P[u] != u:
        u = P[u] # going to predecessor
    return u # return predecessor
        
        
def union(u,v,P):
    # find the roots of both nodes
    root_u = find(u,P)
    root_v = find(v,P)
    
    # if they are not the same, we can make an union
    if root_u != root_v:
        P[root_v] = root_u # connect the second tree to the firts one
    
    
def make_set(u,P):
    P[u] = u # predecessor of u is u

    
def boruvka(G):
    # transfrom graph from dictionary representation to lists
    V, E = dict2lists(G)

    from math import inf
    # computes the minimum spam tree
    # input: V = vertices, E = edges
    # output: T = spam tree, wt = weight of T
    T = [] # initialize the empty list
    wt = 0 # initial weight of tree is 0
    
    P = [inf] * (len(V) + 1) # list of roots
    #r = [inf] * (len(E) + 1) # list of ranks
    
    for v in V:
        make_set(v,P) # initialize trees
    
    # sort edges in respect to weights
    E_sorted = sorted(E, key=lambda it:it[2]) 
    
    for e in E_sorted:
        u, v, w = e
        
        # union find
        if find(u,P) != find(v,P):
            union(u,v,P)
            T.append([u,v,w])
            wt = wt + w
        
    return T, wt


print(boruvka(G))

# Import pyplot for plot and our function for Geopackage to graph conversion
from ygei_lines2graph import lines2graph_gpkg
from matplotlib import pyplot as plt

# Call the gpkg2graph function, as an argument select one of 3 options of cost metric,
# and the .gpkg file for conversion, the default file silnice.gpkg
G, C = lines2graph_gpkg(type_of_weight='Euclidean distance')

from obce_load import obcefromgpkg, obec2node_of_graph
O = obcefromgpkg()
OC = obec2node_of_graph(O,C)

# Test Prim's algorithm
T, weight = boruvka(G)
print("Minimum Spanning Tree:", T)
print("Total Weight:", weight)

# graphically display the network and the computed path (greed)
for node, neighbors in G.items():
    x, y = C[node]
    for neighbor in neighbors:  
        nx, ny = C[neighbor] 
        if node in [t[0] for t in T] and neighbor in [t[1] for t in T]:
            plt.plot([x, nx], [y, ny], 'g-')
        else:
            plt.plot([x, nx], [y, ny], 'c-')
    
    plt.plot(x, y, 'ro')
    #plt.text(x, y, str(node), fontsize=8, ha='right', va='bottom', color='black')
    try:
        name = OC[node]
        plt.text(x, y, str(name), fontsize=8, ha='right', va='bottom', color='black')
    except:
        continue

plt.show()
