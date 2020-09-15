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
x = input("Enter Infix : ")
xout = ""
a = "*/"
b = "+-"
c = "()"
d = "^"
s = Stack()
for i in x:
    if i in b:
        if not s.isEmpty():
            if s.peek() in a:
                while not s.isEmpty():
                    xout+=s.pop()
                    if s.isEmpty() or s.peek() is c[0]:
                        break   
            elif s.peek() is c[0]:
                pass
            else:
                xout+=s.pop()    
        s.push(i)
    elif i in a:
        if not s.isEmpty():
            if s.peek() in d:
                while not s.isEmpty():
                    xout+=s.pop()
                    if s.isEmpty() or s.peek() is c[0]:
                        break        
            elif s.peek() in a:
                xout+=s.pop()  
        s.push(i)
    elif i in d:
        s.push(i)
    elif i == c[0]:
        s.push(i)
        # print(s.item)
    elif i == c[1]:
        # print(s.item)
        while s.peek() is not c[0] and not s.isEmpty():
            xout+=s.pop()
            # print(xout)
            if s.peek() == c[0]:
                s.pop()
                break
    else:
        xout+=i
    # print(xout)
while not s.isEmpty():
    xout+=s.pop()
print("Postfix :",xout)