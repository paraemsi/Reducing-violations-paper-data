#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a single text, return frequency map
    parallel_letter_frequency::frequency_map_t count_letters(const parallel_letter_frequency::text_t& text) {
        parallel_letter_frequency::frequency_map_t freq;
        for (const char ch : text) {
            if ((std::isalpha(static_cast<unsigned char>(ch))) != 0) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }

    // Helper: merge two frequency maps
    void merge_maps(parallel_letter_frequency::frequency_map_t& target, const parallel_letter_frequency::frequency_map_t& source) {
        for (const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }
}

parallel_letter_frequency::frequency_map_t frequency(const std::vector<parallel_letter_frequency::text_t>& texts) {
    std::vector<std::thread> threads;
    std::vector<parallel_letter_frequency::frequency_map_t> partial_results(texts.size());
    std::mutex result_mutex;

    // Launch a thread for each text (but not more than hardware concurrency)
    std::size_t max_threads = std::thread::hardware_concurrency();
    if (max_threads == 0U) {
        max_threads = 2U;
    }
    std::size_t num_texts = texts.size();
    std::size_t num_threads = (num_texts < max_threads) ? num_texts : max_threads;

    auto worker = [&](std::size_t start, std::size_t end) {
        for (std::size_t i = start; i < end; ++i) {
            partial_results[i] = count_letters(texts[i]);
        }
    };

    std::vector<std::thread> workers;
    std::size_t block_size = (num_texts + num_threads - 1U) / num_threads;
    for (std::size_t t = 0U; t < num_threads; ++t) {
        std::size_t start = t * block_size;
        std::size_t end = ((start + block_size) < num_texts) ? (start + block_size) : num_texts;
        if (start < end) {
            workers.emplace_back(worker, start, end);
        }
    }
    for (auto& th : workers) {
        th.join();
    }

    // Merge all partial results
    parallel_letter_frequency::frequency_map_t result;
    for (const auto& freq : partial_results) {
        merge_maps(result, freq);
    }
    return result;
}

}
