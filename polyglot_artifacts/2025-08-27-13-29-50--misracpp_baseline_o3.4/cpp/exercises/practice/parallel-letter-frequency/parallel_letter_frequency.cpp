#include "parallel_letter_frequency.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <map>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t hardware_threads =
        std::max<unsigned int>(1, std::thread::hardware_concurrency());
    const std::size_t num_threads =
        std::min<std::size_t>(hardware_threads, texts.size());

    // Each thread writes into its private counter array to avoid contention.
    std::vector<std::array<int, 26>> partials(num_threads);
    for (auto& arr : partials) {
        arr.fill(0);
    }

    auto worker = [&](std::size_t start, std::size_t end, std::size_t idx) {
        auto& local = partials[idx];
        // locale variable removed; default C locale functions used

        for (std::size_t i = start; i < end; ++i) {
            for (unsigned char ch : texts[i]) {
                if (std::isalpha(ch)) {
                    char lower = static_cast<char>(std::tolower(ch));
                    local[lower - 'a']++;
                }
            }
        }
    };

    std::vector<std::thread> threads;
    const std::size_t chunk_size = texts.size() / num_threads;
    const std::size_t remainder = texts.size() % num_threads;

    std::size_t begin = 0;
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t end = begin + chunk_size + (t < remainder ? 1 : 0);
        threads.emplace_back(worker, begin, end, t);
        begin = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    std::map<char, int> result;
    for (char c = 'a'; c <= 'z'; ++c) {
        int sum = 0;
        for (const auto& arr : partials) {
            sum += arr[c - 'a'];
        }
        if (sum > 0) {
            result[c] = sum;
        }
    }
    return result;
}

}  // namespace parallel_letter_frequency
