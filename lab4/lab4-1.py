class Queue:
    def __init__(self,list = None):
        if list == None:
            self.item =[]
        else :
            self.item = list
    def enQueue(self,i):
        self.item.append(i)
    def size(self): 
        return len(self.item)

    def isEmpty(self):
        return len(self.item)==0
    def deQueue(self):
        return self.item.pop(0)
q= Queue()
x = input("Enter Input : ").split(",")
for i in x:
    if i.split()[0] == "E":
        q.enQueue(i.split()[1])
        print(q.size())
    elif i.split()[0] == "D":
        if not q.isEmpty():
            print(q.deQueue(),0)
        elif q.isEmpty():
            print(-1)
if not q.isEmpty():
    qout = ""
    while not q.isEmpty():
        qout+=q.deQueue()+" "
    print(qout)
else:
    print("Empty")