file = open("input.txt", "r")

teams = []#array holding all the information for each team

while True:
  #input
  line = file.readline().strip()
  if line == "-1":#checking for end of input
    break

  name = line#reading all input values of team and storing them in variables
  numTurkeys = int(file.readline().strip())
  turkeyWeights = file.readline().strip().split()
  file.readline()#extra readline for the "endTeam" line
  
  for i in range(numTurkeys):
    turkeyWeights[i] = float(turkeyWeights[i])#converting each weight from string into a float
  totalWT = sum(turkeyWeights)
  lightest = min(turkeyWeights)#finding lightest and heaviest weights
  heaviest = max(turkeyWeights)
  avgWeight = totalWT/numTurkeys#calculating avg weight
  teams.append([name, numTurkeys, turkeyWeights, totalWT, heaviest, lightest, avgWeight])#adding all of the team data into the array of teams

for team in teams:#looping through the teams to get a rank for each one
  rank = 1
  for otherTeam in teams:
    if otherTeam[6] > team[6]:#comparing the current team to every other team
      rank+=1#if the other team has a higher avg weight, then the rank of this team is one lower
  team.append(rank)#adding the rank to the data for this team

print("Teams\t  Count   W1     W2     W3     W4     W5     Total WT    Heaviest Tky    Lightest Tky    Av. WT    T Rank")#printing the title
for t in teams:
  formattedName = t[0].ljust(10)
  formattedCount = str(t[1]).ljust(8)
  formattedWeights = ("".join([str(x).ljust(7) for x in t[2]])).ljust(35)
  formattedTotal = str(t[3]).ljust(12)
  formattedHeaviest = str(t[4]).ljust(16)
  formattedLightest = str(t[5]).ljust(16)
  formattedAvg = str(t[6]).ljust(10)
  formattedRank = str(t[7])#formatted every statistic of each team into a string, and then concatenating all the strings together
  formattedString = formattedName + formattedCount + formattedWeights + formattedTotal + formattedHeaviest + formattedLightest + formattedAvg + formattedRank
  print(formattedString)#printing out the formatted string

file.close()#closing input file
