def match(a,b):
    print(a,b)
    if a is "(":
        if b is ")":
            return True
    elif a is "[":
        if b is "]":
            return True
    elif a is "{":
        if b is "}":
            return True
    else:
        return False
from stack import Stack
str = "[[[]]]"
s = Stack()
error = False
for i in range(len(str)):
    print(s.item)
    if str[i] == '(' or str[i] == '[' or str[i] == '{':
        s.push(str[i])
        print("push",str[i])
    elif str[i] == ')' or str[i] == ']' or str[i] == '}':
        if(s.isEmpty()):
            error = True
        else:
            open = s.pop()
            if not match(open,str[i]):
                error = True
if error :
    print("MISMATCH")
else :
    if not s.isEmpty() :
        print("MISMATCH open paren.exceed")
    else:
        print("MATCH")