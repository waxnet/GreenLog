#include <unordered_map>
#include <string>

#include "counter.h"

namespace counter {
    std::unordered_map<std::string, int> counters;

    // internal counter functions
    static bool doesKeyExist(const std::string key)
    {
        return (counters.find(key) != counters.end());
    }

    // counter functions
    void counter::increaseValue(const std::string key)
    {
        if (doesKeyExist(key)) {
            counters[key] = (counters[key] + 1);
        } else {
            counters[key] = 0;
        }
    }
    int counter::getValue(const std::string key)
    {
        if (doesKeyExist(key)) {
            return counters[key];
        } else {
            return 0;
        }
    }
}
