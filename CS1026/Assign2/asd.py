def basicCode(code):
  total = 0
  for i in range(len(code)-1):
    total += int(code[i])
  checkDigit = str(total%10)
  if code[-1] == checkDigit:
    return True
  else:
    return False
print(basicCode('434134'))

def positionalCode(code):
    total = 0
    for i in range(len(code)-1):
        total += int(code[i])*(i+1)
    checkDigit = str(total%10)
    if code[-1] == checkDigit:
        return True
    else:
        return False

def UPC(code):
    total = 0
    for i in range(len(code)-1):
        if i%2==0:
            total += int(code[i])*3
        else:
            total += int(code[i])
    if total%10 == 0:
        checkDigit = 0
    else:
        checkDigit = 10-(total%10)
    if int(code[-1]) == checkDigit:
        return True
    else:
        return False
print(UPC("80663341344"))
