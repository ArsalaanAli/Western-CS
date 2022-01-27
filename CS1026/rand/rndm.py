tot = 0
for i in range(len(string)-1):
    if i%2==0:
        tot += int(string[i])*3
    else:
        tot += int(string[i])
