import random
def printfield(field,dpfield):
    for i in range(len(field)):
        strout = "["
        for j in range(len(field[0])):
            if dpfield[i][j] == 1 :
                strout += "[ ], "
            else:
                if field[i][j] >=9:
                    strout += "\"F\""+", "
                else:
                    strout += "\""+str(field[i][j])+"\""+", "
        print(strout[:-2]+"]")
def rand(h,v,field):
    rh,rv = random.randrange(0,h),random.randrange(0,v)
    if field[rh][rv] <= 9:
        field[rh][rv] = 9
    else:
        rand(h,v,field)
def calculatebomb(field):
    for i in range(len(field)):
        for j in range(len(field)):
            if field[i][j] >=9:
                if(i>0):
                    if(j<len(field)-1):
                        field[i-1][j+1]+=1
                    if(j>0):
                        field[i-1][j-1]+=1
                        field[i-1][j]+=1
                if(i<len(field)-1):
                    if(j<len(field)-1):
                        field[i+1][j+1]+=1
                    if(j>0):
                        field[i+1][j-1]+=1
                        field[i+1][j]+=1
                if(j>0):
                    field[i][j-1]+=1
                if(j<len(field)-1):
                    field[i][j+1]+=1

def pick(field,dpfield,x,y):
    if dpfield[x][y]==1:
        if field[x][y] >=9:
            print("gameover")
            return -1
        elif field[x][y] == 0:
            dpfield[x][y] = 0
        else:
            dpfield[x][y] = 0    
    else:
        print("alreadyshown")
    return checkwin(field,dpfield)
def checkwin(field,dpfield):
    win = False
    for i in range(len(field)):
        for j in range(len(field)):
            if field[i][j]<9 and dpfield[i][j]==1:
                return 0
    return 1
game = 0
field = [[0 for i in range(6)] for i in range(6)]
dpfield = [[1 for i in range(6)] for i in range(6)]
printfield(field,[[0 for i in range(6)] for i in range(6)])
inp = int(input("Enter Number of F : "))
for i in range(inp):
    rand(len(field),len(field[0]),field)

calculatebomb(field)  
printfield(field,[[0 for i in range(6)] for i in range(6)])
print("hiding")
printfield(field,dpfield)  
while game ==0:
    x,y = list(map(int,(input(f"choose x,y(1 to {len(field)}) : ").split())))
    game = pick(field,dpfield,x-1,y-1)
    if game !=0:
        printfield(field,[[0 for i in range(6)] for i in range(6)])
        break
    printfield(field,dpfield) 
