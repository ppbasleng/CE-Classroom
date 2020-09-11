def sumzero(lst):
    sumlst = []
    for i in range(len(lst)):
        for j in range(len(lst)):
            for k in range(len(lst)):
                # print(i,j,k)
                if lst[i]+lst[j]+lst[k] == 0 :
                    if i != j != k != i:
                        inlst = [lst[i],lst[j],lst[k]]
                        if set(inlst) not in map(set,sumlst):
                            sumlst.append(inlst)
    print(sumlst)
lst = list(map(int,input("Enter Your List : ").split()))
if len(lst)<3 :
    print("Array Input Length Must More Than 2")
else :
    sumzero(lst)