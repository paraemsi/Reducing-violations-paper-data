#include "parallel_letter_frequency.h"

#include <array>
#include <algorithm>
#include <cctype>
#include <thread>
#include <string_view>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t hw_threads = std::thread::hardware_concurrency();
    const std::size_t num_threads =
        std::max<std::size_t>(1, std::min(hw_threads ? hw_threads : 1, texts.size()));

    const std::size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;

    std::vector<std::array<int, 26>> partial(num_threads);
    for (auto& arr : partial) {
        arr.fill(0);
    }

    std::vector<std::thread> workers;
    workers.reserve(num_threads);

    for (std::size_t t = 0; t < num_threads; ++t) {
        const std::size_t start = t * chunk_size;
        const std::size_t end = std::min(texts.size(), start + chunk_size);

        workers.emplace_back([&, t, start, end]() {
            auto& local = partial[t];
            for (std::size_t i = start; i < end; ++i) {
                for (unsigned char ch : texts[i]) {
                    if (std::isalpha(ch)) {
                        local[std::tolower(ch) - 'a']++;
                    }
                }
            }
        });
    }

    for (auto& th : workers) {
        th.join();
    }

    std::array<int, 26> total{};
    total.fill(0);
    for (const auto& arr : partial) {
        for (std::size_t i = 0; i < 26; ++i) {
            total[i] += arr[i];
        }
    }

    frequency_map result;
    for (std::size_t i = 0; i < 26; ++i) {
        if (total[i] > 0) {
            result[static_cast<char>('a' + i)] = total[i];
        }
    }

    return result;
}

}
