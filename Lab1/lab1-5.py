print("*** Fun with countdown ***")
x = list(map(int,input("Enter List : ").split(" ")))
counter = 0
lst=[]
sumlst=[]
for i in range(len(x)):
    if(x[i]==1):
        ncount=0
        tmplst =[]
        # print("found 1")
        while(ncount+1==x[i-ncount] and i-ncount>=0):
            # print(ncount+1,x[i-ncount])
            ncount+=1
            tmplst.append(ncount)
        tmplst.reverse()
        lst.append(tmplst)
        counter+=1 
sumlst.append(counter)
sumlst.append(lst)
print(sumlst)