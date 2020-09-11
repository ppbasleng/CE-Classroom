def mapping(lst):
    # lstsum = []
    count = 0
    m = dict()
    for ele in lst:
        if ele not in m.keys():
            # print(ele)
            m[ele] = count
            count+= 1
    # print(m.values(),m.keys())
    # for i in lst:
    #     print(m[i])
    #     lstsum.(i = int(m[i])
        
    return [m[i] for i in lst]
        


lst = list(input("Enter String : "))
print(mapping(lst))