'''
n = int(input("How many numbers do you want to use today?"))     
firstValue = int(input("Enter the first number:"))  
largest = firstValue  
smallest = firstValue  
total = firstValue
counter = 0  
while counter<(n‐1):
    current = int(input("Enter the next number:"))
    total=total+current  
    counter=counter+1
    if current<smallest:    #find minimum  
        smallest = current  
    elif current>largest:  #find maximum  
        largest = current  
print("the average of the values is: ", total/n)  
print("the smallest of the values is {}".format(smallest))  
print("the largest of the values is {}".format(largest))  
print("the range of the values is {}".format(largest‐smallest))  
'''

accountTotal = 50   
while accountTotal > 20: #>=  
    accountTotal-=1#-=1
    print(accountTotal)
print('Your account has reached $20.')  
