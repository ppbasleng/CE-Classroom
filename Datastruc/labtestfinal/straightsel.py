def ssel(lst,last):
    if last==0:
        return lst
    if last>0:
        if lst[last]<max(lst[0:last]):
           lst[last],lst[lst.index(max(lst[0:last]))] =  lst[lst.index(max(lst[0:last]))],lst[last]
           print(lst)
        ssel(lst,last-1)
    
lst = [5,4,3,1,2]
# lst = [5,6,7,9,4,2,1,3]
print(ssel(lst,len(lst)-1))