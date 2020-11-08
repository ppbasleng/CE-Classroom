def SSSort(lst,ln):
    if ln >0:
        if lst[ln]<max(lst[0:ln]):
            print("swap ",lst[ln]," <-> ",max(lst[0:ln])," : ",sep = "",end = "")
            swap(lst,max(lst[0:ln]),lst[ln]) 
            print(lst)
            SSSort(lst,ln-1)
        else:
            SSSort(lst,ln-1)

def swap(lst,a,b):
    indexa = lst.index(a)
    indexb = lst.index(b)
    lst[indexa] = b
    lst[indexb] = a 

inp = [int(e) for e in input("Enter Input : ").split()]
SSSort(inp,len(inp)-1)
print(inp)