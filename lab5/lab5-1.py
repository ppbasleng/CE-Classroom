class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def __str__(self):
        if self.isEmpty():
            return "Empty"
        cur, s = self.head, str(self.head.value) + " "
        while cur.next != None:
            s += str(cur.next.value) + " "
            cur = cur.next
        return s

    def isEmpty(self):
        return self.head == None

    def append(self, item):
        if self.head != None:
            p = self.head
            while p.next != None:
                p=p.next
            np = Node(item)
            p.next = np
        else :
            self.head = Node(item)

    def addHead(self, item):
        tmphead = self.head
        self.head = Node(item)
        self.head.next = tmphead

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
        if pos>self.size()-1 or pos <0:
            return "Out of Range"
        if pos == 0:
            self.head = self.head.next
            return "Success"
        if self.head != None:
            p = self.head
            b = None
            for _ in range(pos):
                b = p
                p = p.next
            b.next = p.next
            return "Success"
        return "Out of Range"
        

L = LinkedList()
inp = input('Enter Input : ').split(',')
for i in inp:
    if i[:2] == "AP":
        L.append(i[3:])
    elif i[:2] == "AH":
        L.addHead(i[3:])
    elif i[:2] == "SE":
        print("{0} {1} in {2}".format(L.search(i[3:]), i[3:],L))
    elif i[:2] == "SI":
        print("Linked List size = {0} : {1}".format(L.size(), L))
    elif i[:2] == "ID":
        print("Index ({0}) = {1} : {2}".format(i[3:], L.index(i[3:]), L))
    elif i[:2] == "PO":
        before = "{}".format(L)
        k = L.pop(int(i[3:]))
        print(("{0} | {1}-> {2}".format(k, before, L)) if k == "Success" else ("{0} | {1}".format(k, L)))
print("Linked List :", L)