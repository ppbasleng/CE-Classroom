class Stack:
    sizeof = 0
    def __init__(self,list = None):
        if list == None:
            self.item =[]
        else :
            self.item = list
    def push(self,i):
        self.item.append(i)
    def size(self): 
        return len(self.item)

    def isEmpty(self):
        if self.size()==0:
            return True
        else:
            return False
    def pop(self):
        # tmp = self.item[self.size()-1]
        # del self.item[self.size()-1]
        # return tmp
        return self.item.pop()
    def peek(self):
        tmp = self.item[self.size()-1]
        return tmp
class bowl:
    def __init__(self,a,b):
        self.w = int(a)
        self.f = int(b)
x = list(input("Enter Input : ").split(","))
s = Stack()
bl = []
for i in range(len(x)):
    # print(x[i].split()[0],x[i].split()[1])
    bl.append(bowl(x[i].split()[0],x[i].split()[1]))
count = 0
while count<len(bl):
    if s.isEmpty() :
        # print("push1",bl[count].w,bl[count].f)
        s.push(bl[count])
    else :
        while bl[count].w>s.peek().w and not s.isEmpty():
            print(s.pop().f)
            if s.isEmpty():                
                # print("push2",bl[count])
                s.push(bl[count])
                break
        else:
            # print("push2",bl[count])
            s.push(bl[count])
    count+=1


