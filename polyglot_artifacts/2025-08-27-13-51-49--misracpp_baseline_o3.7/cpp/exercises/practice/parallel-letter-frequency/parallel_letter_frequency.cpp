#include "parallel_letter_frequency.h"
#include <algorithm>
#include <cctype>
#include <thread>
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& strings) {
    if (strings.empty()) {
        return {};
    }

    const unsigned int hw_threads = std::thread::hardware_concurrency();
    const std::size_t max_threads = hw_threads == 0 ? 2 : hw_threads;
    const std::size_t num_threads = std::min<std::size_t>(strings.size(), max_threads);

    std::vector<std::thread> workers;
    std::vector<std::map<char, int>> partials(num_threads);

    // Divide the input among the worker threads.
    const std::size_t block_size = (strings.size() + num_threads - 1) / num_threads;

    auto worker = [&](std::size_t start, std::size_t end, std::size_t idx) {
        auto &local = partials[idx];
        for (std::size_t i = start; i < end; ++i) {
            for (char ch : strings[i]) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                    // Only count standard ASCII lowercase letters 'a'–'z'
                    if (lower >= 'a' && lower <= 'z') {
                        ++local[lower];
                    }
                }
            }
        }
    };

    for (std::size_t idx = 0; idx < num_threads; ++idx) {
        std::size_t start = idx * block_size;
        if (start >= strings.size()) {
            break;
        }
        std::size_t end = std::min(strings.size(), start + block_size);
        workers.emplace_back(worker, start, end, idx);
    }

    for (auto &t : workers) {
        t.join();
    }

    // Merge partial results.
    std::map<char, int> result;
    for (const auto &local : partials) {
        for (const auto &pair : local) {
            result[pair.first] += pair.second;
        }
    }

    return result;
}

}
