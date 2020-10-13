class Node:
    def __init__(self, data, left = None, right = None):
        self.data = data
        self.left = None if left is None else left
        self.right = None if right is None else right
    
    def __str__(self):
        return str(self.data)

class EPT:
    operator = "+-*/"
    def __init__(self):
        self.root = None
    def postFix(self, Strin):
        stack = []
        while Strin != []:
            item = Strin.pop(0)
            # print(item)
            if item in self.operator:
                itemb = stack.pop(-1)
                itema = stack.pop(-1)
                self.root = Node(item,itema,itemb)
                stack.append(self.root)
            else :
                stack.append(Node(item)) 
            
            # print(stack)
    def inFix(self):
        print("Infix : ",end = "")
        self._inFix(self.root)
        print()
    def _inFix(self,root):
        if root:
            if root.left or root.right:
                print("(",end = "")
            self._inFix(root.left)
            print(root.data,end = "")
            self._inFix(root.right)
            if root.left or root.right:
                print(")",end = "")
    def preFix(self):
        print("Prefix : ",end = "")
        self._preFix(self.root)
        print()
    def _preFix(self,root):
        if root:
            print(root.data,end="")
            self._preFix(root.left)
            self._preFix(root.right)
    def printTree(self, node, level = 0):
        
        if node != None:
            self.printTree(node.right, level + 1)
            print('     ' * level, node)
            self.printTree(node.left, level + 1)

T = EPT()
inp = list(input("Enter Postfix : "))
T.postFix(inp)
print("Tree :")
T.printTree(T.root)
print("--------------------------------------------------")
T.inFix()
T.preFix()