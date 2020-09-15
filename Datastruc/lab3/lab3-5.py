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

        return self.item.pop()
    def peek(self):
        tmp = self.item[self.size()-1]
        return tmp
def turnBack(x):
    # print("turnback")
    counter = 0
    fcks = Stack()
    for i in x.item:
        fcks.push(i)
    if not fcks.isEmpty():
        counter = 1
    while fcks.size()>=2 :
        # print("fcksize :",fcks.size())
        a = fcks.pop()
        b = fcks.peek()
        # print("A,B:",a,b)
        if a<b :
            counter+=1 
        else :
            fcks.pop()
            fcks.push(a)    
    return counter
def hypnotize(item):
    # print("hypnotizing: ",item)
    for i in range(len(item)):
        if item[i]%2==0:
            item[i]-=1
            if item[i] < 1 :
                item[i] = 1
        elif item[i]%2==1:
            item[i]+=2
    # print("hypnotized: ",item)

h= False
s = Stack()
lst = list(input("Enter Input : ").split(","))
# print(lst)
for i in lst:
    if i.split()[0] == 'A':
        if h == False:
            # print("nothypno")
            s.push(int(i.split()[1]))
        else:
            # print("hypnoed")
            c = int(i.split()[1])
            if c%2==0:
                c-=1
                if c < 1 :
                    c = 1
            elif c%2==1:
                c+=2
            s.push(c)

    elif i.split()[0] == 'B':
        a = turnBack(s)
        print(a)
    elif i.split()[0] == 'S':
        # if h ==False :
        #     h= True
            hypnotize(s.item)