def bi_search(l, r, arr, x):
    if l>r:
        return False
    mid = l+(r-l)//2
    # print(mid,arr[mid])
    if arr[mid]<x :
        return bi_search(mid+1,r,arr,x)
    elif arr[mid]>x:
        return bi_search(l,mid-1,arr,x)
    elif arr[mid]==x:
        return True
    
inp = input('Enter Input : ').split('/')
arr, k = list(map(int, inp[0].split())), int(inp[1])
print(bi_search(0, len(arr) - 1, sorted(arr), k))