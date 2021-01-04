
def add(a,b,w,graph,table):
    x = table.index(a)
    y = table.index(b)
    graph[x][y] = w
    return graph
def printg(graph):
    for i in graph:
        print(i)

# Dijkstra's algorithm for shortest path
def printPath(start, toV, distance, path,table):

    if path[toV] is None:
        print("Not have path :",table[start],"to",table[toV])

    else:
        pathout = table[toV]
        p = path[toV]
        while p is not None:
            pathout = table[p]+"->"+pathout
            p = path[p]
        print(table[start], ' to ', table[toV], sep = '',end=" : ")
        print(pathout)
def shortest(start,to,table):
    if start not in table or to not in table:
        print("Not have path :",start,"to",to)
    else:

        known = [] # เก็บเฉพาะ vertex ที่รู้ระยะสั้นที่สุดแล้ว
        distance = [float('inf')]*n #set to infinity
        path = [None]*n
        # set start vertex
        start = table.index(start)
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
                w = weight[min_i][i]
                if w and distance[i] > min + w:
                    # adjacent to min_i(has weight > 0)
                    distance[i] = min + w
                    path[i] = min_i
            print(distance)
            print(path)
        toV = table.index(to) # to vertex
        printPath(start,toV, distance, path,first)

inpall = input("Enter : ").split("/")
inp = inpall[0].split(",")
inp2 = inpall[1].split(",")
first = []
for i in inp:#scan first
    if i.split()[0] not in first:
        first.append(i.split()[0])
    if i.split()[2] not in first:
        first.append(i.split()[2])
first.sort()
# print(first)
n = len(first)
weight = [[0 for i in range(n)] for i in range(n)]
for i in inp:
    weight = add(i.split()[0],i.split()[2],int(i.split()[1]),weight,first)
    
# printg(weight)
# print(inp2)
for i in inp2:
    shortest(i.split()[0],i.split()[1],first)

