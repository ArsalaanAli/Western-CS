'''
values =[1,2,3,4,5,"hello",6,7,8,9,"10"]  
 
for cur in values:  
    print("The value is :", cur)  
    if type(cur) == str:
        raise Exception("This is a string!")

'''
filename = input("Enter filename: ")
try:
    infile = open(filename, "r")
except IOError as e:
    print("no file with the name", filename)
else:
    line = infile.readline() 
    try:
        value = int(line.strip("\n"))
    except ValueError:
        print("the line is not an integer value")
    else:
        print(value)
