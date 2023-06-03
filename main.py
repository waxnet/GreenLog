from utilities import (
    enviroment,
    process,
    banner,
    data,
    cmd,
    io
)
import keyboard
import time

class green_log():
    def __init__(self):
        super(green_log, self).__init__()
        
        self.load() # setup console
        self.main() # start greenlog
    
    def load(self):
        cmd.execute(["title GreenLog", "mode con: cols=120 lines=30", "cls"]) # set console title and size
        banner.display() # display banner
        time.sleep(1)
    
    def main(self):
        # check if temp files already exist
        mode = ""
        if enviroment.check_path(data.http_folder):
            mode = io.inp("Would you like to perform a static dump? (y, n)").lower()

        ## static dump
        if mode == "y":
            # starting message
            io.out("\nStarting static dump...")
            io.out("")

            # clean, setup and prepare folders for dumping
            io.out("Setting up folders...")
            enviroment.set_folders([
                data.downloads_dump,
                data.sounds_dump,
                data.http_dump,
                
                data.sounds_output,
                data.http_images,
                data.http_audios,
            ])

            # kill Roblox process if running
            roblox_process = process.find_process("RobloxPlayerBeta.exe")
            if roblox_process:
                io.out("Killing Roblox process...")
                roblox_process.kill()
                roblox_process.wait()

            # dump data
            io.out("Dumping data...")
            enviroment.dump_folder(data.sounds_folder, data.sounds_dump)
            enviroment.dump_folder(data.http_folder, data.http_dump)
            
            # parse data and extract assets
            io.out("Parsing data... (this might take a couple of minutes)")
            enviroment.parse_folder(data.sounds_dump)
            enviroment.parse_folder(data.http_dump)
        
        ## dynamic dump
        else:
            # starting message
            io.out("\nStarting dynamic dump...")
            io.out("")

            # request amount of seconds before starting the dumping phase
            assets_loading_process_timeout = io.inp("Enter a timeout in seconds for the assets loading process (10 min, 30 max)")
            if assets_loading_process_timeout != "":
                try:
                    assets_loading_process_timeout = int(assets_loading_process_timeout)

                    # limit the amount of seconds
                    if assets_loading_process_timeout < 10:
                        assets_loading_process_timeout = 10
                    elif assets_loading_process_timeout > 30:
                        assets_loading_process_timeout = 30

                    # set timer selected timeout and current seconds
                    data.selected_timeout = assets_loading_process_timeout
                    data.timeout = assets_loading_process_timeout
                except ValueError:
                    pass
            io.out("")
            
            # kill Roblox process if running
            roblox_process = process.find_process("RobloxPlayerBeta.exe")
            if roblox_process:
                io.out("Killing already running Roblox process...")
                roblox_process.kill()
                roblox_process.wait()
            
            # clean, setup and prepare folders for dumping
            io.out("Setting up folders...")
            enviroment.set_folders([
                data.sounds_folder,
                data.http_folder,
                
                data.downloads_dump,
                data.sounds_dump,
                data.http_dump,
                
                data.sounds_output,
                data.http_images,
                data.http_audios
            ])
            
            # setup file observers (used to check if new assets are loaded)
            io.out("Starting file observers...")
            sounds_observer = enviroment.set_observer(data.sounds_folder)
            http_observer = enviroment.set_observer(data.http_folder)
            sounds_observer.start()
            http_observer.start()
            
            # wait for Roblox process to start
            io.out("You can now open Roblox, waiting for Roblox...")
            roblox_process = process.wait_for_process("RobloxPlayerBeta.exe")
            
            # start the timer
            io.out("Starting timer... (the timer will reset every time a new asset is loaded)")
            while data.timeout > 0:
                cmd.execute([f"title GreenLog - {data.timeout} seconds left - {data.resets} timer resets"])
                data.timeout -= 1
                time.sleep(1)
            cmd.execute(["title GreenLog"])
            
            # stop file observers
            io.out("The timer has reached its timeout, stopping file observers...")
            sounds_observer.stop()
            http_observer.stop()
            sounds_observer.join()
            http_observer.join()
            
            # kill Roblox process
            io.out("Killing Roblox process...")
            roblox_process.kill()
            
            # dump loaded data
            io.out("Dumping data...")
            enviroment.dump_folder(data.sounds_folder, data.sounds_dump)
            enviroment.dump_folder(data.http_folder, data.http_dump)
            
            # parse data and extract assets
            io.out("Parsing data... (this might take a couple of minutes)")
            enviroment.parse_folder(data.sounds_dump)
            enviroment.parse_folder(data.http_dump)
        
        io.out("\nDone! Check the \".output\" folder to see the extracted files.")
        io.out("Press any key to exit...")
        keyboard.read_key()
        exit(0)

if __name__ == "__main__":
    green_log()
