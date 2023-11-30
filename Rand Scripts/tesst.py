import requests
from bs4 import BeautifulSoup

save_filters_url = "https://offcampus.uwo.ca/Listings/SaveFilters"
search_listings_url = "https://offcampus.uwo.ca/Listings/SearchListings"

# Create a session to maintain state (cookies, etc.)
session = requests.Session()
filters_payload = {"PageNumber": 7}
fresponse = session.post(save_filters_url, data=filters_payload)
if fresponse.status_code == 200:
    print("sent filters")
    response = session.get(search_listings_url)
    soup = BeautifulSoup(response.content, 'html.parser')
    rental_listing_divs = soup.find_all('div', class_='rental-listing')
    print(len(rental_listing_divs))
