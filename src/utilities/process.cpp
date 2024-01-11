#include <Windows.h>
#include <TlHelp32.h>
#include <thread>
#include <chrono>

#include "process.h"

namespace process {
    // find a process and return its id
    int process::findProcess(const char* processName)
    {
        // process id
        int processID = 0;

        // create snapshot
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (INVALID_HANDLE_VALUE == snapshot)
        {
            return 0;
        }

        // create process entry
        PROCESSENTRY32 processEntry{};
        processEntry.dwSize = sizeof(PROCESSENTRY32);

        // find process id
        BOOL firstProcess = Process32First(snapshot, &processEntry);

        while (firstProcess) {
            if (strcmp(processName, processEntry.szExeFile) == 0) {
                processID = processEntry.th32ProcessID;
                break;
            }

            firstProcess = Process32Next(snapshot, &processEntry);
        }
        CloseHandle(snapshot);

        // return process id
        return processID;
    }

    // kill a process
    void process::killProcess(const int processID)
    {
        HANDLE processHandle = OpenProcess(PROCESS_TERMINATE, false, processID);
        TerminateProcess(processHandle, 1);
        CloseHandle(processHandle);
    }

    // wait for process to start and return its id
    int process::waitForProcess(const char* processName)
    {
        int processID = findProcess(processName);

        while (processID == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            processID = findProcess(processName);
        }

        return processID;
    }
}
