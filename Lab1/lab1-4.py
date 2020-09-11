def num_grid(lst):

    for i in range(5):
      for j in range(5):
        if(lst[i][j]=="-"):
          lst[i][j]=0
        elif(lst[i][j]=="#"):
          lst[i][j]=9

    i,j=0,0
    for i in range(5):
      for j in range(5):
        if(lst[i][j]>8):

          if(i>0):
            if(j<4):
              lst[i-1][j+1]+=1
            if(j>0):
              lst[i-1][j-1]+=1
            lst[i-1][j]+=1
          if(i<4):
            if(j<4):
              lst[i+1][j+1]+=1
            if(j>0):
              lst[i+1][j-1]+=1
            lst[i+1][j]+=1
          if(j>0):
            lst[i][j-1]+=1
          if(j<4):
            lst[i][j+1]+=1
    i,j=0,0
    for i in range(5):
      for j in range(5):
          if(lst[i][j]>8):
            lst[i][j]='#'
          else:
            lst[i][j] = str(lst[i][j])      
    return lst
    


'''lst_input = [

    ["-","-","-","-","-"],

    ["-","-","-","-","-"],

    ["-","-","#","-","-"],

    ["-","-","-","-","-"],

    ["-","-","-","-","-"]

]'''

lst_input = []
print("*** Minesweeper ***")
input_list = input("Enter input(5x5) : ").split(",")

for e in input_list:

  lst_input.append([i for i in e.split()])

print("\n",*lst_input,sep = "\n")

print("\n",*num_grid(lst_input),sep = "\n")