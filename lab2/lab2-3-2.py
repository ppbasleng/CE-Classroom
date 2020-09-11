def odd_even(arr, s):
    
    ore = {"Odd":0,"Even":1}
    print(arr[ore[s]:len(arr):2])
    

print('*** Odd Even ***')
lstorstr,lst,oddoreven = input('Enter Input : ').split(',')
if lstorstr is 'L' :
    lst = lst.split()

odd_even(lst,oddoreven)