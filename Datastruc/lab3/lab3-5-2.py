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
def hypnotize(a):
    if a%2==0:
        a-=1
        if a<1:
            a=1
    elif a%2==1:
        a+=2
    return a
def turnBack(sin,h):
    counter = 1
    while sin.size()>=2 :
        if h == False:
            a = sin.pop()
            b = sin.peek()
        else:
            a = hypnotize(sin.pop())
            b = hypnotize(sin.peek())
        if a<b :
            counter+=1 
    return counter

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
        print(turnBack(s,h))
    elif i.split()[0] == 'S':
        h = True