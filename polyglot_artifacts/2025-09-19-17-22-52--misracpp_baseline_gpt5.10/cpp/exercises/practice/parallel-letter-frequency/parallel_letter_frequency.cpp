#include "parallel_letter_frequency.h"

#include <array>
#include <thread>
#include <algorithm>
#include <cstddef>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    const std::size_t n_texts = texts.size();
    if (n_texts == 0) {
        return {};
    }

    std::size_t max_threads = std::thread::hardware_concurrency();
    if (max_threads == 0) {
        max_threads = 2;
    }
    const std::size_t workers = std::min<std::size_t>(n_texts, max_threads);

    std::vector<std::array<int, 26>> partials(workers);
    for (auto& a : partials) {
        a.fill(0);
    }

    std::vector<std::thread> threads;
    threads.reserve(workers);

    auto worker = [&](std::size_t begin, std::size_t end, std::size_t dest_index) {
        auto& acc = partials[dest_index];
        for (std::size_t i = begin; i < end; ++i) {
            std::string_view s = texts[i];
            for (unsigned char uc : s) {
                char c = static_cast<char>(uc);
                if (c >= 'A' && c <= 'Z') {
                    c = static_cast<char>(c - 'A' + 'a');
                }
                if (c >= 'a' && c <= 'z') {
                    ++acc[c - 'a'];
                }
            }
        }
    };

    std::size_t base = n_texts / workers;
    std::size_t extra = n_texts % workers;
    std::size_t start = 0;
    for (std::size_t w = 0; w < workers; ++w) {
        std::size_t end = start + base + (w < extra ? 1 : 0);
        threads.emplace_back(worker, start, end, w);
        start = end;
    }

    for (auto& t : threads) {
        t.join();
    }

    std::array<int, 26> total{};
    for (const auto& a : partials) {
        for (std::size_t i = 0; i < 26; ++i) {
            total[i] += a[i];
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
