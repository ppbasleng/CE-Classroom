# Dijkstra's algorithm for shortest path
def printPath(start, toV, distance, path):
    print('v',start, ' to v', toV, sep = '',end=" : ")
    # print('\tShortest path =', distance[toV])
    # print('\tpath :', end = ' ' )
    pathout = ""
    p = path[toV]
    while p is not None:
        pathout = "v"+str(p)+"->"+pathout
        p = path[p]
    print(pathout[:-2])
       # 0 1 2 3 4 5 6
adj = [ [0,2,0,1,0,0,0], # 0
        [0,0,0,3,10,0,0], # 1
        [4,0,0,0,0,5,0], # 2
        [0,0,2,0,2,8,4], # 3
        [0,0,0,0,0,0,6], # 4
        [0,0,0,0,0,0,0], # 5
        [0,0,0,0,0,1,0]] # 6
n = 7 # total nodes
known = [] # เก็บเฉพาะ vertex ที่รู้ระยะสั้นที่สุดแล้ว
distance = [float('inf')]*n #set to infinity
path = [None]*n
# set start vertex
start = 0
distance[start] = 0
while len(known) != n:
    # greedy : find vertex of smallest distance
    min = float('inf')
    for i in range(n):
        if i not in known and distance[i] < min:
            min_i = i # index
            min = distance[i]
    known.append(min_i)
    for i in range(n): #for every vertex i that
        w = adj[min_i][i]
        if w and distance[i] > min + w:
            # adjacent to min_i(has weight > 0)
            distance[i] = min + w
            path[i] = min_i
toV = 5 # to vertex
printPath(start,toV, distance, path)