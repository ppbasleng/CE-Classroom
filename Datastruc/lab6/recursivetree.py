import turtle
def tree(n,len):
    if n == 1:
        pass
    else:
        me.forward(len)
        me.left(45)
        tree(n-1,len-10)
        me.right(90)
        tree(n-1,len-10)
        me.left(45)
        me.backward(len)
 
        
wn = turtle.Screen()
wn.bgcolor("black")
me = turtle.Turtle()
me.color("white")
me.speed(100)
me.pensize(3)
me.left(90)
me.backward(100)
len = 100
tree(8,len)
me.right(180)
tree(8,len)
wn.exitonclick()
