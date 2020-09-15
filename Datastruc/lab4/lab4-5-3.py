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

def showresult(r,b,heat,freeze,mistake):
    print("Red Team : \n",r.size(),'\n',"".join(reversed(r.item))  if r.size()!=0 else "Empty",'\n',heat," Explosive(s) ! ! ! (HEAT)",sep="")
    if mistake>0:
        print("Blue Team Made (a) Mistake(s)",mistake,"Bomb(s)")
    print("----------TENETTENET----------")
    print(": maeT eulB\n",b.size(),'\n',"".join(reversed(b.item)) if b.size() != 0 else "ytpmE","\n","(EZEERF) ! ! ! (s)evisolpxE ",freeze,sep="")   

def TENET(r,b):
    bombl = Queue()
    heat,freeze,mistake = 0,0,0
    newr = Queue()
    count = len(b.item)-2
    j= 0
    while j < count:
        if  b.item[j] == b.item[j+1] == b.item[j+2]:
            bombl.enQueue(b.item[j])
            # del b.item[j:j+3]
            for _ in range(3):
                b.item.pop(j)
                count-=1
            j-=1
            freeze +=1
        j+=1
    # print(bombl.item)
    for i in range(r.size()):
        
        newr.enQueue(r.item[i])
        # print("before",newr.item)
        if newr.size()>=3:
            if newr.item[-1]==newr.item[-2]==newr.item[-3]:
                if not bombl.isEmpty():
                    bombq = bombl.deQueue()
                    if bombq == newr.item[-1]:
                        mistake+=1
                        for _ in range(2):
                            newr.item.pop()
                    else :
                        newr.item.insert(-1,bombq)
                        
                else:
                    heat+=1
                    for _ in range(3):
                        newr.item.pop()
        # print("after",newr.item)           

    showresult(newr,b,heat,freeze,mistake)


r,b = input("Enter Input (Red, Blue) : ").split()
r = Queue(list(r))
b = Queue(list(b[::-1]))
# print(r.item,b.item)
TENET(r,b)
# print("heat",heat,"Freeze",freeze,"mistake",mistake)



