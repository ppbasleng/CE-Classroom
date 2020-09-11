from collections import deque
class Queue:
    def __init__(self,list = None):
        if list == None:
            self.items = deque()
        else :
            self.items = deque(list)
    def enQueue(self,i):
        self.items.append(i)
    def size(self): 
        return len(self.items)

    def isEmpty(self):
        return len(self.items)==0
    def deQueue(self):
        return self.items.popleft()
