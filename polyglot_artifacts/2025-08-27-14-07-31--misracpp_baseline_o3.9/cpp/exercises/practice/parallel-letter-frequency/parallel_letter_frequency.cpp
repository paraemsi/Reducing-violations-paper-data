#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <map>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {


frequency_map frequency(const std::vector<std::string_view>& texts)
{
    if (texts.empty()) {
        return {};
    }

    auto worker = [](std::string_view text) -> frequency_map {
        frequency_map local;
        for (char ch : text) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++local[lower];
            }
        }
        return local;
    };

    std::vector<std::future<frequency_map>> futures;
    futures.reserve(texts.size());

    for (const auto& text : texts) {
        futures.emplace_back(std::async(std::launch::async, worker, text));
    }

    frequency_map result;
    for (auto& fut : futures) {
        for (const auto& [ch, cnt] : fut.get()) {
            result[ch] += cnt;
        }
    }

    return result;
}

} // namespace parallel_letter_frequency
