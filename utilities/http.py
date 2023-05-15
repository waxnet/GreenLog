import requests

def build_url(data):
    url = f"https://" + data[20] + data[21] + ".rbxcdn.com/"
    for number in range(32):
        url += data[number + 34]
    return url

def get_content(url):
    request = requests.get(url)
    if request.ok:
        return request.content
