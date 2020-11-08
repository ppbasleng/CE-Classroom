def iSort(lst,newl = [],n=1):
    if len(lst)>0:
        # print(newl,lst)
        compInsert(newl,lst.pop(0),len(newl)-1)
        if len(newl)>1:
            print(newl,end=" ")
            if len(lst)>0:
                print(lst)
            else:
                print('\n',"sorted\n",newl,sep="")
        iSort(lst,newl,n+1)
        
            
def compInsert(lst,a,ln):
    if len(lst)==0:
        lst.append(a)
        return
    if ln>=-1: 
        if ln ==-1:
            lst.insert(0,a)
            print("insert ",a," at index ",ln+1," : ",sep = "",end ="")
        elif a < lst[ln]:
            compInsert(lst,a,ln-1)
        else:
            lst.insert(ln+1,a)
            print("insert ",a," at index ",ln+1," : ",sep = "",end ="")

        

    

inp = [int(e) for e in input("Enter Input : ").split()]
iSort(inp)