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

def match(a,b):
    #print(a,b)
    if a is "(":
        if b is ")":
            return True
    elif a is "[":
        if b is "]":
            return True
    elif a is "{":
        if b is "}":
            return True
    else:
        return False

str = input("Enter Input : ")
s = Stack()
error = 0
for i in range(len(str)):
    #print(s.item)
    if str[i] == '(' or str[i] == '[' or str[i] == '{':
        s.push(str[i])
        #print("push",str[i])
    elif str[i] == ')' or str[i] == ']' or str[i] == '}':
        error+=1
        # if(s.isEmpty()):
        #     error += 1 
        if not s.isEmpty():
            if match(s.peek(),str[i]) :
                s.pop()
                error -=1
if not s.isEmpty():
    #print(error)
    #print(s.item)
    error += len(s.item)
print(error)

if error == 0:
    print("Perfect ! ! !")