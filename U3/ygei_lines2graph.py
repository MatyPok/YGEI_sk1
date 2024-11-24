from typing import Literal
import fiona
import math
def lines2graph_gpkg(type_of_weight: Literal['Euclidean distance', 'Transport time', 'Transport time with deviality'], file: str ='silnice.gpkg'):
    #file = 'silnice.gpkg'
    net = fiona.open(file)

    # create empty dictionaries
    G = {}
    C = {}
    W = {}

    # Z popisu dat databáze ArcČR500 v.3.3
    # 1 - dálnice
    # 2 - rychlostní silnice
    # 3 - silnice I. třídy
    # 4 - silnice II. třídy
    # 5 - silnice III. třídy
    # 6 - neevidovaná silnice

    # expected speed in respect to he class of road
    road_classes = {1:130, 2:110, 3:90, 4:80, 5:60, 6:50}

    for line in net:
        #coords = line.geometry.coordinates[0]
        coords = line.geometry['coordinates'][0]

        (x1, y1) = coords[0]
        (x2, y2) = coords[-1]
        
        start = (x1 , y1)
        end = (x2, y2)
        
        if start not in C:
            C[start] = [x1, y1]
        
        if end not in C:
            C[end] = [x2, y2]


        if start not in G:
            G[start] = []
        if end not in G:
            G[end] = []
        
        # add connection, if the two start and end node are connected
        G[start].append(end)
        G[end].append(start)


        # According to what parameter is wanted to be the cost metric, the next lines computes the weights,
        # that are the 1) Euklidian polyline lenght, 2) Transport time in respect to the speed that is expected 
        # on the type of road, that is taken, # 3) Trasport time like in 2) but the curvature of the road is taken as parameter
        if type_of_weight == 'Euclidean distance':
            w = float(line.properties['SHAPE_Length'])
        elif type_of_weight == 'Transport time':
            d = float(line.properties['SHAPE_Length'])
            trida = int(line.properties['TRIDA'])
            v = road_classes[trida]/3.6
            t = d/v
            w = t
        elif type_of_weight == 'Transport time with deviality':
            d = float(line.properties['SHAPE_Length'])
            trida = int(line.properties['TRIDA'])
            v = road_classes[trida]/3.6
            t = d/v
            d_bod_bod = math.sqrt((x1 - x2)**2 + (y1 - y2)**2)
            w = t*(d/d_bod_bod)
        if start not in W:
            W[start] = w
        
        if end not in W:
            W[end] = w 
    # node mapping creates an number (i = 1,...,N; where i is integer and N is the number of nodes) for each node
    node_mapping = {node: i+1 for i, node in enumerate(C)}

    # replacing the coordinates that are in role of key  in dictionary with an number (1,...,N)
    # keys are now integers and the values are coordinates in C_m, and the keys of neighbors and the weights of edges in G_m
    C_m = {node_mapping[node]: coords for node, coords in C.items()}
    G_m = {node_mapping[node]: {node_mapping[neighbor]:round(W[neighbor]) for neighbor in neighbors} for node, neighbors in G.items()}

    # return graph with weighted edges (by the selected criterium) and return the dictionary with the coordinates of each node
    return G_m, C_m

#G_m, C_m = lines2graph_gpkg(type_of_weight='Euclidean distance')
#print(G_m)
#print(C_m)

if __name__ == '__main__':
    from matplotlib import pyplot as plt

    G_m, C_m = lines2graph_gpkg(type_of_weight='Euclidean distance')

    print(G_m, C_m)

    for node, neighbors in G_m.items():
        x, y = C_m[node]
        for neighbor in neighbors:
            nx, ny = C_m[neighbor]
            plt.plot([x, nx], [y, ny], 'b-')
        plt.plot(x, y, 'ro')
        plt.text(x, y, str(node), fontsize=8, ha='right', va='bottom', color='black')
    plt.show()