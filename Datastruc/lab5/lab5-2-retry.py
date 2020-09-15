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
        if self.head != None:
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
        if self.head != None:
            p = self.head
            while p != None:
                if p.value == item:
                    return "Found"
                p = p.next
            return "Not Found"
        else :
            return "Not Found"

    def index(self, item):
        if self.head != None:
            counter = 0
            p = self.head
            while p != None:
                if p.value == item:
                    return counter
                p = p.next
                counter+=1
            return -1
        else :
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
        elif pos == 0:
            if self.head != None:
                self.head = self.head.next
                if self.head != None:
                    self.head.previous = None
                return "Success"
            else:
                return "Out of Range"
        elif pos>0:
            if self.head != None:
                count = 0
                p = self.head
                b = None
                while p != None:
                    if count == pos:
                        if p == self.tail:
                            self.tail = b
                            b.next = None
                        else:
                            b.next = p.next
                            b.next.previous = b
                        return "Success"
                    b = p
                    p = p.next
                    count+=1
            return "Out of Range"
        elif pos<0:
            if self.tail != None:
                count = 0
                p = self.tail
                b = None
                while p != None:
                    # print("compare count:pos",count,pos)
                    if count == pos:
                        if p == self.tail:
                            # print("a")
                            self.tail = p.previous
                            self.tail.next = None
                        elif p == self.head:
                            # print("b")
                            self.head = p.next
                            self.head.previous = None
                        else:
                            # print("c")
                            b.previous = p.previous
                            b.previous.next = b
                        return "Success"
                    b = p
                    p = p.previous
                    count-=1
            return "Out of Range"


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