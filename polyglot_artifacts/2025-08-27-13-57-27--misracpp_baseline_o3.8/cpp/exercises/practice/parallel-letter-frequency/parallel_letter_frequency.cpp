#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cstddef>
#include <array>
#include <cctype>
#include <map>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const unsigned int hw_threads = std::thread::hardware_concurrency();
    const std::size_t max_threads = hw_threads == 0 ? 2 : hw_threads;
    const std::size_t num_threads = std::min<std::size_t>(texts.size(), max_threads);

    // One frequency table per thread
    std::vector<std::array<int, 26>> partials(num_threads);
    for (auto& arr : partials) {
        arr.fill(0);
    }

    auto worker = [&](std::size_t thread_id) {
        const std::size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
        const std::size_t begin = thread_id * chunk_size;
        const std::size_t end = std::min<std::size_t>(texts.size(), begin + chunk_size);

        auto& counts = partials[thread_id];
        for (std::size_t i = begin; i < end; ++i) {
            for (unsigned char ch : texts[i]) {
                if (std::isalpha(ch)) {
                    counts[std::tolower(ch) - 'a']++;
                }
            }
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (std::size_t id = 0; id < num_threads; ++id) {
        threads.emplace_back(worker, id);
    }
    for (auto& t : threads) {
        t.join();
    }

    frequency_map result;
    for (int i = 0; i < 26; ++i) {
        int total = 0;
        for (const auto& arr : partials) {
            total += arr[i];
        }
        if (total > 0) {
            result[static_cast<char>('a' + i)] = total;
        }
    }
    return result;
}

}  // namespace parallel_letter_frequency
