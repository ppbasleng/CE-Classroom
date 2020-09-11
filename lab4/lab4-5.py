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
heat,freeze,mistake = 0,0,0
def checkbomb(bq,t):
    global heat,mistake,freeze
    while "( )b" in bq.item:
        bq.item.remove("( )b")
    i = 0
    while i in range(bq.size()-2):
        if  bq.item[i][0] == bq.item[i+1][0] == bq.item[i+2][0]:
            # print(len(bq.item[i]),len(bq.item[i+1]),len(bq.item[i+2]))
            if len(bq.item[i])+len(bq.item[i+2])+len(bq.item[i+2])!=3:
                mistake+=1
            else:
                if t == 0:
                    heat+=1
                elif t ==1:
                    freeze+=1
            # print("del",bq.item[i:i+3])
            # del bq.item[i:i+3]
            for _ in range(3):
                bq.item.pop(i)
            i-=1
        i+=1
    
def TENET(r,b):
    global freeze
    buffer = 0
    temp = ""
    newr = Queue()
    for i in r.item:
        if temp == i and buffer == 1:
            bbomb = "( )"
            for j in range(len(b.item)-2):
                if  b.item[j] == b.item[j+1] == b.item[j+2]:
                    bbomb = b.item[j]
                    # del b.item[j:j+3]
                    for _ in range(3):
                        b.item.pop(j)
                    freeze +=1
                    break
            newr.enQueue(bbomb+"b")
            temp = bbomb
        if temp == i:
            buffer = 1
        else:
            buffer = 0
        
        newr.enQueue(i)
        temp = i
    # print(newr.item)
    checkbomb(newr,0)
    # print(newr.item)
    # print(b.item)
    checkbomb(b,1)
    # print(b.item)
    return newr  


r,b = input("Enter Input (Red, Blue) : ").split()
r = Queue(list(r))
b = Queue(list(b[::-1]))
# print(r.item,b.item)
r = TENET(r,b)
# print("heat",heat,"Freeze",freeze,"mistake",mistake)
rout = ""
for i in r.item:
    rout+=i[0]
bout = "".join(b.item)
if rout == "":
    rout = "ytpmE"
if bout == "":
    bout = "Empty"
print("Red Team : \n",r.size(),'\n',rout[::-1],'\n',heat," Explosive(s) ! ! ! (HEAT)",sep="")
if mistake>0:
    print("Blue Team Made (a) Mistake(s)",mistake,"Bomb(s)")
print("----------TENETTENET----------")
print(": maeT eulB\n",b.size(),'\n',bout[::-1],"\n","(EZEERF) ! ! ! (s)evisolpxE ",freeze,sep="")


