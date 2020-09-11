class node:
    def __init__(self,data,next = None):
        self.data = data
        if next == None:
            self.next = None
        else:
            self.next = next
    def __str__(self):
        return self.data
    def getData(self):
        return self.data
    def getNext(self):
        return self.next
    def setData(self,data):
        self.data = data
    def setNext(self,next):
        self.next = next
class mylist:
    def __init__(self,head = None):
        self.head = head
    def __str__(self):
        if not self.isEmpty():
            p = self.head
            strout = "["
            while p.next != None:
                strout+=p.data+','
                p = p.getNext()
            strout+=p.data+"]"
            return  strout
        else:
            return '[]'
    def size(self):
        counter = 0
        if self.head !=None:
            p = self.head
            counter = 1
            while p.next != None:
                p = p.next
                counter+=1
        return counter
    def isEmpty(self):
        return self.size() == 0
    def append(self,data):
        if not self.isEmpty():
            p = self.head
            while p.next != None:
                # print(p,"->",end="")
                p=p.getNext()
                # print(p)
            np = node(data)
            # print("change next",p)
            p.setNext(np)
        else :
            self.head = node(data)
            print("sh is",self.head)
    def addHead(self,data):
        self.head = node(data,self.head)
        print("sh is",self.head)
    def isIn(self,data):
        p = self.head
        while p.next != None:
            if p.data == data:
                return True
            p = p.next
        else:
            if p.data == data:
                return True
        return False
    def before(self,data):
        p = self.head
        b = None
        while p.data != data:
            b = p
            p = p.next
        return b
    def remove(self,data):
        if self.head.data == data:
            # print("first")
            p = self.head
            self.head = self.head.next
            return p
        elif self.head.data != data:
            p = self.head
            # print("mid")
            while p.next != None:
                p = p.next
                if p.data == data:
                    self.before(p.data).next = p.next
                    return p

    def removeTail(self):
        p = self.head
        while p.next != None:
            p = p.next
        self.before(p.data).next = None
        return p
    def removeHead(self):
        p = self.head
        self.head = self.head.next
        return p
        
               
n3 = node("C") 
n2 = node("B",n3)        
n1 = node("A",n2)
lst = mylist(n1)
print(lst)
lst.append("D")
print(lst)
print(lst.isEmpty())
lst.addHead("Z")
print(lst)
lst.append("a")
print(lst)
print(lst.isIn("Z"))
print(lst.before("B"))
print('remove',lst.remove("a"))
print(lst)
print("rmt",lst.removeTail())
print(lst)
print("rmh",lst.removeHead())
print(lst)

