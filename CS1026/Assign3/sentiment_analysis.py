#constant variables for the time zones
NONE = -1
EASTERN = 0
CENTRAL = 1
MOUNTAIN = 2
PACIFIC = 3

def findTimeZone(lat, long):#calculates the time zone given longitude and latitude
    if lat > 49.189787 or lat < 24.660845 or long > 67.444574 or long < -125.242264:#if coordinates are outside the given range then there is no timezone
        return NONE
    if long >= -87.518395:#using longitude boudaries to check which time zone the coordinates are in
        return EASTERN
    elif long >= -101.998892:
        return CENTRAL
    elif long >= -115.236428:
        return MOUNTAIN
    elif long >= -125.242264:
        return PACIFIC

def compute_tweets(tweetFileName, keywordFileName):#computes the happiness scores of tweets in different time zones
    timeZoneData = [[0, 0, 0] for i in range(4)]#list to hold data for each timezone
    keywordsFile = open(keywordFileName, "r")
    tweetsFile = open(tweetFileName, "r")
    keywords = {}#dictionary to hold the values of each keyword
    for line in keywordsFile:
        line = line.rstrip("\n")
        line = line.split(',')
        keywords[line[0]] = int(line[1])#adding keywords and values to dictionary

    for line in tweetsFile:#looping through each tweet
        location = []#list to hold the lat and long values of the tweet
        line = line.split()
        location.append(float(line[0][1:-1]))
        location.append(float(line[1][0:-1]))
        timeZone = findTimeZone(location[0], location[1])#finding the time zone of each tweet
        if timeZone == NONE:
            continue#if there is no time zone then the tweet is not counted

        timeZoneData[timeZone][0] += 1 #increasing the count of tweets in this time zone
        sentence = line[5::]#a list that holds the words in the tweet
        isKeyword = False#variable to check if this tweet has been counted as a keyword tweet already
        happinessScore = 0#the total happiness score of this tweet
        keywordCount = 0#the amount of keywords in this tweet
        for word in sentence:#looping through the words in the tweet
            word = word.strip('''!()-[]{};:'"\,<>./?@#$%^&*_~\n+~` ''')#removing any punctuation around the word
            if word == "":
                continue#if the word is empty after removing puntuation, then it does not count
            word = word.lower()#making all the letters in the word lowercase
            if word in keywords:#if the word is a keyword
                happinessScore += keywords[word]#the value of the keyword is added to the happiness score
                keywordCount += 1#amount of keywords is increased
                if not isKeyword:#if this tweet isnt a keyword tweet already
                    isKeyword = True#the tweet is turned into a keyword
        if isKeyword:#if the tweet is a keyword tweet
            timeZoneData[timeZone][1] += 1#the amount of keyword tweets in this region is increased by 1
            timeZoneData[timeZone][2] += happinessScore/keywordCount#the average happiness score of the tweet is added to the data for this timezone

    timeZoneOutput = []#list to hold the output for this function
    for region in range(4):#for each region
        tweetCount = timeZoneData[region][0]#variable holds the amount of tweets in the region
        keywordTweetCount = timeZoneData[region][1]##variable holds the amount of keyword tweets in the region
        totalHappinessScore = timeZoneData[region][2]#variable holds the total happiness score for the region
        averageHappinessScore = 0 if keywordTweetCount == 0 else totalHappinessScore/keywordTweetCount#the average happiness score is the total happiness score divided by the amount of keywords
                                                        #if the amount of keywords is zero, then the happiness score is 0 
        timeZoneOutput.append((averageHappinessScore, keywordTweetCount, tweetCount))#adding the data for this region to the output list
    keywordsFile.close()
    tweetsFile.close()#closing the IO files
    return timeZoneOutput#returning the output list with the data on all the regions

