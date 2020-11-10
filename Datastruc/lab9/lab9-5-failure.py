def bubble(lst,size,a=0,b=0):
    if a == size:
        return lst
    else:
        if b == size:
            return bubble(lst,size,a+1,a+1)
        if lst[a]>lst[b]:
            lst[a],lst[b] = lst[b],lst[a]
        return bubble(lst,size,a,b+1)

def subset(key,a = 0,l = []):
    global y
    if sum(l) == key:
        print(l)
    if a<=len(y)-1:
        subset(key,a+1)
        subset(key,a+1,[y[a]])
        l.append(y[a])
        subset(key,a+1,l)

    

inp = input("Enter Input : ").split("/")
y = [int(e) for e in inp[1].split()]
x = int(inp[0])
y = bubble(y,len(y))
subset(x)