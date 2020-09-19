def move(n,A,C,B):
    if n==1:
        print(n,"From",A,"To",C)
    else:
        move(n-1,A,B,C)
        print(n,"From",A,"To",C)
        move(n-1,B,C,A)

move(3,"A","C","B")
