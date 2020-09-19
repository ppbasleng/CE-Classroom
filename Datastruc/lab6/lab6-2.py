def length(txt):
    txtl = list(txt)
    if txtl!=[]:
        n = 0
        print(txtl.pop(0),"*",end ="",sep ="")
        n+=1
        if txtl!=[]:
            print(txtl.pop(0),"~",end ="",sep ="")
            n+=1
        return n+length("".join(txtl))
    else:
        return 0
print("\n",length(input("Enter Input : ")),sep="")
#ตรง print(เป็นแค่ตัวอย่างสามารถแก้ไขได้)