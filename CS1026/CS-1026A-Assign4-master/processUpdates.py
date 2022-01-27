badUpdateFile = open("badupdates.txt", 'w')
def processUpdates(cntryFileName,updateFileName,badUpdateFile):
    return None
def isValidUpdate(record):
    record = record.replace(" ", "")
    record = record.split(";")
    if len(record) > 4:
        return False
    if invalidName(record[0]):
        return False
    
    pop = ""
    area = ""
    cont = ""

    for update in record[1::]:
        if update[0:2]=="P=":
            if pop != "":
                return False
            if invalidDigit(update[2::]):
                return False
            pop = update[2::]
            
        if update[0:2]=="A=":
            if area != "":
                return False
            if invalidDigit(update[2::]):
                return False
            area = update[2::]
        
        if update[0]=="C=":
            if cont != "":
                return False
        print(update)

def invalidDigit(digit):
    digit = digit.split(",")
    if not digit[0].isdigit():
        return True
    if len(digit[0]) > 3 or len(digit[0])<1:
        return True
    for nums in digit[1::]:
        if len(nums) != 3:
            return True
        if not nums.isdigit():
            return True
    return False
def invalidCont(cont):
    
def invalidName(name):
    if name[0] != name[0].upper():
        return True
    for char in name:
        if not char.isalpha() and char != "_":
            return True
    return False
print(isValidUpdate(" United_States_of_America; P=328,566,312; A=83, 022, 544"))
