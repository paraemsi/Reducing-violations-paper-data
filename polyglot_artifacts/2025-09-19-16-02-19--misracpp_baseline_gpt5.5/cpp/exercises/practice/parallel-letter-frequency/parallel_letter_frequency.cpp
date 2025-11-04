#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <string_view>
#include <future>
#include <thread>

namespace parallel_letter_frequency {

namespace {
// Count letters a-z (case-insensitive) in a range of strings.
frequency_map count_range(std::vector<std::string_view>::const_iterator first,
                          std::vector<std::string_view>::const_iterator last) {
    frequency_map local;
    for (auto it = first; it != last; ++it) {
        std::string_view s = *it;
        for (unsigned char ch : s) {
            if (std::isalpha(ch)) {
                char lower = static_cast<char>(std::tolower(ch));
                if (lower >= 'a' && lower <= 'z') {
                    ++local[lower];
                }
            }
        }
    }
    return local;
}
}  // namespace

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t hw = std::max(1u, std::thread::hardware_concurrency());
    const std::size_t tasks = std::min<std::size_t>(hw, texts.size());
    const std::size_t chunk = (texts.size() + tasks - 1) / tasks;

    std::vector<std::future<frequency_map>> futures;
    futures.reserve(tasks);

    for (std::size_t i = 0; i < tasks; ++i) {
        auto begin = texts.begin() + static_cast<std::ptrdiff_t>(i * chunk);
        auto end = (i + 1 == tasks)
                       ? texts.end()
                       : texts.begin() + static_cast<std::ptrdiff_t>((i + 1) * chunk);
        if (begin >= texts.end()) {
            break;
        }
        futures.emplace_back(std::async(std::launch::async, [begin, end] {
            return count_range(begin, end);
        }));
    }

    frequency_map result;
    for (auto& fut : futures) {
        frequency_map part = fut.get();
        for (const auto& [ch, cnt] : part) {
            result[ch] += cnt;
        }
    }

    return result;
}

frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}  // namespace parallel_letter_frequency
