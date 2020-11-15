class Data:
    def __init__(self, key, value):
        self.key = key
        self.value = value

    def __str__(self):
        return "({0}, {1})".format(self.key, self.value)

class hash:

    def __init__(self,tablesize,maxcolision):
        self.tablesize = tablesize
        self.table = [None for i in range(self.tablesize)]
        self.maxcolision = maxcolision
        self.full = False
    def __str__(self):
        sout = ""
        for i in range(len(self.table)):
            sout+="#"+str(i+1)+"	"+self.table[i].__str__()+"\n"
        return sout+"---------------------------"
    def hashing(self,data):
        if not self.full and None in self.table:
            asum = 0
            for i in data.key:
                asum+= ord(i)
            self.qprobe(asum,data)
            print(self)
        elif not self.full:
            print("This table is full !!!!!!")
            self.full = True
        
    def qprobe(self,asum,data,f=0):
        index = (asum+f**2)%self.tablesize
        if self.table[index] == None:
            self.table[index] = data
        else:
            print("collision number {0} at {1}".format(f+1,index))
            if f+1>=self.maxcolision:
                print("Max of collisionChain")
            else:
                self.qprobe(asum,data,f+1)

        
print(" ***** Fun with hashing *****")
inp = input("Enter Input : ").split("/")

h = hash(int(inp[0].split()[0]),int(inp[0].split()[1]))

for i in inp[1].split(","):
    h.hashing(Data(i.split()[0],i.split()[1]))