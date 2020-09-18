import turtle

def tree(branchLen,t,sp):
    if branchLen > 5:
        t.speed(sp)
        t.forward(branchLen)
        t.right(45)
        tree(branchLen-15,t,sp+20)
        t.left(90)
        tree(branchLen-15,t,sp+20)
        t.right(45)
        t.backward(branchLen)

speed = 200
t = turtle.Turtle()
myWin = turtle.Screen()
t.color("white")
myWin.bgcolor("black")
t.speed(speed)
t.pensize(3)
t.left(90)
t.up()
t.backward(100)
t.down()
tree(100,t,speed)
myWin.exitonclick()
