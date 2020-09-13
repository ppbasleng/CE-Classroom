class Node:
    def __init__(self, value):
        self.value = value
        self.next = None
        self.previous = None

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
inp = input('Enter Input : ').split(',')
for i in inp:
    if i[:2] == "AP":
        L.append(i[3:])
    elif i[:2] == "AH":
        L.addHead(i[3:])
    elif i[:2] == "SE":
        print("{0} {1} in {2}".format(L.search(i[3:]), i[3:], L))
    elif i[:2] == "SI":
        print("Linked List size = {0} : {1}".format(L.size(), L))
    elif i[:2] == "ID":
        print("Index ({0}) = {1} : {2}".format(i[3:], L.index(i[3:]), L))
    elif i[:2] == "PO":
        before = "{}".format(L)
        k = L.pop(int(i[3:]))
        print(("{0} | {1}-> {2}".format(k, before, L)) if k == "Success" else ("{0} | {1}".format(k, L)))
    elif i[:2] == "IS":
        data = i[3:].split()
        L.insert(int(data[0]), data[1])
print("Linked List :", L)
print("Linked List Reverse :", L.reverse())