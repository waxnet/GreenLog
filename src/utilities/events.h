#pragma once

#include "../data/timer.h"

namespace events {
    class fileObserver {
    public:
        fileObserver(std::filesystem::path path);
        void stop();
    private:
        void task(std::filesystem::path path) const;
        bool running;
        std::thread thread;
    };
}
