'''
def zFirst(words):  
    zresult =[]  
    result =[]  
    for word in words:  
        if word.lower()[0] == 'z':  
            zresult.append(word)  
        else:  
            result.append(word)  
    zresult.sort()  
    result.sort()  
    return zresult + result 


words=["hello","good","nice","as","at","baseball","absorb","sword","a","tall","so","bored","silver","hi","pool","we","am","seven","do","you","want","ants","because","that's","how","you","get","zebra","zealot","zoo","xylophone","asparagus"]  
# Print the result of using zFirst  
print(zFirst(words)) 
'''

values = [1,2,3,4,5]  
newValues = list(values)
for i in range(len(values)):  
    newValues[i] +=1

    print("Old Value at index {} is: {} ".format(i, values[i]))  
      
    print("New Value at index {} is: {} \n".format(i, newValues[i]))  
