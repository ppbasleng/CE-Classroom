def merge(l,left,right,rightend):
    start = left
    leftend = right-1
    result = []
    print(l)
    while left<=leftend and right<=rightend:
        if l[left]<l[right]:
            result.append(l[left])
            left+=1    
        else:
            result.append(l[right])
            right+=1
    while left<=leftend:
        result.append(l[left])
        left+=1
    while right<=rightend:
        result.append(l[right])
        right+=1
    
    for ele in result:
        l[start] = ele
        start+=1
        if start>rightend:
            break
def mergesort(l,left,right):
    center = left+(right-left)//2
    if left<right:
        mergesort(l,left,center)
        mergesort(l,center+1,right)
        merge(l,left,center+1,right)

lst = [1,3,6,5,2,4,8,7]
mergesort(lst,0,len(lst)-1)
print(lst)