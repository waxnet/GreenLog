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
    static std::string combineRootToKey(const std::string root, const std::string key)
    {
        return (root + "_" + key);
    }

    // counter functions
    void counter::increaseValue(const std::string root, const std::string key)
    {
        std::string fullKey = combineRootToKey(root, key);

        if (doesKeyExist(fullKey)) {
            counters[fullKey] = (counters[fullKey] + 1);
        } else {
            counters[fullKey] = 0;
        }
    }
    int counter::getValue(const std::string root, const std::string key)
    {
        std::string fullKey = combineRootToKey(root, key);

        if (doesKeyExist(fullKey)) {
            return counters[fullKey];
        } else {
            return 0;
        }
    }
}
