answer1 = 5+3  
answer2 = 7*4
print("answer1")
print(answer1)  

x=7  
print(x)  
y=x+5
print("x is {} and y is {}".format(x,y))
print ("x is %d and y is %d" % (x,y))


shopName = input("Please enter the shop name: ")
ringQTY = int(input("Please enter ring QTY: "))
glassesQTY = int(input("Please enter glasses QTY: "))
print("Shop name is {}".format(shopName))  
print("Ring QTY is {}".format(ringQTY))  
print("Glasses QTY is {}".format(glassesQTY))
print("Inventory Total: {}".format(ringQTY+glassesQTY))
