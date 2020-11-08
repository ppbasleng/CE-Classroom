def mysort(lst):
    recent = None
    for i in lst:
        if recent==None:
            recent = i
        elif recent>i:
            return "No"
    return "Yes"
lst = []
inp = [int(e) for e in input("Enter Input : ").split()]
print(mysort(inp))