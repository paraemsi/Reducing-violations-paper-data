#include "parallel_letter_frequency.h"

#include <future>
#include <thread>
#include <unordered_map>
#include <locale>
#include <algorithm>
#include <utility>
#include <string_view>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> std::map<char, std::uint32_t>
{
    std::map<char, std::uint32_t> total_counts{};

    if (texts.empty()) {
        return total_counts;
    }

    const std::locale loc{};
    std::vector<std::future<std::unordered_map<char, std::uint32_t>>> futures{};
    futures.reserve(texts.size());

    const auto worker = [&loc](const std::string_view& text) -> std::unordered_map<char, std::uint32_t> {
        std::unordered_map<char, std::uint32_t> local_counts{};

        for (const char ch : text) {
            if (std::isalpha(ch, loc) != 0) {
                const char lower_ch = std::tolower(ch, loc);
                ++local_counts[lower_ch];
            }
        }

        return local_counts;
    };

    for (const std::string_view& text : texts) {
        futures.emplace_back(std::async(std::launch::async, worker, std::cref(text)));
    }

    for (auto& fut : futures) {
        const auto local_counts = fut.get();
        for (const auto& kv : local_counts) {
            total_counts[kv.first] += kv.second;
        }
    }

    return total_counts;
}

} // namespace parallel_letter_frequency
