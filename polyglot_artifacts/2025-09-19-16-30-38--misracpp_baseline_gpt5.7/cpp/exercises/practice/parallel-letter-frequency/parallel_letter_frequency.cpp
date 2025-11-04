#include "parallel_letter_frequency.h"

#include <algorithm>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) noexcept {
    if (texts.empty()) {
        return {};
    }

    std::size_t hw = std::thread::hardware_concurrency();
    if (hw == 0) {
        hw = 2; // sensible fallback if hardware_concurrency is not available
    }
    const std::size_t num_threads = std::min<std::size_t>(hw, texts.size());
    if (num_threads == 1) {
        // Fast path: do it sequentially to avoid thread overhead
        frequency_map result;
        for (const auto& s : texts) {
            for (unsigned char ch : s) {
                if (ch >= 'A' && ch <= 'Z') {
                    ++result[static_cast<char>(ch - 'A' + 'a')];
                } else if (ch >= 'a' && ch <= 'z') {
                    ++result[static_cast<char>(ch)];
                }
            }
        }
        return result;
    }

    std::vector<frequency_map> partials(num_threads);

    auto worker = [&](std::size_t idx) {
        const std::size_t start = idx * texts.size() / num_threads;
        const std::size_t end   = (idx + 1) * texts.size() / num_threads;
        auto& local = partials[idx];

        for (std::size_t i = start; i < end; ++i) {
            const auto& s = texts[i];
            for (unsigned char ch : s) {
                if (ch >= 'A' && ch <= 'Z') {
                    ++local[static_cast<char>(ch - 'A' + 'a')];
                } else if (ch >= 'a' && ch <= 'z') {
                    ++local[static_cast<char>(ch)];
                }
            }
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    for (std::size_t t = 0; t < num_threads; ++t) {
        threads.emplace_back(worker, t);
    }
    for (auto& th : threads) {
        th.join();
    }

    frequency_map result;
    for (const auto& m : partials) {
        for (const auto& kv : m) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}
