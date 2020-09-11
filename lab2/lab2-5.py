class Torkham:
    wordType = ""
    word = ""
    def __init__(self,stringin):
        lstword = stringin.split()
        self.wordType = lstword[0]
        if self.wordType == "P" :
            self.word = lstword[1]
            # print(self.word) #test word
        else:
            self.word = stringin
    def wordcompare(self,nextKham):
        if self.wordType == "P" and nextKham.wordType == "P":
            # print("test case : ",self.word[len(self.word)-2:len(self.word)].casefold() , nextKham.word[0:2].casefold())
            if self.word[len(self.word)-2:len(self.word)].lower() == nextKham.word[0:2].lower():
                # print("match")
                return 1
            else:
                print('\'',nextKham.word,'\' -> game over',sep = "")
                # print("Not Match !!!")
                return -1
        elif nextKham.wordType is "R":
            return 0
        elif nextKham.wordType is "X":
            return -1
        else :
            print('\'',nextKham.word,'\' is Invalid Input !!!',sep = "")
            return -1
    @staticmethod
    def result(lst):
        outlst = []
        count = 0
        summary=0
        while summary!=-1: 
            # print("len = ",len(outlst))
            while lst[count].wordType == "R":
                outlst = []
                count+=1
                print("game restarted")
            if len(outlst) == 0 and lst[count].wordType == "P":
                outlst.append(lst[count].word)
                print('\'',lst[count].word,'\' -> ',outlst,sep = "")

            summary = lst[count].wordcompare(lst[count+1])    
            if summary is 1:
                if  lst[count+1].word not in outlst:
                    outlst.append(lst[count+1].word)
                    print('\'',lst[count+1].word,'\' -> ',outlst,sep = "")
            elif summary is -1:
                break
            count+=1

print("*** TorKham HanSaa ***")
inputstr = list(input("Enter Input : ").split(","))
for i in range(len(inputstr)):
    inputstr[i] = Torkham(inputstr[i])
    # print("Torkham",inputstr[i].word)
Torkham.result(inputstr)