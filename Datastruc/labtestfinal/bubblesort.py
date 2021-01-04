# def bubble(lst,size,a=0,b=0):
#     print(a,b)
#     if a == size:
#         return lst
#     else:
#         if b == size:
#             return bubble(lst,size,a+1,a+1)
#         if lst[a]>lst[b]:
#             lst[a],lst[b] = lst[b],lst[a]
#         return bubble(lst,size,a,b+1)
def bubble(lst):
    count = 0
    for i in range(len(lst)):
        swap = False
        for j in range(len(lst)-i-1):
            count +=1
            if lst[j] > lst[j+1]:
                lst[j],lst[j+1] = lst[j+1],lst[j]
                swap = True
        if not swap:
            break
    print(count)
    return lst
lst = [9,8,7,6,5,4,3,2,1]
print(bubble(lst))