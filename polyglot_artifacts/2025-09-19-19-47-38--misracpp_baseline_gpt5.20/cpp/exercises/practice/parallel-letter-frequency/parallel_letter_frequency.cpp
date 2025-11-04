#include "parallel_letter_frequency.h"

#include <cctype>
#include <future>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace {

// Count frequency of letters (a-z, case-insensitive) in a single string.
parallel_letter_frequency::frequency_map count_in_string(std::string_view s) {
    parallel_letter_frequency::frequency_map local;
    for (unsigned char uch : s) {
        if (std::isalpha(uch)) {
            char lower = static_cast<char>(std::tolower(uch));
            if (lower >= 'a' && lower <= 'z') {
                ++local[lower];
            }
        }
    }
    return local;
}

}  // namespace

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    std::vector<std::future<frequency_map>> tasks;
    tasks.reserve(texts.size());

    for (const auto& s : texts) {
        tasks.emplace_back(std::async(std::launch::async, [s]() {
            return count_in_string(s);
        }));
    }

    frequency_map total;
    for (auto& f : tasks) {
        frequency_map part = f.get();
        for (const auto& [ch, cnt] : part) {
            total[ch] += cnt;
        }
    }
    return total;
}

}  // namespace parallel_letter_frequency
