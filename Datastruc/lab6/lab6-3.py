def bit(n, data=''):
    if n <0:
        print("Only Positive & Zero Number ! ! !")
        return 0
    if n == 0:
        print(0)
        return 0
    if len(data) == n:
        print(data)
    else:
        bit(n, data + '0')
        bit(n, data + '1')

        
x = int(input("Enter Number : "))
bit(x)