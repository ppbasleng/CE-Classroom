def odd_even(arr, s):
    returnlst = []
    divider = 0
    if s == "Even" :
        # print("ODDDD")
        divider = 1
    elif s == "Odd":
        # print("EVENNNNN")
        divider = 0

    for i in range(len(arr)):
        if i%2 == divider:
            # print(i,i%2,divider)
            returnlst.append(arr[i])
    return returnlst

print('*** Odd Even ***')
lstorstr,lst,oddoreven = input('Enter Input : ').split(',')
lst= list(lst)
while lst.count(" ")>0:
    lst.remove(" ")

if lstorstr is "S":

    str1 = ""
    output = odd_even(lst,oddoreven)
    for ele in output:
        str1 += ele
    print(str1)
elif lstorstr is "L":
    print(odd_even(lst,oddoreven))