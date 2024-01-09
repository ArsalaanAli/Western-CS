import requests
from bs4 import BeautifulSoup
import csv
from datetime import datetime

# Send the first request to save filters
filters_payload = {
    "Desc": True,
    "PageNumber": 0,
    "MaximumRent": 7000,
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
    page = 0
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
                    location = atag.text.strip()
                    dateText = date.text.strip()
                    if "September" in dateText:
                        link = atag['href']
                        print(location)
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
