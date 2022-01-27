#BY ARSALAAN ALI
#CS1026 ASSIGNMENT 2: CODES AND CHECK DIGITS
#FUNCTIONS FOR CHECK THE VALIDITY OF EACH TYPE OF CODE

def Basic(code):#function checks if code is a basic code
    total = 0#variable to hold the total of all digits
    baseCode = code[0:-1]#baseCode is the original code without the last digit
    for i in baseCode:
        total+=int(i)#looping through the basic code and getting the sum of its digits
    checkDigit = str(total%10)#calculating the check digit
    if baseCode+checkDigit == code:#checking if the original code is a valid basic code
        return True#returning true if its a basic code
    return False#returning false otherwise

def Positional(code):#function checks if code is a positional code
    total = 0#total vairable to hold the sum of the digits
    baseCode = code[0:-1]#original code without the last digit
    for i in range(len(baseCode)):#looping through basecode
        total += int(baseCode[i])*(i+1)#getting sum of each digit multiplied by its index+1
    checkDigit = str(total%10)#calculating the check digit
    if baseCode + checkDigit == code:#checking if the original code is a valid positional code
        return True#returning true if its valid
    return False#returning false if otherwise

def UPC(code):#function checks if code is a UPC code
    total = 0#total vairable to hold the sum of the digits
    baseCode = code[0:-1]#original code without the last digit
    for i in range(len(baseCode)):#looping through the basecode
        if i%2==0:#if the index of the digit is odd
            total += int(baseCode[i])*3#the digit mulitplied by three is added to total
        else:#if the index of the digit is even
            total += int(baseCode[i])#the digit is added to total
    
    checkDigit = 0 if (total%10 == 0) else (10-(total%10))#if the last digit of total is 0 then check digit is 0, otherwise check digit is the last digit subtracted from 10
    print(total, checkDigit)
    if baseCode + str(checkDigit) == code:#checking if the original code is a valid UPC code
        return True#returning true if its valid
    return False#returning false otherwise
print(UPC("80663341344"))
