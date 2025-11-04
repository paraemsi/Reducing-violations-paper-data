#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t hardware = std::thread::hardware_concurrency();
    std::size_t num_threads = hardware ? hardware : 2;
    if (num_threads > texts.size()) {
        num_threads = texts.size();
    }

    std::vector<frequency_map> partials(num_threads);
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    auto worker = [&](std::size_t idx_begin, std::size_t idx_end, std::size_t slot) {
        auto& local = partials[slot];
        for (std::size_t i = idx_begin; i < idx_end; ++i) {
            const std::string_view s = texts[i];
            for (unsigned char uc : s) {
                // Count ASCII letters only, case-insensitive
                if ((uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z')) {
                    char lc = static_cast<char>(std::tolower(uc));
                    ++local[lc];
                }
            }
        }
    };

    const std::size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t begin = t * chunk_size;
        std::size_t end = std::min(begin + chunk_size, texts.size());
        threads.emplace_back(worker, begin, end, t);
    }

    for (auto& th : threads) {
        th.join();
    }

    frequency_map total;
    for (const auto& m : partials) {
        for (const auto& [ch, cnt] : m) {
            total[ch] += cnt;
        }
    }

    return total;
}

}
