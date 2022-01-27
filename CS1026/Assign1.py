#BY ARSALAAN ALI
#CS1026 ASSIGNMENT 1: HOME POWER CONSUMPTION
#PROGRAM THAT COMPUTES THE COST OF ELECTRICITY FOR INDIVIDUAL RESIDENCES

#Constants for electricity usage rates
OFF_PEAK_RATE = 0.085
PEAK_RATE = 0.176
MID_PEAK_RATE = 0.119

#loop that runs until user inputs 0
while True:
    #getting input from user and storing it as floats in variables to hold the different rates
    offPeakKwh = float(input("Enter kwh during Off Peak period: "))
    if offPeakKwh == 0:# if the user enters 0 the loop breaks and prints out to let the user know that the process is finished
        break
    peakKwh = float(input("Enter kwh during On Peak period: "))
    midPeakKwh = float(input("Enter kwh during Mid Peak period: "))
    isSenior = (input("Is owner senior? (y,n): ") == "y".lower())#getting input from the user to check if they're a senior
    print(isSenior)
    totalKwh = offPeakKwh + peakKwh + midPeakKwh#calculating the total kwh of the user and storing it in a variable
    offPeakValue = offPeakKwh * OFF_PEAK_RATE#calculating the price of the electricity used in each of the different rates
    peakValue = peakKwh * PEAK_RATE
    midPeakValue = midPeakKwh * MID_PEAK_RATE

    if totalKwh < 400:#total usage discount of 4% if the total usage is less than 400
        price = offPeakValue + peakValue + midPeakValue
        price *= 0.96#price holds the sum of all of the prices of the different periods, the discount is applied to this sum

    else:#if the total usage discount is not applied
        if peakKwh < 150:#if the on peak kwh is less than 150 then a disount of 5% is applied on the on peak period 
            peakValue *= 0.95#peak value is discounted by 5%
        price = offPeakValue + peakValue + midPeakValue#price holds the sum of all of the prices of the different periods
        
    if isSenior:
        price *= 0.89#if the user is a senior then the senior discount of 11% is applied

    price *= 1.13#a tax of 13% is added to the subtotal

    print("Electricity cost: %.2f" % price)#the electricity cost is outputted to 2 decimal places
    

    
