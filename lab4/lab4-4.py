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
act = ["Eat","Game","Learn","Movie"]
site = ["Res.","ClassR.","SuperM.","Home"]
quote = ["Yes! You're my love! : Score is ","Umm.. It's complicated relationship! : Score is ","No! We're just friends. : Score is "]
def showqueue(q):
    qout = ""
    qs = Queue(q.item.copy())
    for _ in range(int(qs.size()/2)):
        qout+=str(qs.deQueue())+":"+str(qs.deQueue())+", "
    
    return qout[:-2]
def showact(q):
    qout = ""
    qs = Queue(q.item.copy())
    for _ in range(int(qs.size()/2)):
        qout+=act[qs.deQueue()]+":"+site[qs.deQueue()]+", "
    return qout[:-2]
def result(q1,q2):
    rtype = -1
    score = 0
    for _ in range(int(q1.size()/2)):
        q1a = q1.deQueue()
        q2a = q2.deQueue()
        q1b = q1.deQueue()
        q2b = q2.deQueue()
        if q1a == q2a :
            if q1b == q2b :
                score+=4
            else:
                score+=1  
        elif q1b == q2b :
            score+=2
        else :
            score-=5
    if score>=7:
        rtype = 0
    elif 0<score<7:
        rtype = 1
    else:
        rtype = 2
    return quote[rtype]+str(score)+"."
qme = Queue()
qu = Queue()
x = input("Enter Input : ").split(",")
for i in x:
    y1,y2 = i.split()
    qme.enQueue(int(y1.split(":")[0]))
    qme.enQueue(int(y1.split(":")[1]))
    qu.enQueue(int(y2.split(":")[0]))
    qu.enQueue(int(y2.split(":")[1]))
# print(qme.item,qu.item)
print("My   Queue =",showqueue(qme))
print("Your Queue =",showqueue(qu))
print("My   Activity:Location =",showact(qme))
print("Your Activity:Location =",showact(qu))
print(result(qme,qu))