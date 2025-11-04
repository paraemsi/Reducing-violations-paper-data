#include "parallel_letter_frequency.h"

#include <algorithm>
#include <array>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

namespace {
inline bool is_ascii_letter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}
inline char to_lower_ascii(char c) {
    if (c >= 'A' && c <= 'Z') return static_cast<char>(c - 'A' + 'a');
    return c;
}
}  // namespace

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t hc = std::thread::hardware_concurrency();
    const std::size_t num_threads =
        std::min<std::size_t>(texts.size(), hc ? hc : 2u);

    // Per-thread letter counters (a..z).
    std::vector<std::array<int, 26>> local_counts(num_threads);
    for (auto& arr : local_counts) {
        arr.fill(0);
    }

    auto worker = [&](std::size_t idx) {
        const std::size_t n = texts.size();
        const std::size_t chunk = n / num_threads;
        const std::size_t rem = n % num_threads;

        const std::size_t begin = idx * chunk + std::min<std::size_t>(idx, rem);
        const std::size_t end = begin + chunk + (idx < rem ? 1 : 0);

        auto& counts = local_counts[idx];
        for (std::size_t i = begin; i < end; ++i) {
            const std::string_view s = texts[i];
            for (char c : s) {
                if (!is_ascii_letter(c)) continue;
                c = to_lower_ascii(c);
                counts[static_cast<std::size_t>(c - 'a')] += 1;
            }
        }
    };

    // Launch threads.
    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (std::size_t t = 0; t < num_threads; ++t) {
        threads.emplace_back(worker, t);
    }
    for (auto& th : threads) {
        th.join();
    }

    // Reduce per-thread counts into the final frequency map.
    frequency_map result;
    for (int letter = 0; letter < 26; ++letter) {
        int total = 0;
        for (const auto& arr : local_counts) {
            total += arr[letter];
        }
        if (total != 0) {
            result[static_cast<char>('a' + letter)] = total;
        }
    }

    return result;
}


}
