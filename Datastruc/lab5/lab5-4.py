class Node:
    def __init__(self, value):
        self.value = value
        self.next = None
        self.previous = None
    def __str__(self):
        return self.value
class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def __str__(self):
        if self.isEmpty():
            return "Empty"
        cur, s = self.head, str(self.head.value) + " "
        while cur.next != None:
            s += str(cur.next.value) + " "
            cur = cur.next
        return s

    def reverse(self):
        if self.isEmpty():
            return "Empty"
        cur, s = self.tail, str(self.tail.value) + " "
        while cur.previous != None:
            s += str(cur.previous.value) + " "
            cur = cur.previous
        return s

    def isEmpty(self):
        return self.head == None

    def append(self, item):
        if self.tail != None:
            p = self.head
            while p.next != None:
                p=p.next
            np = Node(item)
            np.previous = p
            p.next = np
            self.tail = np
        else :
            n = Node(item)
            self.head = n
            self.tail = n

    def idtoNode(self,pos):
        if pos>self.size():
            return None
        if pos == 0:
            return self.head
        elif pos >0:
            p = self.head
            counter = 0
            while p.next!= None:
               counter+=1
               p = p.next
               if counter == pos:
                   return p
        elif pos<0:
            p = self.tail
            counter = 0
            while p.previous!= None:
                counter-=1
                p = p.previous
                if counter == pos:
                    print("idtonode:",p.value)
                    return p
               

    def addHead(self, item):
        if self.head != None:
            tmphead = self.head
            self.head = Node(item)
            self.head.next = tmphead
            tmphead.previous = self.head
        else :
            n = Node(item)
            self.head = n
            self.tail = n

    def insert(self, pos, item):

        if pos ==0 or self.head == None or self.tail == None:
            self.addHead(item)
        elif pos>0:
            counter = 0
            if self.head != None:
                b = None
                p = self.head
                while p != None:
                    if counter == pos:
                        newp = Node(item)
                        b.next = newp
                        newp.previous = b
                        newp.next = p
                        p.previous = newp
                        break
                    if counter < pos:
                        b = p
                        p = p.next
                    counter+=1
                else:
                    self.append(item)
        elif pos<0:
            counter = 0
            if self.tail != None:
                b = None
                p = self.tail
                while p != None:
                    if counter == pos:
                        newp = Node(item)
                        b.previous = newp
                        newp.next = b
                        newp.previous = p
                        p.next = newp
                        break
                    if counter > pos:
                        b = p
                        p = p.previous
                    counter-=1
                else:
                    self.addHead(item)

    def search(self, item):
        p = self.head
        while p != None:
            if p.value == item:
                return "Found"
            p = p.next
        return "Not Found"

    def index(self, item):
        counter = 0
        p = self.head
        while p != None:
            if p.value == item:
                return counter
            p = p.next
            counter+=1
        return -1

    def size(self):
        counter = 0
        if self.head !=None:
            p = self.head
            while p != None:
                p = p.next
                counter+=1
        return counter

    def pop(self, pos):
        if abs(pos)>self.size():
            return "Out of Range"
        datnode = self.idtoNode(pos)
        if self.head == None or self.tail == None:
            return "Out of Range"
        if datnode == self.head:
            self.head = self.head.next
            if self.head!=None:
                self.head.previous = None
            return "Success"
        elif datnode == self.tail:
            self.tail = self.tail.previous
            if self.tail!=None:
                self.tail.next = None        
            return "Success"
        else:
            datnode.previous.next = datnode.next
            datnode.next.previous = datnode.previous
            return "Success"
            

L = LinkedList()
L.append("|")
cursorindex = L.index("|")
inp = input('Enter Input : ').split(',')
for i in inp:
    if i.split()[0] == "I":
        L.insert(cursorindex,i[2:])
        cursorindex = L.index("|")
    elif i.split()[0] == "L":
        if cursorindex>0:
            L.pop(cursorindex)
            L.insert(cursorindex-1,"|")
            cursorindex = L.index("|")
            
    elif i.split()[0] == "R":
        if cursorindex<L.size()-1:
            L.pop(cursorindex)
            L.insert(cursorindex+1,"|")
            cursorindex = L.index("|")
    elif i.split()[0] == "B":
        datnode = L.idtoNode(cursorindex-1)
        # print(datnode)
        if datnode != None:
            L.pop(cursorindex-1)
        cursorindex = L.index("|")
    elif i.split()[0] == "D":
        datnode = L.idtoNode(cursorindex+1)
        # print(datnode)
        if datnode != None:
            L.pop(cursorindex+1)
        cursorindex = L.index("|")
print(L)
