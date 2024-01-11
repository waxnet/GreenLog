#include <filesystem>
#include <thread>

#include "events.h"

namespace events {
    // file observer constructor
    fileObserver::fileObserver(std::filesystem::path path) {
        this->running = true;
        this->thread = std::thread(&fileObserver::task, this, path);
    }

    // stop file observer
    void fileObserver::stop() {
        this->running = false;
        this->thread.join();
    }

    // file observer thread task
    void fileObserver::task(std::filesystem::path path) const {
        int fileAmount = 0;

        while (this->running) {
            // count files
            int newFileAmount = 0;
            for (auto& entry : std::filesystem::directory_iterator(path)) {
                if (entry.is_regular_file()) {
                    newFileAmount++;
                }
            }

            // check if files have been added to the path
            if (newFileAmount != fileAmount) {
                fileAmount = newFileAmount;

                timer::time = timer::start;
                timer::resets++;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}