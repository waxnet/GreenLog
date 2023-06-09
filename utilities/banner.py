import pystyle

color = pystyle.Colors.DynamicMIX((pystyle.Col.dark_gray, pystyle.Col.light_green)) # banner color
banner = """
  ▄████  ██▀███  ▓█████ ▓█████  ███▄    █  ██▓     ▒█████    ▄████ 
 ██▒ ▀█▒▓██ ▒ ██▒▓█   ▀ ▓█   ▀  ██ ▀█   █ ▓██▒    ▒██▒  ██▒ ██▒ ▀█▒
▒██░▄▄▄░▓██ ░▄█ ▒▒███   ▒███   ▓██  ▀█ ██▒▒██░    ▒██░  ██▒▒██░▄▄▄░
░▓█  ██▓▒██▀▀█▄  ▒▓█  ▄ ▒▓█  ▄ ▓██▒  ▐▌██▒▒██░    ▒██   ██░░▓█  ██▓
░▒▓███▀▒░██▓ ▒██▒░▒████▒░▒████▒▒██░   ▓██░░██████▒░ ████▓▒░░▒▓███▀▒
 ░▒   ▒ ░ ▒▓ ░▒▓░░░ ▒░ ░░░ ▒░ ░░ ▒░   ▒ ▒ ░ ▒░▓  ░░ ▒░▒░▒░  ░▒   ▒ 
  ░   ░   ░▒ ░ ▒░ ░ ░  ░ ░ ░  ░░ ░░   ░ ▒░░ ░ ▒  ░  ░ ▒ ▒░   ░   ░ 
░ ░   ░   ░░   ░    ░      ░      ░   ░ ░   ░ ░   ░ ░ ░ ▒  ░ ░   ░ 
      ░    ░        ░  ░   ░  ░         ░     ░  ░    ░ ░        ░ 
                                                                   \n
"""

def display(): # display banner in the middle of the console
    print(pystyle.Colorate.Diagonal(color, pystyle.Center.XCenter(banner)))
