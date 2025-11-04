#include "parallel_letter_frequency.h"

#include <array>
#include <algorithm>
#include <cctype>
#include <functional>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

[[nodiscard]] frequency_map frequency(const std::vector<std::string>& texts) {
    constexpr std::size_t alphabet_size{26};
    std::array<int, alphabet_size> global_counts{};
    global_counts.fill(0);

    if (texts.empty()) {
        return {};
    }

    const unsigned int hw_threads{std::thread::hardware_concurrency()};
    const std::size_t num_threads{
        std::min<std::size_t>(hw_threads == 0 ? 1 : hw_threads, texts.size())};

    // One local counter per thread
    std::vector<std::array<int, alphabet_size>> local_counts(num_threads);
    for (auto& arr : local_counts) {
        arr.fill(0);
    }

    auto worker = [&](std::size_t begin, std::size_t end,
                      std::array<int, alphabet_size>& counts) {
        for (std::size_t i = begin; i < end; ++i) {
            for (unsigned char ch : texts[i]) {
                if (std::isalpha(ch)) {
                    ch = static_cast<unsigned char>(std::tolower(ch));
                    counts[ch - 'a']++;
                }
            }
        }
    };

    // Launch threads with roughly equal sized chunks
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    std::size_t block_size{texts.size() / num_threads};
    std::size_t remainder{texts.size() % num_threads};

    std::size_t start{0};
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t end{start + block_size + (t < remainder ? 1 : 0)};
        threads.emplace_back(worker, start, end, std::ref(local_counts[t]));
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    // Merge local results
    for (const auto& counts : local_counts) {
        for (std::size_t i = 0; i < alphabet_size; ++i) {
            global_counts[i] += counts[i];
        }
    }

    frequency_map result;
    for (std::size_t i = 0; i < alphabet_size; ++i) {
        if (global_counts[i] > 0) {
            result.emplace(static_cast<char>('a' + static_cast<char>(i)),
                           global_counts[i]);
        }
    }
    return result;
}

}
