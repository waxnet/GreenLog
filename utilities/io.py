import pystyle

color = pystyle.Colors.DynamicMIX((pystyle.Col.white, pystyle.Col.light_gray))

def out(text):
    print(pystyle.Colorate.Horizontal(color, text))

def inp(text, colon = True):
    if colon:
        input_text = pystyle.Colorate.Horizontal(color, f"{text} :") + " "
    else:
        input_text = pystyle.Colorate.Horizontal(color, text)
    
    data = input(input_text)
    return data
