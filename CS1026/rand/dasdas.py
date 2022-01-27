from code_check import

BList = []
PList = []
UPList = []
while True:
    x = input()
        if BCode(x):
            print("is basic code")
            BList.append(x)
        if PCode(x):
            print("is positional code")
            PList.append(x)
        if UPCode(x)
            print("is universal product code")
            UPList.append(x)
        if x == '0':
            break
print('summary')
print('BCode: ', BList)
print('PCode: ', PList)
print('UPCode: ', UPList)
