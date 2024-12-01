
# Graph definition
G = {
    1: {2:8, 3:4, 5:2},
    2: {1:8, 3:5, 4:2, 7:6, 8:7},
    3: {1:4, 2:5, 6:3, 7:4},
    4: {2:2, 9:3},
    5: {1:2, 6:5},
    6: {3:3, 5:5, 7:5, 8:7, 9:10},
    7: {2:6, 3:4, 6:5, 8:3},
    8: {2:7, 6:7, 7:3, 9:1},
    9: {4:3, 6:10, 8:1},
}

def jarnik(G, start=1):
    """
    Implements Prim's algorithm to find the Minimum Spanning Tree (MST) of a graph,
    skipping disconnected components.
    
    Parameters:
        G: dict
            Graph represented as an adjacency list.
        start: int
            Starting vertex for Prim's algorithm.
    
    Returns:
        T: list
            List of edges in the MST.
        total_weight: int
            Total weight of the MST.
    """
    visited = set()  # Set to track visited nodes
    T = []  # initialize the empty list
    wt = 0  # initial weight of tree is 0

    # Start with the initial node
    unvisited = set(G.keys())  # Set of all nodes
    current_node = start

    count_of_components = 0

    # Start with the starting node
    #visited.add(start)
    while len(visited) < len(G):
        if current_node not in visited:
            visited.add(current_node)
            unvisited.remove(current_node)

        # Find the smallest edge that connects a visited node to an unvisited node
        min_edge = None
        for u in visited:
            for v, w in G[u].items():
                if v not in visited:  # Check if the edge leads to an unvisited node
                    if min_edge is None or w < min_edge[2]:
                        min_edge = (u, v, w)

    
        if min_edge:
            u, v, w = min_edge
            T.append((u, v, w))
            wt = wt + w
            visited.add(v)  # Mark the new node as visited

            unvisited.remove(v)
            current_node = v  # Move to the newly added node
        else:
            print("Warning, graph is not conncted. However, algorithm continues.")
            count_of_components = count_of_components + 1 # Counting how many unconnected components does graph have
            if unvisited:
                current_node = unvisited.pop()
                unvisited.add(current_node)  # Add it back to ensure correct iteration
            else:
                break  # All nodes have been visited
    print(f"Number of unconnected components: {count_of_components+1}")
    return T, wt


# Test Prim's algorithm
#T, weight = jarnik(G)
#print("Minimum Spanning Tree:", T)
#print("Total Weight:", weight)


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
T, weight = jarnik(G)
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