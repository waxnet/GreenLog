from utilities import (
    file_system,
    process,
    banner,
    data,
    cmd,
    io
)
import msvcrt
import random
import time
import os

class green_log():
    def __init__(self):
        super(green_log, self).__init__()
        
        self.load()
        self.main()
    
    def load(self):
        cmd.execute(["title GreenLog", "mode con: cols=120 lines=30", "cls"])
        banner.display()
        time.sleep(1)
    
    def main(self):
        assets_loading_process_timeout = io.inp("Enter a timeout for the assets loading process (15 recommended)")
        if assets_loading_process_timeout != "":
            try:
                assets_loading_process_timeout = int(assets_loading_process_timeout)
                data.selected_timeout = assets_loading_process_timeout
                data.timeout = assets_loading_process_timeout
            except ValueError:
                pass
        io.out("\n")
        
        roblox_process = process.find_process("RobloxPlayerBeta.exe")
        if roblox_process:
            io.out("Killing already running Roblox process...")
            roblox_process.kill()
            roblox_process.wait()
        
        io.out("Setting up folders...")
        file_system.set_folders([
            data.sounds_folder,
            data.http_folder,
            
            data.downloads_dump,
            data.sounds_dump,
            data.http_dump,
            
            data.sounds_output,
            data.http_images,
            data.http_audios
        ])
        
        io.out("Starting file observers...")
        sounds_observer = file_system.set_observer(data.sounds_folder)
        http_observer = file_system.set_observer(data.http_folder)
        
        sounds_observer.start()
        http_observer.start()
        
        io.out("You can now open Roblox, waiting for Roblox...")
        roblox_process = process.wait_for_process("RobloxPlayerBeta.exe")
        
        io.out("Starting timer... (the timer will reset every time a new asset is loaded)")
        while data.timeout > 0:
            cmd.execute([f"title GreenLog - {data.timeout} seconds left - {data.resets} timer resets"])
            data.timeout -= 1
            time.sleep(1)
        cmd.execute(["title GreenLog"])
        
        io.out("The timer has reached its timeout, stopping file observers...")
        sounds_observer.stop()
        http_observer.stop()
        sounds_observer.join()
        http_observer.join()
        
        io.out("Killing Roblox process...")
        roblox_process.kill()
        
        io.out("Dumping data...")
        file_system.dump_folder(data.sounds_folder, data.sounds_dump)
        file_system.dump_folder(data.http_folder, data.http_dump)
        
        io.out("Parsing data... (this might take a couple of minutes)")
        file_system.parse_folder(data.sounds_dump)
        file_system.parse_folder(data.http_dump)
        
        io.out("\nDone! Check the \".output\" folder to see the extracted files.")
        io.out("Press any key to exit...")
        msvcrt.getch()
        exit()

green_log()
