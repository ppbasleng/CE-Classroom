print("*** multiplication or sum ***")
x = list(map(int,input("Enter num1 num2 : ").split()))

if(x[0]*x[1]<=1000):
    sum=x[0]*x[1]
else:
    sum=sum(x)
print("The result is",sum)
