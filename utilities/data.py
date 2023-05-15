import sys
import os

current_folder = os.path.dirname(sys.argv[0])

sounds_folder = os.path.join(os.getenv("temp"), "Roblox", "sounds")
http_folder = os.path.join(os.getenv("temp"), "Roblox", "http")

downloads_dump = os.path.join(current_folder, ".dump", "downloads")
sounds_dump = os.path.join(current_folder, ".dump", "sounds")
http_dump = os.path.join(current_folder, ".dump", "http")

sounds_output = os.path.join(current_folder, ".output", "sounds")
http_audios = os.path.join(current_folder, ".output", "http", "audios")
http_images = os.path.join(current_folder, ".output", "http", "images")

selected_timeout = 15
timeout = 15

resets = 0
