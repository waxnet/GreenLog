import pystyle

color = pystyle.Colors.DynamicMIX((pystyle.Col.white, pystyle.Col.light_gray)) # text color

def out(text): # colored output
    print(pystyle.Colorate.Horizontal(color, text))

def inp(text): # colored input
    data = input(pystyle.Colorate.Horizontal(color, f"{text} :") + " ")
    return data
