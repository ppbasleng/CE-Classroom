def MinimumWeight(Weights, n):
    left, right = max(Weights), sum(Weights)
    print("min,max",left,right)
    while left < right:
        mid = left + (right - left)//2
        currentWeight, needBox = 0, 1
        for wt in Weights:
            print(currentWeight,needBox,end = "-> ")
            if currentWeight + wt > mid:
                needBox += 1
                currentWeight = wt
            else:
                currentWeight += wt
            print(currentWeight,needBox,end = "|| ")
        print("now we had ")
        print(left,mid,right)
        if needBox <= n :
            right = mid 
        else:
            left = mid + 1
        print(left,mid,right)
    return left

boxs, n = input("Enter Input : ").split('/')
boxs, n = list(map(int, boxs.split())), int(n)
print(f"Minimum weigth for {n} box(es) = {MinimumWeight(boxs, n)}")