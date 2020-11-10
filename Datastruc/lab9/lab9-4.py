def bubble(lst,size,a=0,b=0):
    if a == size:
        return lst
    else:
        if b == size:
            return bubble(lst,size,a+1,a+1)
        if lst[a]>lst[b]:
            lst[a],lst[b] = lst[b],lst[a]
        return bubble(lst,size,a,b+1)
def findmed(lst):
    tmp = lst.copy()
    tmp = bubble(tmp,len(tmp))
    if len(tmp)%2==0:
        return (tmp[len(tmp)//2-1]+tmp[len(tmp)//2])/2
    else:
        return tmp[len(tmp)//2]

l = [e for e in input("Enter Input : ").split()]
if l[0] == 'EX':
    Ans = "minHeap and maxHeap"
    print("Extra Question : What is a suitable sort algorithm?")
    print("   Your Answer : "+Ans)
else:
    l=list(map(int, l))
    lst = []
    for i in l:
        lst.append(i)
        print("list = ",lst," : median = ","{:.1f}".format(findmed(lst)),sep="")
        