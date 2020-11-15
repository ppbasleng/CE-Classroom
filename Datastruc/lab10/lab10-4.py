class hash:

    def __init__(self,tablesize,maxcolision,threshold):
        self.tablesize = tablesize
        self.table = [None for i in range(self.tablesize)]
        self.maxcolision = maxcolision
        self.threshold = threshold
        self.item = 0
    def __str__(self):
        sout = ""
        for i in range(len(self.table)):
            sout+="#"+str(i+1)+"	"+str(self.table[i])+"\n"
        return sout+"----------------------------------------"
    def rehashing(self):
        newsize = nextprime(self.tablesize*2)
        self.table.extend([None for i in range(self.tablesize,newsize)])
        self.tablesize = newsize
        
    def qprobe(self,data,f=0):
        if (self.item+1)/self.tablesize > self.threshold/100:
            print("****** Data over threshold - Rehash !!! ******")
            self.rehashing()
            self.qprobe(data)
        else:
            index = (data+f**2)%self.tablesize
            if self.table[index] == None:
                self.table[index] = data
                self.item+=1
                print(self)
            else:
                print("collision number {0} at {1}".format(f+1,index))
                if f+1>=self.maxcolision:
                    print("****** Max collision - Rehash !!! ******")
                    self.rehashing()
                    self.qprobe(data)
                else:
                    self.qprobe(data,f+1)
def isprime(n,a=2):
    if n<=1:
        return
    else:
        if a>=n:
            return True
        elif n==2:
            return True
        elif n%a == 0:
            return False
        else:
            return isprime(n,a+1)
def nextprime(n):
    if not isprime(n+1):
        return nextprime(n+1)
    else:
        return n+1
        
print(" ***** Rehashing *****")
inp = input("Enter Input : ").split("/")

h = hash(int(inp[0].split()[0]),int(inp[0].split()[1]),int(inp[0].split()[2]))
print("Initial Table :\n",h,sep = "")
for i in inp[1].split():
    print("Add :",int(i))
    h.qprobe(int(i))