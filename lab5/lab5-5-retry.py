import math
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
    return strout[:-1]

def SIZE(head):
    counter = 0
    if head !=None:
        p = head
        while p != None:
            p = p.next
            counter+=1
        
    return counter

def scramble(head, b, r, size):
    #BottomUp Started
    bdown,btop = Node(None),Node(None)
    b0 = head
    temp1,temp2 = bdown,btop
    counter = 0
    while counter<size: 
        # print("::",(counter+1)*100/size,"/",b)
        if ((counter+1)*100)/size<=b:
            temp2.next = b0
            temp2 = temp2.next
        elif ((counter+1)*100)/size>b:
            temp1.next = b0
            temp1 = temp1.next
        b0 = b0.next
        counter+=1
        temp1.next = btop.next
        temp2.next = None
    head = bdown.next
    print("BottomUp {0} % : {1}".format(format(b, '.3f'),printLL(head)))

    #riffle Started
    riffletime = 0
    rsum = Node(None)
    rtemp = rsum
    rl,rr = Node(None),Node(None)
    r0 = head
    templ,tempr = rl,rr
    counter = 0
    rehand = 0
    while counter<size:
        if ((counter+1)*(100/size))<=r:
            # print(":A:",r0,((counter+1)*(100/size)),"/",r)
            templ.next = r0
            templ = templ.next
        elif ((counter+1)*(100/size))>r:
            # print(":B:",r0,((counter+1)*(100/size)),"/",r)
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
        riffletime+=2
    if rl != None:
        rtemp.next = rl
        rehand =1
    elif rr != None:
        rtemp.next = rr
        rehand = 0
    head = rsum.next
    print("Riffle {0} % : {1}".format(format(r, '.3f'),printLL(head)))

    
    #deriffle Started
    rsum = Node(None)
    rtemp = rsum
    rl,rr,rre = Node(None),Node(None),Node(None)
    r0 = head
    templ,tempr = rl,rr
    counter = 0
    # print(riffletime)
    while counter<riffletime:
        if counter%2==0:
            # print(counter,":A:",(counter+1)*100/size,r0.value)
            templ.next = r0
            templ = templ.next
            r0 = r0.next
            counter+=1
        elif counter%2!=0:
            # print(counter,":B:",(counter+1)*100/size,r0.value)
            tempr.next = r0
            tempr = tempr.next
            r0 = r0.next
            counter+=1
    # print("remainder:",r0,"remaining in hand:",rehand)
        
    if riffletime ==0:
        rl.next = head
    elif rehand == 0:
        rre.next = r0
        tempre = rre
        while tempre.next!=None:
            tempre = tempre.next
        if rre.next !=None:
            templ.next = rr.next
            tempr.next = rre.next
        else:
            templ.next = rr.next
        tempre.next = None    
    elif rehand == 1:
        rre.next = r0
        tempre = rre
        while tempre.next!=None:
            tempre = tempre.next
        if rre.next !=None:
            templ.next = rre.next
            tempre.next = rr.next
        else:
            templ.next = rr.next
        tempr.next = None    
    # elif r<50 or (r==50 and size%2!=0):
    #     # print("case1")
    #     rre.next = r0
    #     tempre = rre
    #     while tempre.next!=None:
    #         tempre = tempre.next
    #     if rre.next !=None:
    #         templ.next = rr.next
    #         tempr.next = rre.next
    #     else:
    #         templ.next = rr.next
    #     tempre.next = None    
    # elif r>=50 or (r==50 and size%2==0):
    #     # print("case2")
    #     rre.next = r0
    #     tempre = rre
    #     while tempre.next!=None:
    #         tempre = tempre.next
    #     if rre.next !=None:
    #         templ.next = rre.next
    #         tempre.next = rr.next
    #     else:
    #         templ.next = rr.next
    #     tempr.next = None   
    head = rl.next
    print("Deriffle {0} % : {1}".format(format(r, '.3f'),printLL(head)))

    #Debottomup Started
    bdown,btop = Node(None),Node(None)
    b0 = head
    
    temp1,temp2 = bdown,btop
    counter = 0
    while counter<size: 
        
        if ((counter)*100/size)<100-b:
            # print("::",math.floor((counter)*100/size),"/",100-b,b0,"Left")
            temp2.next = b0
            temp2 = temp2.next
        elif ((counter)*100/size)>=100-b:
            # print("::",math.floor((counter)*100/size),"/",100-b,b0,"Right")
            temp1.next = b0
            temp1 = temp1.next
        b0 = b0.next
        counter+=1
    temp1.next = btop.next
    temp2.next = None
    head = bdown.next
    print("Debottomup {0} % : {1}".format(format(b, '.3f'),printLL(head)))


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
    