from utilities import (
    http,
    data
)
import watchdog.observers
import watchdog.events
import shutil
import magic
import os

class file_event_handler(watchdog.events.LoggingEventHandler):
    def on_created(self, event):
        data.timeout = data.selected_timeout
        data.resets += 1

def set_folders(paths):
    for path in paths:
        if not os.path.exists(path):
            os.makedirs(path)
        else:
            for file in os.listdir(path):
                os.remove(os.path.join(path, file))

def set_observer(path):
    observer = watchdog.observers.Observer()
    observer.schedule(file_event_handler(), path, recursive=True)
    return observer

def dump_folder(path, destination):
    for file in os.listdir(path):
        shutil.copy2(os.path.join(path, file), destination)

def parse_folder(path):
    file_counter = 0
    sound_counter = 0
    image_counter = 0

    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        
        if not file.startswith("RBX"):
            with open(file_path, "r", errors="ignore") as data_file:
                data_file_first_line = data_file.readline()
                data_file_content = data_file.read()
                data_file.close()
            
            if "binary/octet-stream" in data_file_content:
                file_url = http.build_url(data_file_first_line)
                file_content = http.get_content(file_url)
                
                if file_content:
                    downloaded_file_path = os.path.join(data.downloads_dump, file)
                    with open(downloaded_file_path, "wb") as downloaded_file:
                        downloaded_file.write(file_content)
                        downloaded_file.close()
                    
                    file_type = magic.from_file(downloaded_file_path)
                    file_extension = ""
                    
                    if "audio" in file_type:
                        new_downloaded_file_directory = os.path.join(data.http_audios, f"{sound_counter}.ogg")
                        os.rename(downloaded_file_path, new_downloaded_file_directory)
                        sound_counter += 1
                    elif "image" in file_type:
                        new_downloaded_file_directory = os.path.join(data.http_images, f"{image_counter}.jpg")
                        os.rename(downloaded_file_path, new_downloaded_file_directory)
                        image_counter += 1
                    else:
                        continue
        else:
            with open(file_path, "rb") as data_file:
                data_file_first_line = data_file.read()
                data_file.close()
            
            with open(os.path.join(data.sounds_output, f"{file_counter}.ogg"), "wb") as parsed_file:
                parsed_file.write(data_file_first_line)
                parsed_file.close()
            
            file_counter += 1
