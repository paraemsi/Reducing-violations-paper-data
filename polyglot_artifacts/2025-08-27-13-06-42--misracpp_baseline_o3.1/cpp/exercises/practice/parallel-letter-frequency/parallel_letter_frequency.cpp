#include "parallel_letter_frequency.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <string_view>
#include <string>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    std::map<char, int> result;
    if (texts.empty()) {
        return result;
    }

    const std::size_t num_texts = texts.size();
    unsigned int max_threads = std::thread::hardware_concurrency();
    if (max_threads == 0) {
        max_threads = 2; // reasonable fallback when HW concurrency is unknown
    }
    const std::size_t num_threads = std::min<std::size_t>(max_threads, num_texts);

    std::vector<std::map<char, int>> partials(num_threads);
    std::vector<std::thread> threads(num_threads);

    auto worker = [&](std::size_t begin, std::size_t end, std::size_t slot) {
        auto &local = partials[slot];
        for (std::size_t i = begin; i < end; ++i) {
            for (char ch : texts[i]) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                    ++local[lower];
                }
            }
        }
    };

    if (num_threads == 1) {
        // Single-threaded fast-path – avoid the overhead of spawning a thread
        worker(0, num_texts, 0);
    } else {
        std::size_t block_size = num_texts / num_threads;
        std::size_t remainder = num_texts % num_threads;
        std::size_t begin = 0;
        for (std::size_t t = 0; t < num_threads; ++t) {
            std::size_t end = begin + block_size + (t < remainder ? 1u : 0u);
            threads[t] = std::thread(worker, begin, end, t);
            begin = end;
        }

        for (auto &th : threads) {
            th.join();
        }
    }

    for (const auto &local : partials) {
        for (const auto &p : local) {
            result[p.first] += p.second;
        }
    }

    return result;
}

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

} // namespace parallel_letter_frequency
