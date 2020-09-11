print("*** Election ***")
x = int(input("Enter a number of voter(s) : "))
y = list(map(int,input().split(" ",x)))
candidate=-1
vote=0
for i in range(20):
    newvote = y.count(i)
    #print(newvote,candidate)

    if(newvote>vote):
        candidate=i
        vote = newvote
if(candidate!=-1):
    print(candidate)
else:
    print("*** No Candidate Wins ***")