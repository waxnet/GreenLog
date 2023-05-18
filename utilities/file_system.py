from utilities import (
    http,
    data
)
import watchdog.observers
import watchdog.events
import shutil
import magic
import os

# file events for observers
class file_event_handler(watchdog.events.LoggingEventHandler):
    def on_created(self, _):
        data.timeout = data.selected_timeout
        data.resets += 1

# setup paths
def set_folders(paths):
    for path in paths:
        if not os.path.exists(path):
            os.makedirs(path)
        else:
            for file in os.listdir(path):
                os.remove(os.path.join(path, file))

# setup observer
def set_observer(path):
    observer = watchdog.observers.Observer()
    observer.schedule(file_event_handler(), path, recursive=True)
    return observer

# dump folder content into another folder
def dump_folder(path, destination):
    for file in os.listdir(path):
        shutil.copy2(os.path.join(path, file), destination)

# parse dumped data
def parse_folder(path):
    sound_counter = 0 # sound counter
    audio_counter = 0 # audio counter
    image_counter = 0 # image counter

    for file in os.listdir(path):
        file_path = os.path.join(path, file)
        
        if not file.startswith("RBX"): # check file name
            with open(file_path, "r", errors="ignore") as data_file:
                data_file_first_line = data_file.readline()
                data_file_content = data_file.read()
                data_file.close()
            
            if "binary/octet-stream" in data_file_content: # check if file is valid
                file_url = http.build_url(data_file_first_line) # build the Roblox CDN url for the asset
                file_content = http.get_content(file_url) # download the asset
                
                if file_content: # check if file was downloaded successfully
                    # write file to the download folder
                    downloaded_file_path = os.path.join(data.downloads_dump, file)
                    with open(downloaded_file_path, "wb") as downloaded_file:
                        downloaded_file.write(file_content)
                        downloaded_file.close()
                    
                    # get and check file type
                    file_type = magic.from_file(downloaded_file_path)
                    if "audio" in file_type:
                        new_downloaded_file_directory = os.path.join(data.http_audios, f"{audio_counter}.ogg") # write file to the http audio folder
                        os.rename(downloaded_file_path, new_downloaded_file_directory)
                        audio_counter += 1
                    elif "image" in file_type:
                        new_downloaded_file_directory = os.path.join(data.http_images, f"{image_counter}.jpg") # write file to the http image folder
                        os.rename(downloaded_file_path, new_downloaded_file_directory)
                        image_counter += 1
                    else:
                        continue
        else:
            # rewrite file as ogg in the sounds output folder
            with open(file_path, "rb") as data_file:
                data_file_first_line = data_file.read()
                data_file.close()
            
            with open(os.path.join(data.sounds_output, f"{sound_counter}.ogg"), "wb") as parsed_file:
                parsed_file.write(data_file_first_line)
                parsed_file.close()
            
            sound_counter += 1 # update sound counter
