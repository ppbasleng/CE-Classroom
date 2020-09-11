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
def encodemsg(q1,q2):
    q2n = Queue(q2.item.copy())
    for _ in range(q1.size()):
        a = ord(q1.deQueue())
        b = q2n.deQueue()
        # print(a+b,chr(a+b),a,b)
        if (65<=a<=90 and a+b>90) or (97<=a<=122 and a+b>122):
            q1.enQueue(chr(a+b-26))
        else:
            q1.enQueue(chr(a+b))
        q2n.enQueue(b)
    return q1.item
        
def decodemsg(q1,q2):
    q2n = Queue(q2.item.copy())
    for _ in range(q1.size()):
        a = ord(q1.deQueue())
        b = q2n.deQueue()
        # print(a-b,chr(a-b),a,b)
        if (65<=a<=90 and a-b<65) or (97<=a<=122 and a-b<97):
            q1.enQueue(chr(a-b+26))
        else:
            q1.enQueue(chr(a-b))
        q2n.enQueue(b)
    return q1.item
q1 = Queue()
q2 = Queue()
x1,x2 = input("Enter String and Code : ").split(",")
for i in x1:
    # print(i,ord(i))
    if 65<=ord(i)<=90 or 97<=ord(i)<=122:
        q1.enQueue(i)
for i in x2:
    q2.enQueue(int(i))
# print(q1.item,q2.item)
print("Encode message is : ",encodemsg(q1,q2))
print("Decode message is : ",decodemsg(q1,q2))