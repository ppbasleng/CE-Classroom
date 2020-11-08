def bubble(lst,a,b,size):
    if a == size:
        return lst
    else:
        if b == size:
            return bubble(lst,a+1,a+1,size)
        if lst[a]>lst[b]:
            lst[a],lst[b] = lst[b],lst[a]
        return bubble(lst,a,b+1,size)
def findmean(lst):
    pass
inp = [int(e) for e in input("Enter Input : ").split()]
print(bubble(inp,0,0,len(inp)))