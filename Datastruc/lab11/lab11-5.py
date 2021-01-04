inpall = input("Enter Input : ").split("/")
inp = inpall[0].split(",")
path = [int(i) for i in inpall[1].split()]
first = []
l = []
for i in inp:#scan first
    if i.split()[0] not in first:
        first.append(int(i.split()[0]))
    if i.split()[1] not in first:
        first.append(int(i.split()[1]))
g = dict((i,[]) for i in first)

for i in inp:
    a = int(i.split()[0])
    b = int(i.split()[1])
    if b not in g[a]:
        g[a].append(b)
    if a not in g[b]:
        g[b].append(a)
for key in g.values():
    key.sort()
# print(g)

visitedList = [[]]

def depthFirst(graph, currentVertex, visited):
    visited.append(currentVertex)
    for vertex in graph[currentVertex]:
        if vertex not in visited:
            depthFirst(graph, vertex, visited.copy())
    visitedList.append(visited)
def filt(start,to,vlist):
    lst = []
    for i in vlist:
        if len(i)>1:
            if i[0] == start and i[-1] == to:
                lst.append(i)
    return lst
def possiblepath(a,b,lst):

    flst = filt(a,b,lst)
    if len(flst)>1:
        print(f"All possible path from {a} to {b} :")
        
        for i in flst:
            strout = ""
            for j in i:
                strout+=str(j)+" -> "
            print(strout[:-4])
    else:
        print(f"{a} can't go to {b}")
depthFirst(g, path[0], [])
visitedList.sort(key=lambda x: len(x), reverse=False)

possiblepath(path[0],path[1],visitedList)