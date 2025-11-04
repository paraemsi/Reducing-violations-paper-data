#include "parallel_letter_frequency.h"

#include <cctype>
#include <thread>
#include <vector>
#include <atomic>
#include <algorithm>  // for std::min
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& input_strings,
                              std::size_t max_workers) {
    const std::size_t n = input_strings.size();
    if (n == 0) {
        return {};
    }

    if (max_workers == 0) {
        max_workers = 1;
    }

    const std::size_t thread_count = std::min(max_workers, n);

    // One local result map per worker thread to eliminate data races.
    std::vector<std::map<char, int>> partial_results(thread_count);

    // Index of the next string a worker has to process.
    std::atomic<std::size_t> next_index{0};

    std::vector<std::thread> workers;
    workers.reserve(thread_count);

    for (std::size_t t = 0; t < thread_count; ++t) {
        workers.emplace_back([&, t] {
            auto& local = partial_results[t];

            while (true) {
                const std::size_t i = next_index.fetch_add(1);
                if (i >= n) {
                    break;
                }

                const std::string_view text = input_strings[i];

                for (unsigned char ch : text) {
                    if (std::isalpha(ch)) {
                        char lower = static_cast<char>(std::tolower(ch));
                        ++local[lower];
                    }
                }
            }
        });
    }

    for (auto& th : workers) {
        th.join();
    }

    // Merge the individual results into a single map.
    std::map<char, int> result;
    for (const auto& local : partial_results) {
        for (const auto& [ch, cnt] : local) {
            result[ch] += cnt;
        }
    }

    return result;
}

} // namespace parallel_letter_frequency
