import fiona

def obcefromgpkg(file='obce.gpkg'):
    obce = fiona.open(file)

    O = {}

    for obec in obce:
        coords = obec.geometry['coordinates']
        name = obec.properties['NAZ_OBEC']

        O[name]=list(coords)    
    return O

def dist(A,B):
    import math
    return math.sqrt((A[0] - B[0])**2 + (A[1] - B[1])**2)

def obec2node_of_graph(O,C):
    # C = coordinates of each node of a network
    # O = towns with its coordinates

    # most of the time: len(C)>>len(O)

    # This function asignes for each town, the closest point of network
    towns_closest_to_points_from_C = {}
    for town, def_coord in O.items():
        closest_coord = None
        min_distance = float('inf')
        for id, coord in C.items():
            distance = dist(def_coord, coord)
            if distance < min_distance:
                min_distance = distance
                closest_coord = id
        towns_closest_to_points_from_C[closest_coord] = town

    return towns_closest_to_points_from_C


def node2obec_of_graph(O,C):
    # C = coordinates of each node of a network
    # O = towns with its coordinates

    # most of the time: len(C)>>len(O)

    # This function asignes for each town, the closest point of network
    towns_closest_to_points_from_C = {}
    for town, def_coord in O.items():
        closest_coord = None
        min_distance = float('inf')
        for id, coord in C.items():
            distance = dist(def_coord, coord)
            if distance < min_distance:
                min_distance = distance
                closest_coord = id
        towns_closest_to_points_from_C[town] = closest_coord

    return towns_closest_to_points_from_C


if __name__ == '__main__':
    O = obcefromgpkg()
    print(O)


