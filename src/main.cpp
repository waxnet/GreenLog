#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <thread>

#include "utilities/environment.h"
#include "utilities/process.h"
#include "utilities/events.h"
#include "utilities/banner.h"
#include "utilities/magic.h"
#include "utilities/cmd.h"
#include "utilities/io.h"

#include "data/timer.h"
#include "data/paths.h"

int main()
{
    // set console title and size
    cmd::execute(new const char* [] {
        "title GreenLog v2.2",
        "mode con: cols=90 lines=20",
        "cls"
    }, 3);

    // banner
    banner::display();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    // ask user for static dump if roblox temp files already exist
    bool doStaticDump = false;
    if (environment::checkPath(paths::roblox::http))
        doStaticDump = (io::inp("Would you like to perform a static dump? (y, n)") == "y");

    //// static dump
    if (doStaticDump) {
        // starting message
        io::out("\nStarting static dump...\n");

        // cleanup folders
        io::out("Setting up folders...");
        environment::cleanFolders(new std::filesystem::path[]{
            paths::greenlog::http,
            paths::greenlog::sounds
        }, 2);

        // kill roblox if its already running
        DWORD robloxProcessID = process::findProcess("RobloxPlayerBeta.exe");
        if (robloxProcessID != 0)
        {
            io::out("Killing already running Roblox process...");
            process::killProcess(robloxProcessID);
        }
    }

    //// dynamic dump
    else {
        // starting message
        io::out("\nStarting dynamic dump...\n");

        // ask user for timer value
        std::string selectedTime = io::inp("Enter the time to wait before the parsing process (10 min, 30 max)");

        if (selectedTime != "")
        {
            int selectedTimeValue;

            // convert selected time to integer and check if conversion succeed
            if (magic::stringToInteger(selectedTime, selectedTimeValue, 15))
            {
                // limit the amount of seconds
                if (selectedTimeValue < 10) {
                    selectedTimeValue = 10;
                } else if (selectedTimeValue > 30) {
                    selectedTimeValue = 30;
                }

                // set timer timeout and current seconds
                timer::start = selectedTimeValue;
                timer::time = selectedTimeValue;
            }
        }
        io::out("");

        // kill roblox if its already running
        DWORD robloxProcessID = process::findProcess("RobloxPlayerBeta.exe");
        if (robloxProcessID != 0)
        {
            io::out("Killing already running Roblox process...");
            process::killProcess(robloxProcessID);
        }

        // cleanup folders
        io::out("Setting up folders...");
        environment::cleanFolders(new std::filesystem::path[]{
            paths::roblox::http,
            paths::roblox::sounds,

            paths::greenlog::http,
            paths::greenlog::sounds
        }, 4);

        // setup file observers
        io::out("Starting file observers...");
        events::fileObserver httpObserver(paths::roblox::http);
        events::fileObserver soundsObserver(paths::roblox::sounds);

        // wait for roblox process to start
        io::out("Waiting for Roblox...");
        process::waitForProcess("RobloxPlayerBeta.exe");

        // start the timer
        io::out("Starting timer... (the timer will reset every time a new asset is loaded)");
        while (timer::time > 0)
        {
            cmd::execute(new const char* [] {
                (
                    "title GreenLog v2.2 - " +
                    std::to_string(timer::time) +
                    " seconds left - " +
                    std::to_string(timer::resets) +
                    " timer resets"
                ).c_str()
            }, 1);

            timer::time--;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        cmd::execute(new const char* [] { "title GreenLog v2.2" }, 1);

        // stop file observers
        io::out("Stopping file observers...");
        httpObserver.stop();
        soundsObserver.stop();

        // kill roblox process if its running
        robloxProcessID = process::findProcess("RobloxPlayerBeta.exe");
        if (robloxProcessID != 0)
        {
            io::out("Killing Roblox process...");
            process::killProcess(robloxProcessID);
        }
    }

    // parse data and extract assets
    io::out("Parsing data... (this might take some time)");
    environment::parseFolders(new std::filesystem::path[]{
        paths::roblox::http,
        paths::roblox::sounds
    }, 2);

    // exit
    io::out("\nDone! Check the \".output\" folder to see the extracted files.");
    io::out("Press any key to exit...");
    (void)_getch();

    return 0;
}
