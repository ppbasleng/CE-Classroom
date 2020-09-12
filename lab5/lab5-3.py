class node:
    def __init__(self,data,next = None ):
        ### Code Here ###
        self.value = data
        self.next = None
    def __str__(self):
        ### Code Here ###
        return self.value

def createList(l=[]):
    ### Code Here ###
    for i in range(len(l)):
        l[i] = node(l[i])
        if i > 0:
            l[i-1].next = l[i]
    return l[0]

def printList(H):
    ### Code Here ###
    p = H
    strout = ""
    while p != None:
        strout+= str(p)+" "
        p = p.next
    print(strout)

def mergeOrderesList(p,q):
    ### Code Here ###
    mnode = node(None)
    mp = mnode
    while p != None and q != None:
        df = int(p.value) - int(q.value)
        # print(p.value,q.value,df)
        if df < 0:
            mp.next = p
            p = p.next
        else:
            mp.next = q
            q = q.next
        mp = mp.next
    if not p is None :
        mp.next = p
    elif not q is None :
        mp.next = q    
    
    return mnode.next  

#################### FIX comand ####################   
# input only a number save in L1,L2
L1,L2 = input("Enter 2 Lists : ").split()
L1,L2 = L1.split(","),L2.split(",")
LL1 = createList(L1)
LL2 = createList(L2)
print('LL1 : ',end='')
printList(LL1)
print('LL2 : ',end='')
printList(LL2)
m = mergeOrderesList(LL1,LL2)
print('Merge Result : ',end='')
printList(m)