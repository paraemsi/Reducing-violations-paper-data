#include "parallel_letter_frequency.h"

#include <future>
#include <locale>
#include <string_view>
#include <unordered_map>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> std::unordered_map<char, std::uint32_t> {
    if (texts.empty()) {
        return {};
    }

    const std::locale loc {};
    const auto count_single = [&loc](std::string_view str) -> std::unordered_map<char, std::uint32_t> {
        std::unordered_map<char, std::uint32_t> local_counts {};
        for (const char ch : str) {
            if ((std::isalpha(ch, loc) != 0)) {
                const char lower_ch { static_cast<char>(std::tolower(ch, loc)) };
                ++local_counts[lower_ch];
            }
        }
        return local_counts;
    };

    std::vector<std::future<std::unordered_map<char, std::uint32_t>>> futures {};
    futures.reserve(texts.size());

    for (const std::string_view text : texts) {
        futures.emplace_back(std::async(std::launch::async, count_single, text));
    }

    std::unordered_map<char, std::uint32_t> result {};
    for (auto & fut : futures) {
        const std::unordered_map<char, std::uint32_t> local_counts { fut.get() };
        for (const auto & kv : local_counts) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}
