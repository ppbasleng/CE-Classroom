class Node:

    def __init__(self, data): 

        self.data = data  

        self.left = None  

        self.right = None 

        self.level = None 



    def __str__(self):

        return str(self.data) 



class Tree:

    def __init__(self): 

        self.root = None

        self.num = 0



    def insert(self, val):  

        if self.root == None:

            self.root = Node(val)

            self.num += 1

        else:

            h = height(self.root)

            max_node = pow(2,h+1)-1

            current = self.root

            if self.num+1 > max_node:

                while(current.left != None):

                    current = current.left

                current.left = Node(val)

                self.num+=1

            elif self.num+1 == max_node:

                while(current.right != None):

                    current = current.right

                current.right = Node(val)

                self.num+=1

            else:

                # print(max_node-((max_node-(pow(2,h)-1))/2))

                if self.num+1 <= max_node-((max_node-(pow(2,h)-1))/2):

                    insert_subtree(current.left,self.num - round(pow(2,h)/2),val)

                else:

                    insert_subtree(current.right,self.num - pow(2,h),val)

                self.num+=1

                    

def insert_subtree(r,num,val):

    if r != None:

        h = height(r)

        max_node = pow(2,h+1)-1

        current = r

        if num+1 > max_node:

            while(current.left != None):

                current = current.left

            current.left = Node(val)

            return

        elif num+1 == max_node:

            while(current.right != None):

                current = current.right

            current.right = Node(val)

            return

        if num+1 <= max_node-((max_node-(pow(2,h)-1))/2):

            insert_subtree(current.left,num - round(pow(2,h)/2),val)

        else:

            insert_subtree(current.right,num - pow(2,h),val)

    else:

        return



def height(root):

    if root == None:

        return -1

    else:

        left = height(root.left)

        right = height(root.right)

        if left>right:

            return left + 1

        else:

            return right + 1

                       

def printTree90(node, level = 0):

    if node != None:

        printTree90(node.right, level + 1)

        print('     ' * level, node)

        printTree90(node.left, level + 1)
def sum(root):
    if not root:
        return 0
    else:
        return root.data + sum(root.left) + sum(root.right)
def roughtree(root):
    if root.left and root.right:
        root.left = roughtree(root.left)
        # print("phase1")
        root.right = roughtree(root.right)
        # print("phase2")
        if root.left.data>=root.right.data:
            root.data = root.right.data
            root.left.data -= root.right.data
            root.right.data = 0
            
        else:
            root.data = root.left.data
            root.right.data -= root.left.data
            root.left.data = 0
            
            # print("phase3")
        return root
    else:
        return root
tree = Tree()

nodenum,data = input("Enter Input : ").split("/")
data = data.split(" ")
# print(data)
if int(nodenum)/2+1<len(data):
    print("Incorrect Input")
else:
    for i in range(0,int(nodenum)-len(data)):
        tree.insert(0)
    for e in data:
        tree.insert(int(e))

    # printTree90(tree.root)
    # print(sum(tree.root))
    tree.root = roughtree(tree.root)
    # printTree90(tree.root)
    print(sum(tree.root))