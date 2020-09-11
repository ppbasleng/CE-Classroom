class Queue:
    def __init__(self,list = None):
        if list == None:
            self.item =[]
        else :
            self.item = list
    def enQueue(self,i):
        self.item.append(i)
    def size(self): 
        return len(self.item)

    def isEmpty(self):
        return len(self.item)==0
    def deQueue(self):
        return self.item.pop(0)
def TENET(r,b,freeze,heat,mistake):
    lst = []
    buffer=0
    tmp = ""
    for i in range(len(r)):
        if r[i] == tmp:
            buffer+=1
            if buffer ==2:
                for j in range(len(b)-2):
                    bbomb = ""
                    if b[j] == b[j+1] == b[j+2] :
                        freeze+=1
                        bbomb = b[j]
                        del b[j:j+3]
                        if bbomb == r[i]:
                            mistake+=1
                        lst.append(bbomb)
                        break
                buffer = 1
        else:
            buffer = 0
        tmp = r[i]
        # print("append",r[i])
        lst.append(r[i])
    # newr = []
    # i = 0
    # while i < len(r)-2:
        # print("token",r[i])
        # if r[i] == r[i+1] == r[i+2]:
        #     for j in range(len(b)-2):
        #         bomb = ""
        #         if b[j] == b[j+1] == b[j+2] :
        #             freeze+=1
        #             bbomb = b[j]
        #             del b[j:j+3]
        #             if bbomb == r[i]:
        #                 mistake+=1
        #                 r.insert(i+2,bbomb)
        #                 del r[i:i+3]
        #                 i-=1
        #             else:
        #                  r.insert(i+2,bbomb)
        #             break
        #     i+=1
        # print(i,len(r))
        # if i>len(r):
        #     print("not in range")
        #     break
    # print(lst)
    # print(b)
    lst,heat = checkbomb(lst,heat)
    b,freeze = checkbomb(b,freeze)
    display(lst,b,heat,freeze,mistake)
def checkbomb(lst,t):
    result = Queue()
    buffer=0
    tmp = ""
    for i in range(len(lst)):
        if lst[i] == tmp:
            print(lst)
            buffer+=1
            if buffer ==2:
                t+=1

                print(result.item.pop())
                print(result.item.pop())
                buffer = 1
            elif buffer<2:
                result.enQueue(lst[i])    
        else:
            buffer = 0
            result.enQueue(lst[i])
        tmp = lst[i]
    return result.item,t
def display(r,b,heat,freeze,mistake):
    print("Red Team : \n",len(r),'\n',"".join(reversed(r))  if len(r)!=0 else "Empty",'\n',heat-mistake," Explosive(s) ! ! ! (HEAT)",sep="")
    if mistake>0:
        print("Blue Team Made (a) Mistake(s)",mistake,"Bomb(s)")
    print("----------TENETTENET----------")
    print(": maeT eulB\n",len(b),'\n',"".join(reversed(b)) if len(b) != 0 else "ytpmE","\n","(EZEERF) ! ! ! (s)evisolpxE ",freeze,sep="")
    


freeze,heat,mistake = 0,0,0
r,b = list(map(list,input("Enter Input (Red, Blue) : ").split()))
b = b[::-1]
TENET(r,b,freeze,heat,mistake)