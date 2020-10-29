
class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
    
    def __str__(self):
        return str(self.data)

class BST:
    def __init__(self):
        self.root = None
        self.breadthqueue = []
    def insert(self, data):
        dnode = Node(data)
        if self.root is None:
            self.root = dnode
        else:
            fp = None
            p = self.root
            while p :
                fp = p
                p = p.left if data<p.data else p.right
            if data < fp.data:
                fp.left = dnode
            else:
                fp.right = dnode
        self.breadthqueue.append(dnode)
    def inOrder(self):
        print("Inorder : ",end = "")
        self._inOrder(self.root)
        print()
    def _inOrder(self,root):
        if root:
            self._inOrder(root.left)
            print(root.data,end = " ")
            self._inOrder(root.right)

    def preOrder(self):
        print("Preorder : ",end = "")
        self._preOrder(self.root)
        print()
    def _preOrder(self,root):
        if root:
            print(root.data,end = " ")
            self._preOrder(root.left)
            self._preOrder(root.right)
    
    def postOrder(self):
        print("Postorder : ",end = "")
        self._postOrder(self.root)
        print()
    def _postOrder(self,root):
        if root:
            self._postOrder(root.left)
            self._postOrder(root.right)
            print(root.data,end = " ")
    def breadthOrder(self):
        print("Breadth : ",end = "")
        queue = []
        queue.append(self.root)
        while len(queue)>0:
            node = queue.pop(0)
            print(node.data,end = " ")
            if node.left is not None:
                queue.append(node.left)
            if node.right is not None:
                queue.append(node.right)
    def printTree(self, node, level = 0):
        if node != None:
            self.printTree(node.right, level + 1)
            print('     ' * level, node)
            self.printTree(node.left, level + 1)
    

        

T = BST()
inp = [int(i) for i in input('Enter Input : ').split()]
for i in inp:
    T.insert(i)
T.preOrder()
T.inOrder()
T.postOrder()
T.breadthOrder()
# print()
# T.printTree(T.root)