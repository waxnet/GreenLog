import os

def execute(commands): # execute multiple system commands
    for command in commands:
        os.system(command)
