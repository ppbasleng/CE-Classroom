g = {
    "A" : {"B":2,"D":1},
    "B" : {"D":3,"E":10},
    "C" : {"A":4,"F":5},
    "D" : {"C":2,"E":2,"F":8,"G":4},
    "E" : {"G":6},
    "F" : {},
    "G" : {"F":1}
}
gn = ["A","B","C","D","E","F","G"]
# Dijkstra's algorithm for shortest path
def printPath(start, toV, distance, path,gn):
    print(start, ' to ', toV, sep = '',end=" : ")
    print('\tShortest path =', distance[toV])
    print('\tpath :', end = ' ' )
    pathout = gn[toV]
    p = path[toV]
    while p is not None:
        pathout = gn[p]+"->"+pathout
        p = path[p]
    print(pathout)
n = 7 # total nodes
known = [] # เก็บเฉพาะ vertex ที่รู้ระยะสั้นที่สุดแล้ว
distance = [float('inf')]*n #set to infinity
path = [None]*n
# set start vertex
start = 0
distance[start] = 0
# print(g[gn[0]])
while len(known) != n:
    # greedy : find vertex of smallest distance
    min = float('inf')
    for i in range(n):
        if i not in known and distance[i] < min:
            min_i = i # index
            min = distance[i]
    known.append(min_i)
    for i in range(n): #for every vertex i that
        w = g[gn[min_i]].get(gn[i],None)
        # w = g[gn[min_i]][gn[i]]
        if w and distance[i] > min + w:
            # adjacent to min_i(has weight > 0)
            distance[i] = min + w
            path[i] = min_i
print(known)
print(path)
print(g)
printPath(0,5,distance,path,gn)