def firstG(lst,value):
    for i in lst:
        if i>value:
            return i
    return "No First Greater Value"
inp = input('Enter Input : ').split('/')
L,R = list(map(int, inp[0].split())), list(map(int, inp[1].split()))
for i in R:
    print(firstG(sorted(L),i))
