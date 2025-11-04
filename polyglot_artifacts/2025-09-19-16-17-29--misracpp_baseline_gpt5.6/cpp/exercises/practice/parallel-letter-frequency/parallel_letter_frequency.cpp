#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    frequency_map total;

    if (texts.empty()) {
        return total;
    }

    const unsigned int hwc = std::thread::hardware_concurrency();
    const std::size_t n = texts.size();
    const std::size_t num_threads = std::min<std::size_t>(n, hwc ? static_cast<std::size_t>(hwc) : 1);

    std::vector<frequency_map> partials(num_threads);
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    auto worker = [&](std::size_t start, std::size_t end, std::size_t idx) {
        auto& local = partials[idx];
        for (std::size_t i = start; i < end; ++i) {
            for (unsigned char ch : texts[i]) {
                if (std::isalpha(ch)) {
                    char lc = static_cast<char>(std::tolower(ch));
                    if (lc >= 'a' && lc <= 'z') {
                        ++local[lc];
                    }
                }
            }
        }
    };

    const std::size_t base = n / num_threads;
    const std::size_t rem = n % num_threads;
    std::size_t start = 0;
    if (num_threads == 1) {
        worker(0, n, 0);
    } else {
        for (std::size_t t = 0; t < num_threads; ++t) {
            const std::size_t count = base + (t < rem ? 1 : 0);
            const std::size_t end = start + count;
            threads.emplace_back(worker, start, end, t);
            start = end;
        }
    }

    for (auto& th : threads) {
        th.join();
    }

    for (const auto& m : partials) {
        for (const auto& kv : m) {
            total[kv.first] += kv.second;
        }
    }

    return total;
}

frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}
