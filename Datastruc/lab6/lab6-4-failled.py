def perket(x,N=0,S=0,B=0):
    print("X:",x,"N:",N,"S:",S,"B:",B)
    if S == 0 and B == 0:
        if len(x.split(","))==1:
            print("chk2")
            perket("",abs(int(x.split(",")[-1].split()[0])-int(x.split(",")[-1].split()[1])),int(x.split(",")[-1].split()[0]),int(x.split(",")[-1].split()[1]))
            return
        else:
            print("chk3",",".join(x.split(",")[:-1]),"N:",abs(int(x.split(",")[-1].split()[0])-int(x.split(",")[-1].split()[1])))
            perket(",".join(x.split(",")[:-1]),abs(int(x.split(",")[-1].split()[0])-int(x.split(",")[-1].split()[1])),int(x.split(",")[-1].split()[0]),int(x.split(",")[-1].split()[1]))
            return
    if len(x) >= 3:
        if N >= abs(S*int(x.split(",")[-1].split()[0])-(B+int(x.split(",")[-1].split()[1]))) :
            print("chk4","N:",abs(S*int(x.split(",")[-1].split()[0])-(B+int(x.split(",")[-1].split()[1]))))
            perket(",".join(x.split(",")[:-1]),abs(S*int(x.split(",")[-1].split()[0])-(B+int(x.split(",")[-1].split()[1]))),S*int(x.split(",")[-1].split()[0]),B+int(x.split(",")[-1].split()[1]))
        else:
            print("chk5","N:",N)
            perket(",".join(x.split(",")[:-1]),N,S,B)
    else:
        print(len(x),"::",N)
        print(N)
x = input("Enter Input : ")
perket(x)