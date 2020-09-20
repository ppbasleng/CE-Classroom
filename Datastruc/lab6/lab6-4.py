def perket(S=1,B=0,n=0):
    global slst,blst,result
    # print(S,B,n)
    if n>=len(slst)-1:
        result = abs(S-B) if result == None or result> abs(S-B) else result
    else:
        perket(S*slst[n+1],B+blst[n+1],n+1)
        perket(S,B,n+1)
inp =  input("Enter Input : ").split(",")
slst,blst =[],[]
result = None
for i in inp:
    slst.append(int(i.split()[0]))
    blst.append(int(i.split()[1]))
for i in range(len(slst)):
    perket(slst[i],blst[i],i)
print(result)