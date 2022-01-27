#ARSALAAN ALI
#CS 1026 ASSIGNMENT 3
#CALCULATES HAPPINESS SCORES FROM TWEETS FOR DIFFERENT REGIONS
from sentiment_analysis import compute_tweets#importing compute_tweets function from the other file

tweetFile = input("tweet file name: ")
keywordFile = input("keyword file name: ")#getting file names input from user

results = compute_tweets(tweetFile, keywordFile)#out from the compute_tweets function is held in this variable
for i in range(4):#looping for each region
    if i == 0:#printing out the name of each region
        print("\nEASTERN")
    if i == 1:
        print("\nCENTRAL")
    if i == 2:
        print("\nMOUNTAIN")
    if i == 3:
        print("\nPACIFIC")
    print("Average Happiness Score: " + str(results[i][0]))#printing the data from each region
    print("Keyword Tweet Count: " + str(results[i][1]))
    print("Tweet Count: " + str(results[i][2]))
