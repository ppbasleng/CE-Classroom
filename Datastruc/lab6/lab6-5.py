def staircase(n,stair=""):
    if abs(n)==1:
        print("#")
        return
    elif n<0:
        if -n == len(stair)+1:
            if len(stair) != 0:
                print(stair+"#")
        else:
            if len(stair) ==0:
                staircase(n,"#"+stair)
            elif stair[0]!="_":
                staircase(n,"#"+stair)
            staircase(n,"_"+stair)
    elif n>0:
        if n == len(stair)+1:
            if len(stair) != 0:
                print(stair+"#")
        else:
            if len(stair) ==0:
                staircase(n,stair+"_")
            elif stair[-1]!="#":
                staircase(n,stair+"_")
            staircase(n,stair+"#")
    elif n == 0:
        print("Not Draw!")

        
staircase(int(input("Enter Input : ")))