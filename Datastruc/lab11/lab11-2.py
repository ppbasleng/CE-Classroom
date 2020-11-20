class Node:
    def __init__(self,data):
        self.data = data
        self.edge = []
    def __str__(self):
        return self.data
    def add_Edge(self,edge):
        self.edge.append(edge)
    def breath(self):
        print("Bredth First Traversals : ",end="")
        strout =""
        traversed = []
        queue = []
        queue.append(self)
        while len(queue)!=0:
            vertex = queue.pop(0)
            # print("get",vertex.data)
            if vertex not in traversed:
                traversed.append(vertex)
                strout += vertex.data+" "
                tmpl = []
                for i in vertex.edge:
                    tmpl.append(i)
                #     print("|",i.data,"|",end="")
                # print()
                tmpl.sort(key=lambda x: x.data, reverse=False)
                queue.extend(tmpl)
        print(strout[:-1])
    def depth(self):
        print("Depth First Traversals : ",end="")
        strout = ""
        traversed = []
        stack = []
        stack.append(self)
        while len(stack)!=0:
            vertex = stack.pop(-1)
            # print("get",vertex.data)
            if vertex not in traversed:
                traversed.append(vertex)
                strout+= vertex.data+" "
                tmpl = []
                for i in vertex.edge:
                    tmpl.append(i)
                #     print("|",i.data,"|",end="")
                # print()
                tmpl.sort(key=lambda x: x.data, reverse=True)
                stack.extend(tmpl)
        print(strout[:-1])
def addlink(a,b,g):
    if g.get(a,-1) ==-1:
        g[a] = Node(a)
    if g.get(b,-1) == -1:
        g[b] = Node(b)
    g.get(a).add_Edge(g.get(b))
    g.get(b).add_Edge(g.get(a))       

inp = input("Enter : ").split(",")
table = dict()
first = []
for i in inp:
    addlink(i.split()[0],i.split()[1],table)
    if i.split()[0] not in first:
        first.append(i.split()[0])
    if i.split()[1] not in first:
        first.append(i.split()[1])
first.sort()
table[first[0]].depth()
table[first[0]].breath()
