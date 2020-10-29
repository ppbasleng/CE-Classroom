class Node(object): 
    def __init__(self, data): 
        self.data = data 
        self.left = None
        self.right = None

    def __str__(self):
        return str(self.data)
  
class AVL_Tree(object): 
    def height(self,root):
        if not root:
            return -1
        else:
            hl = self.height(root.left)
            hr = self.height(root.right)
            if hl>hr:
                return hl+1
            else:
                return hr+1
    def insert(self,root,data):
        if not root:
            return Node(data)
        elif data<root.data:
            root.left = self.insert(root.left,data)
        else :
            root.right = self.insert(root.right,data)
        balance = self.getBalance(root)
        if abs(balance)>=2 : print("Not Balance, Rebalance!")
        
        if balance>1 and data<root.left.data:
            return self.rRotate(root)
        if balance<-1 and data>root.right.data:
            return self.lRotate(root)
        if balance>1 and data>root.left.data:
            root.left = self.lRotate(root.left)
            return self.rRotate(root)
        if balance<-1 and data<root.right.data:
            root.right = self.rRotate(root.right)
            return self.lRotate(root)
        return root
    def lRotate(self,root):
        newr = root.right
        child = newr.left
        newr.left = root
        root.right = child
        return newr
    def rRotate(self,root):
        newr = root.left
        child = newr.right
        newr.right = root
        root.left = child
        return newr
    def getBalance(self, root): 
        if not root: 
            return 0
  
        return self.height(root.left) - self.height(root.right) 
    
def printTree90(node, level = 0):
    if node != None:
        printTree90(node.right, level + 1)
        print('     ' * level, node)
        printTree90(node.left, level + 1)
  
myTree = AVL_Tree() 
root = None

data = input("Enter Input : ").split()
for e in data:
    print("insert :",e)
    root = myTree.insert(root, int(e))
    printTree90(root)
    print("===============")