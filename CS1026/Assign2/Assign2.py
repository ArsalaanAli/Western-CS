#BY ARSALAAN ALI
#CS1026 ASSIGNMENT 2: CODES AND CHECK DIGITS
#PROGRAM THAT DETERMINES WHETHER INPUTTED CODES ARE VALID BASIC, POSITIONAL OR UPC CODES

#importing code_check.py to gain access to its functions
import code_check

#declaring lists that will hold the different types of codes
basicList = []
positionalList = []
upcList = []
noneList = []

#while loop that runs until user inputs "0"
while True:
    #declaring booleans that represent what type of code each code is
    isBasic = False
    isPositional = False
    isUPC = False
    #getting input from user
    inputCode = input("Please enter code (digits only) (enter 0 to quit): ")
    #breaking the loop if input is "0"
    if inputCode  == "0":
        break

    #checking the inputted code with each code type to determine which code types are valid for this code
    if code_check.Basic(inputCode):#runs code through the respective function in code check
        isBasic = True#if function returns true the boolean for this specific code type is changed to true
        basicList.append(inputCode)#adding code to its respective list
        print("‐‐ code:", inputCode,"valid Basic code")#printing out to let the user know that it is a valid code of this type
    if code_check.Positional(inputCode):
        isPositional = True
        positionalList.append(inputCode)
        print("‐‐ code:", inputCode, "valid Position code")
    if code_check.UPC(inputCode):
        isUPC = True
        upcList.append(inputCode)
        print("‐‐ code:", inputCode, "valid UPC code")
    if not (isBasic or isPositional or isUPC):#if code was not valid for any of the three types
        noneList.append(inputCode)#code is added to list of none type codes
        print("‐‐ code:", inputCode, "not Basic, Position or UPC code.")#printing out to let user know that it is not a valid code of any type

#if the lists of these code types have values in them, then a string is created with each code in the list seperated by a ","
#otherwise if the lists of these code types dont have any values in them then the string is set to the value of "None"
basicString = ', '.join(basicList) if len(basicList) > 0 else "None"
positionalString = ', '.join(positionalList) if len(positionalList) > 0 else "None"
upcString = ', '.join(upcList) if len(upcList) > 0 else "None"
noneString = ', '.join(noneList) if len(noneList) > 0 else "None"

print("\nSummary")#printing out a summary with each code type and all of the codes that apply to that type, or if no codes apply to that type printing out "None"
print("Basic: " + basicString)
print("Position: " + positionalString)
print("UPC: " + upcString)
print("None: " + noneString)
