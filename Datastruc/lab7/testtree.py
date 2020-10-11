
class BST:
    class node:   
        def __init__(self, data, left = None, right = None):
            self.data = data
            self.left = None if left is None else left
            self.right = None if right is None else right
        def __str__(self):
            return str(self.data)
    def __init__(self,root = None):
        self.root = None if root is None else self.node(root)

    def addI(self,data):
        if self.root is None:
            self.root = self.node(data)
        else:
            fp = None
            p = self.root
            while p :
                fp = p
                p = p.left if data<p.data else p.right
            if data < fp.data:
                fp.left = self.node(data)
            else:
                fp.right = self.node(data)
    def inOrder(self):
        self._inOrder(self.root)
        print()
    def _inOrder(self,root):
        if root:
            self._inOrder(root.left)
            print(root.data,end = " ")
            self._inOrder(root.right)
    def add(self,data):
        self.root = self._add(self.root,data)
    def _add(self,root,data):
        if root is None:
            return self.node(data)
        else:
            if data<root.data:
                root.left = self._add(root.left,data)
            else:
                root.right = self._add(root.right,data)
    def printSideway(self):
        self._printSideway(self.root,0)
        print()
    def _printSideway(self,root,level):
        if root:
            self._printSideway(root.right,level+1)
            print("    "*level,root.data,sep = "")
            self._printSideway(root.left,level+1)

l = [int(e) for e in input("insert integers : ").split()]
print(l)
t = BST()
for ele in l:
    t.addI(ele)
t.inOrder()
t.printSideway()