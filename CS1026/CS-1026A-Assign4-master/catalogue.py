from country import Country
class CountryCatalogue:
    def __init__(self, countryFile):
        countryCat = dict()
        self.countryCat = countryCat 
        countryFileOpened = open(countryFile, 'r')
        countryInfo = countryFileOpened.readlines()
        for country in countryInfo[1::]:
            country = country.split("|")
            tempName = country[0]
            tempContinent = country[1]
            tempPop = country[2]
            tempArea = country[3].strip("\n")
            tempCountry = Country(tempName, tempPop, tempArea, tempContinent)
            countryCat[tempName] = tempCountry
    
    def setPopulationOfCountry(self, countryName, value):
        if countryName in self.countryCat:
            self.countryCat[countryName].setPopulation(value)
        else:
            print(countryName, "is not in the Country Catalogue")
    def setAreaOfCountry(self, countryName, value):
        if countryName in self.countryCat:
            self.countryCat[countryName].setArea(value)
        else:
            print(countryName, "is not in the Country Catalogue")
    def setContinentOfCountry(self, countryName, value):
        if countryName in self.countryCat:
            self.countryCat[countryName].setContinent(value)
        else:
            print(countryName, "is not in the Country Catalogue")

    def findCountry(self, country):
        if country in self.countryCat.values():
            return country
        else:
            return None

    def addCountry(self, countryName, pop, area, cont):
        if countryName in self.countryCat:
            return False
        newCountry = Country(countryName, pop, area, cont)
        self.countryCat[countryName] = newCountry
        return True

    def printCountryCatalogue(self):
        for country in self.countryCat.keys():
            print(self.countryCat[country])
    def saveCountryCatalogue(self, fName):
        try:
            newFile = open(fName, "w")
            newFile.write("Country|Continent|Population|Area\n")
            total = 0
            for country in sorted(self.countryCat.keys()):
                cur = self.countryCat[country]
                newFile.write(cur.getName() + "|" + cur.getContinent() + "|" + cur.getPopulation() + "|" + cur.getArea() + "\n")
                total+=1
            return total
        except IOError:
            return -1
        
x = CountryCatalogue("data.txt")
x.printCountryCatalogue()
x.addCountry("Narnia", "asd", "asd", "asd")
x.printCountryCatalogue()
print(x.saveCountryCatalogue("savedFile.txt"))
