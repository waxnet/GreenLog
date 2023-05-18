import requests

def build_url(data): # build Roblox CDN url for the asset from file data
    url = f"https://" + data[20] + data[21] + ".rbxcdn.com/"
    for number in range(32):
        url += data[number + 34]
    return url

def get_content(url): # make http request
    request = requests.get(url)
    if request.ok:
        return request.content
