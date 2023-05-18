import sys
import os

# current script folder
current_folder = os.path.dirname(sys.argv[0])

# Roblox temp files folders
sounds_folder = os.path.join(os.getenv("temp"), "Roblox", "sounds")
http_folder = os.path.join(os.getenv("temp"), "Roblox", "http")

# dump folders
downloads_dump = os.path.join(current_folder, ".dump", "downloads")
sounds_dump = os.path.join(current_folder, ".dump", "sounds")
http_dump = os.path.join(current_folder, ".dump", "http")

# output folders
sounds_output = os.path.join(current_folder, ".output", "sounds")
http_audios = os.path.join(current_folder, ".output", "http", "audios")
http_images = os.path.join(current_folder, ".output", "http", "images")

# timer data
selected_timeout = 15
timeout = 15

# timer reset counter
resets = 0
