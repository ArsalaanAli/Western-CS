s = input()
numRows = int(input())
length = len(s)
if length == 1:
    print(s)
if numRows == 1:
    print(s)
ans = ['' for i in range(numRows)]
buffer = numRows*2 - 2
ind = 0
while ind < length:
    for i in range(buffer):
        print(ind)
        if ind >= length:
            break
        if i < numRows:
            ans[i] += s[ind]
        else:
            ans[buffer-i] += s[ind]
        ind+=1
print(ans)
