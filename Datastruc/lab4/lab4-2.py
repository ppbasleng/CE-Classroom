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
qn = Queue()
qs = Queue()
x = input("Enter Input : ").split(",")
for i in x:
    if i.split()[0] == "EN":
        qn.enQueue(i.split()[1])
    elif i.split()[0] == "ES":
        qs.enQueue(i.split()[1])
    elif i.split()[0] == "D":
        if not qs.isEmpty():
            print(qs.deQueue())
        elif not qn.isEmpty():
            print(qn.deQueue())
        else:
            print("Empty")