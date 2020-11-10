def bubble(lst,size,a=0,b=0):
    if a == size:
        return lst
    else:
        if b == size:
            return bubble(lst,size,a+1,a+1)
        if lst[a]>lst[b]:
            lst[a],lst[b] = lst[b],lst[a]
        return bubble(lst,size,a,b+1)
def bubbleset(lst):
    for a in range(len(lst)):
        for b in range(a,len(lst)):
            if len(lst[a])>len(lst[b]):
                lst[a],lst[b] = lst[b],lst[a]
            elif len(lst[a])==len(lst[b]):
                if len(lst[a]) != 0 and len(lst[b]) !=0:
                    lst[a],lst[b] = lst[b],lst[a]
        
def subs(l):
    if l == []:
        return [[]]

    x = subs(l[1:])

    return x + [[l[0]] + y for y in x]

def filt(lst,x):
    newl = []
    for i in lst:
        # print(i,"|::",sum(i))
        if sum(i) == x:
            newl.append(i)
    return newl
inp = input("Enter Input : ").split("/")
y = [int(e) for e in inp[1].split()]
x = int(inp[0])
y = bubble(y,len(y))
y = subs(y)
y = filt(y,x)
bubbleset(y)
if len(y)==0:
    print("No Subset")
else:
    for i in y:
        print(i)
