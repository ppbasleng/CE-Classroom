class Calculator :

    ### Enter Your Code Here ###
    def __init__(self,inp):
        self.value = inp
    def __add__(self,b):
        return self.value+b.value
        ###Enter Your Code For Add Number###
        
    def __sub__(self,b):
        return self.value-b.value
        ###Enter Your Code For Sub Number###
    
    def __mul__(self,b):
        return self.value*b.value
        ###Enter Your Code For Mul Number###
    def __truediv__(self,b):
        return float(self.value)/float(b.value)
        ###Enter Your Code For Div Number###

x,y = input("Enter num1 num2 : ").split(",")
x,y = Calculator(int(x)),Calculator(int(y))
# print(x+y)
print(x+y,x-y,x*y,x/y,sep = "\n")