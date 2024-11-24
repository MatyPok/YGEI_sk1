
from math import inf


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


def bellman_ford(G, start):
    n = len(G) + 1
    d = [inf] * n
    P = [-1]*n # predecessors to -1
    d[start] = 0

    visited_edges = set()
    in_negative_cycle = [False] * n  # Flags for nodes in negative cycles
    
    for _ in range(n - 1):  # Relax edges n-1 times
        for u in G:
            for v, w in G[u].items():
                if (u, v) not in visited_edges and not in_negative_cycle[v]:
                    if d[u] + w < d[v]:
                        d[v] = d[u] + w
                        P[v] = u
                        visited_edges.add((u, v))
    
    # Check for negative weight cycles
    for u in G:
        for v, w in G[u].items():
            if d[u] + w < d[v]:
                #raise ValueError("Graph contains a negative-weight cycle")
                print('Value Warning - Graph contains a negative-weight cycle')
                in_negative_cycle[v] = True
                in_negative_cycle[u] = True  # Flag nodes in negative cycles

    # Avoid paths going through negative cycles
    #for u in range(n):
    #    if in_negative_cycle[u]:
    #        d[u] = float('-inf')  # Mark distance as unreachable
    
    return P, d[v]



#Graph
G = {
    1 : {2:8, 3:-4, 5:2},
    2 : {1:8, 3:-5, 4:-2, 7:-6, 8:7},
    3 : {1:-4, 2:5, 6:-3, 7:4},
    4 : {2:2, 9:3},
    5 : {1:-2, 6:5},
    6 : {3:3, 5:-5, 7:5, 8:7, 9:10},
    7 : {2:6, 3:4, 6:-5, 8:-3},
    8 : {2:7, 6:7, 7:3, 9:1},
    9 : {4:3, 6:10, 8:-1}
}

P, D = bellman_ford(G,1)
print(P,D)

path = rPath(1,9,P)
print(path)