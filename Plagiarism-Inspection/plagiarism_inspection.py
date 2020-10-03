# -*- coding: utf-8 -*-
"""
Created on Mon Jan 27 22:10:13 2020

@author: hasc
"""

def split_sentence(sentences):
    EXCEPTION = ['.','!','?']
    sentence=[]
    tmp =""
    for ch in sentences:
        if ch in EXCEPTION:
            sentence.append(tmp)
            tmp= ""
        else:
            tmp+=ch
    return sentence

def transform(sentences):
    tmp = ""
    divide_sentence = []
    for sentence in sentences:
        for ch in sentence:
           if((ord(ch)>=65 and ord(ch)<=90) or (ord(ch)>=97 and ord(ch)<=122)):
               tmp+=ch
           else:
               if tmp not in "":
                   divide_sentence.append(tmp)
                   tmp = ""                
    divide_sentence.append(tmp)          
    return divide_sentence
# 트랜스폼 하고 비교문장 함수에 넣기
def compare_sentences(sentence1,sentence2):
    num=[]
    sentence=[]
    tmp =""
    count = 0
    key = -1
    for i,ch1 in enumerate(sentence1):
        for j,ch2 in enumerate(sentence2):
            if(ch1==ch2):
                num.append(j)
                break
        if(ch1 !=ch2):
            num.append(-1)
    for i, (a,b) in enumerate(zip(num,sentence2)):
        if(i==0 or key ==0):
            idx=a
            count+=1
            tmp+=b
            key=-1
        else:
            if((a-idx)==1):
                idx=a
                count+=1
                tmp=tmp +" "+b         
            else:
                idx=a
                if(count>=4 and tmp !=""):
                    sentence.append(tmp)
                    count = 0
                    tmp=""
                else:
                    count = 0
                    tmp=""
        if(a ==-1):
            key=0
            count = 0
            tmp = ""
        if(i==(len(num)-1)):
            if(count>=4 and tmp !=""):
                sentence.append(tmp)
                tmp=""
                count=0
    return sentence
                
                
sentence1 = []
sentence2 = []
s1=[]
s2=[]
overlap_sentence=[]

r1 = open('test1.txt', mode='r', encoding='cp949')
r2 = open('test2.txt', mode='r', encoding='cp949')

sentence1.extend(r1.read())
sentence2.extend(r2.read())

sentence1, sentence2 = split_sentence(sentence1),split_sentence(sentence2)
for i in sentence1:
    s1.append(i.strip())
for i in sentence2:
    s2.append(i.strip())
    
for a in s1:
    for i,b in enumerate(s2):
        if(i==0):
            a = transform(a)
        b = transform(b)
        x = compare_sentences(a,b)
        if x:
            overlap_sentence.append(x)
         

print("실행 결과")
for same_sentence in overlap_sentence:
    for sentence in same_sentence:
        print(sentence)
