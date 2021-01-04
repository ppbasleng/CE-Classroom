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
        if root is None:
            root = Node(data)
        else:
            fp = None
            p = root
            while p :
                fp = p
                p = p.left if data<p.data else p.right
            if data < fp.data:
                fp.left = Node(data)
            else:
                fp.right = Node(data)
            # printTree90(root)
            if not self.isBalance(root):
                print("Not Balance, Rebalance!")
                root = self.reBalance(root)
        return root
    def isBalance(self,root):
        out = self._isBalance(root)
        return True if out == 1 else False 
    def _isBalance(self,root):
        if not root :
            return 1
        else:
            if abs(self.height(root.left)-self.height(root.right))>=2:
                return 0
            else:
                return 1*self._isBalance(root.left)*self._isBalance(root.right)
    def reBalance(self,root):
        if not root :
            pass
            # print("basecase reached")
        else:
            print("recurrrr")
            printTree90(root)
            if self.height(root.left)-self.height(root.right)<=-2:   
                 
                root.right = self.reBalance(root.right)
                if self.height(root.left)-self.height(root.right)<=-2:
                    root = self.Rleftchild(root)
                elif self.height(root.left)-self.height(root.right)>=2:
                    root = self.Rrightchild(root)
                
            elif self.height(root.left)-self.height(root.right)>=2:    
                root.left = self.reBalance(root.left)
                if self.height(root.left)-self.height(root.right)<=-2:
                    root = self.Rleftchild(root)
                elif self.height(root.left)-self.height(root.right)>=2:
                    root = self.Rrightchild(root) 
            if not self.isBalance(root):
                root.right = self.reBalance(root.right)
                root.left = self.reBalance(root.left)
            return root
        
    def Rleftchild(self,root):
        newr = root.right
        root.right = newr.left
        newr.left = root

        return newr

    def Rrightchild(self,root):
        newr = root.left
        root.left = newr.right
        newr.right = root
        return newr

   
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