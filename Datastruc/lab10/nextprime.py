def isprime(n,a=2):
    if n<=1:
        return
    else:
        if a>=n:
            return True
        elif n==2:
            return True
        elif n%a == 0:
            return False
        else:
            return isprime(n,a+1)
def nextprime(n):
    if not isprime(n+1):
        return nextprime(n+1)
    else:
        return n+1
tablesize = int(input())
table = [None for i in range(tablesize)]
print(table)
newsize = nextprime(tablesize*2)
table.extend([None for i in range(tablesize,newsize)])
tablesize = newsize
print(table)