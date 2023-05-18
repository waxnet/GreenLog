import psutil
import time

def find_process(name): # find a process
    found_process = None
    for process in psutil.process_iter():
        if process.name() == name:
            found_process = process
            break
    return found_process

def wait_for_process(name): # wait for a process to start
    found_process = None
    while not found_process:
        time.sleep(.1)
        for process in psutil.process_iter():
            if process.name() == name:
                found_process = process
                break
    return found_process
