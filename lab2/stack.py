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
# s = Stack(['A','B','C'])
# print(s.item)
# s.push("D")
# print(s.item)
# print(s.size())
# print(s.isEmpty())
# print(s.pop())
# print(s.item)
# print(s.peek())
# l = []