import requests
from bs4 import BeautifulSoup
import csv
from datetime import datetime

# Send the first request to save filters
filters_payload = {
    "Desc": True,
    "PageNumber": 2,
    "requestType": "Normal",
    "MinimumRent": 0,
    "MaximumRent": 7000,
    "NumberOfBedrooms": 0,
    "TenantTypeId": 0,
    "Distance": 0,
    "Posted": 0,
    "AmenitiesCheckList[0].Id": 1,
    "AmenitiesCheckList[1].Id": 2,
    "AmenitiesCheckList[2].Id": 3,
    "AmenitiesCheckList[3].Id": 4,
    "AmenitiesCheckList[4].Id": 5,
    "AmenitiesCheckList[5].Id": 6,
    "AmenitiesCheckList[6].Id": 7,
    "AmenitiesCheckList[7].Id": 8,
    "AmenitiesCheckList[8].Id": 9,
    "AmenitiesCheckList[9].Id": 10,
    "AmenitiesCheckList[10].Id": 11,
    "AmenitiesCheckList[11].Id": 12,
    "AmenitiesCheckList[12].Id": 17,
    "Desc": False,
    "AmenitiesCheckList[0].IsSelected": False,
    "AmenitiesCheckList[1].IsSelected": False,
    "AmenitiesCheckList[2].IsSelected": False,
    "AmenitiesCheckList[3].IsSelected": False,
    "AmenitiesCheckList[4].IsSelected": False,
    "AmenitiesCheckList[5].IsSelected": False,
    "AmenitiesCheckList[6].IsSelected": False,
    "AmenitiesCheckList[7].IsSelected": False,
    "AmenitiesCheckList[8].IsSelected": False,
    "AmenitiesCheckList[9].IsSelected": False,
    "AmenitiesCheckList[10].IsSelected": False,
    "AmenitiesCheckList[11].IsSelected": False,
    "AmenitiesCheckList[12].IsSelected": False,
}


def loadFromCsv(filePath):
    try:
        with open(filePath, 'r', newline='') as file:
            reader = csv.DictReader(file)
            listings = [dict(row) for row in reader]
    except FileNotFoundError:
        listings = []
    return listings


def saveToCsv(filePath, listings):
    desired_order = ["location", "link"]
    with open(filePath, 'w', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=desired_order)
        writer.writeheader()
        writer.writerows(listings)


def getListings():
    save_filters_url = "https://offcampus.uwo.ca/Listings/SaveFilters"
    search_listings_url = "https://offcampus.uwo.ca/Listings/SearchListings"

    # Create a session to maintain state (cookies, etc.)
    session = requests.Session()
    page = 1
    allListings = [
        {"link": "none", "location": datetime.now()}]
    while True:
        print(page)
        filters_payload["PageNumber"] = page
        fresponse = session.post(save_filters_url, data=filters_payload)
        if fresponse.status_code == 200:
            response = session.get(search_listings_url)
            soup = BeautifulSoup(response.content, 'html.parser')
            listings = soup.find_all('div', class_='rental-listing')
            if len(listings) < 2:
                break
            for rental in listings:
                date = rental.find("h4")
                strong = rental.find('strong')
                if date and strong:
                    atag = strong.find("a")
                    dateText = date.text.strip()
                    if "September" in dateText:
                        location = atag.text.strip()
                        link = atag['href']
                        allListings.append(
                            {"link": "https://offcampus.uwo.ca"+link, "location": location})
        page += 1
    return allListings


filePath = "Rand Scripts/rentalListings.csv"
listings = loadFromCsv(filePath=filePath)
newListings = getListings()
for rental in newListings:
    if rental not in listings:
        listings.append(rental)
saveToCsv(filePath=filePath, listings=listings)
