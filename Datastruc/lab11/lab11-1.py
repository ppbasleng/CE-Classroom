def printadj(table,g):
    print("    ",end="")
    print("  ".join(table))
    for i in table:
        strout = ""
        print(i,end=" : ")
        for j in table:
            l = g.get(i,None)
            if not l :
                strout+="0, "
            elif j in l:
                strout+="1, "
            else:
                strout+="0, "
        print(strout[:-2])


table = []
inp = input("Enter : ").split(",")
g = dict()
for i in inp:
    if g.get(i.split()[0],-1) == -1:
        g[i.split()[0]] = i.split()[1]
    else:
        g[i.split()[0]] += i.split()[1]
    if i.split()[0] not in table:
        table.append(i.split()[0])
    if i.split()[1] not in table:
        table.append(i.split()[1])
table.sort()
printadj(table,g)
