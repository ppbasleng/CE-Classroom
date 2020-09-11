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
class StackCalc:
    d = ["+","-","*","/","DUP","POP"]
    def __init__(self):
        self.s = Stack()
        self.error = 0
    def run(self,arg):
        for i in range(len(arg)):
            if  arg[i].isdigit() :
                self.s.push(int(arg[i]))
            elif arg[i] in self.d:
                if arg[i] is self.d[0] :
                    a=self.s.pop()
                    b=self.s.pop()
                    self.s.push(a+b)
                elif arg[i] is self.d[1] :
                    a=self.s.pop()
                    b=self.s.pop()
                    self.s.push(a-b)
                elif arg[i] is self.d[2] :
                    a=self.s.pop()
                    b=self.s.pop()
                    self.s.push(a*b)
                elif arg[i] is self.d[3] :
                    a=self.s.pop()
                    b=self.s.pop()
                    self.s.push(int(a/b))
                elif arg[i] == self.d[4] :
                    self.s.push(self.s.peek())
                elif arg[i] == self.d[5] :
                    # print("POP!!")
                    self.s.pop()
            else:
                
                self.error = arg[i]
                break
    
    def getValue(self):
        if not self.s.isEmpty():
            return self.s.peek()
        elif self.error == 0 :
            return 0
        else :
            return "Invalid instruction: "+self.error
arg = list(input("* Stack Calculator *\nEnter arguments : ").split())
machine = StackCalc()
machine.run(arg)
print(machine.getValue())