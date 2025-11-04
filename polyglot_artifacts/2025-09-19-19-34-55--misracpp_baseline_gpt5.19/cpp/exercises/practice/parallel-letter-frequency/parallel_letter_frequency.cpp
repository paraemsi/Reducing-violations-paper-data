#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <future>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

namespace {
    // Count letter frequencies (a-z, case-insensitive) in a single text.
    std::array<int, 26> count_text(std::string_view text) {
        std::array<int, 26> counts{};
        counts.fill(0);

        for (unsigned char uc : text) {
            if (std::isalpha(uc)) {
                unsigned char lower = static_cast<unsigned char>(std::tolower(uc));
                if (lower >= 'a' && lower <= 'z') {
                    ++counts[lower - 'a'];
                }
            }
        }
        return counts;
    }
}  // namespace

frequency_map frequency(const std::vector<std::string_view>& texts) {
    // Launch one async task per text to count locally, then reduce.
    std::vector<std::future<std::array<int, 26>>> tasks;
    tasks.reserve(texts.size());

    const bool parallelize = texts.size() > 1;

    for (const auto& t : texts) {
        // Use async for parallel runs; for single input, defer to avoid thread overhead.
        auto policy = parallelize ? std::launch::async : std::launch::deferred;
        tasks.emplace_back(std::async(policy, count_text, t));
    }

    std::array<int, 26> total{};
    total.fill(0);

    for (auto& fut : tasks) {
        auto partial = fut.get();
        for (std::size_t i = 0; i < 26; ++i) {
            total[i] += partial[i];
        }
    }

    frequency_map result;
    for (std::size_t i = 0; i < 26; ++i) {
        if (total[i] > 0) {
            result.emplace(static_cast<char>('a' + static_cast<int>(i)), total[i]);
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
