class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

    def __str__(self):
        return str(self.value)

def createLL(l = []):
    for i in range(len(l)):
        l[i] = Node(l[i])
        if i > 0:
            l[i-1].next = l[i]
    return l[0]

def printLL(H):
    # Code Here
    p = H
    strout = ""
    while p != None:
        strout+= str(p)+" "
        p = p.next
    return strout

def SIZE(head):
    counter = 0
    if head !=None:
        p = head
        while p != None:
            p = p.next
            counter+=1
        
    return counter

def scramble(head, b, r, size):
    bdown,btop = Node(None),Node(None)
    b0 = head
    temp1,temp2 = bdown,btop
    counter = 0
    while counter<size: #BottomUp
        if counter*100/size<b:
            temp2.next = b0
            temp2 = temp2.next
        elif counter*100/size>=b:
            temp1.next = b0
            temp1 = temp1.next
        b0 = b0.next
        counter+=1
        temp1.next = btop.next
        temp2.next = None
    head = bdown.next
    print("BottomUp {0} % : {1}".format(format(b, '.3f'),printLL(head)))

    rsum = Node(None)
    rtemp = rsum
    rl,rr = Node(None),Node(None)
    r0 = head
    templ,tempr = rl,rr
    counter = 0
    while counter<size:
        if counter*100/size<r:
            templ.next = r0
            templ = templ.next
        elif counter*100/size>=r:
            templ.next = None
            tempr.next = r0
            tempr = tempr.next
        r0 = r0.next
        counter+=1
    rl,rr = rl.next,rr.next
    while rl != None and rr != None:
        # print("rl:",printLL(rl),"rr:",printLL(rr))
        rtemp.next = rl
        rtemp = rtemp.next
        rl = rl.next
        rtemp.next = rr
        rtemp = rtemp.next
        rr = rr.next
    if rl != None:
        rtemp.next = rl
    elif rr != None:
        rtemp.next = rr
    # print("end while")
    head = rsum.next
    print("Riffle {0} % : {1}".format(format(r, '.3f'),printLL(head)))
    # print("end fuction")

    




    



inp1, inp2 = input('Enter Input : ').split('/')
print('-' * 50)
h = createLL(inp1.split())
for i in inp2.split('|'):
    print("Start : {0}".format(printLL(h)))
    k = i.split(',')
    if k[0][0] == "B" and k[1][0] == "R":
        scramble(h, float(k[0][2:]), float(k[1][2:]), SIZE(h))
    elif k[0][0] == "R" and k[1][0] == "B":
        scramble(h, float(k[1][2:]), float(k[0][2:]), SIZE(h))
    print('-' * 50)
    