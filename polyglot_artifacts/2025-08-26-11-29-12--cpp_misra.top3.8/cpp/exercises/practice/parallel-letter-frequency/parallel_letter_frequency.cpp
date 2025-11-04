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
                // Only count alphabetic, convert to lower case
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }
}

// Provide alias 'frequency' for backward compatibility with test suite
frequency_map_t frequency(const text_vector_t& texts) {
    return letter_frequency(texts);
}

parallel_letter_frequency::frequency_map_t letter_frequency(const text_vector_t& texts) {
    const std::size_t num_texts = texts.size();
    if (num_texts == 0U) {
        return {};
    }

    // Determine number of threads to use
    const std::size_t num_threads = (std::min)(num_texts, std::max<std::size_t>(1U, std::thread::hardware_concurrency()));
    std::vector<std::thread> threads;
    std::vector<frequency_map_t> partial_results(num_threads);

    // Mutex for writing to partial_results
    std::mutex results_mutex;

    // Lambda for thread work
    auto worker = [&](std::size_t thread_idx) {
        frequency_map_t local_freq;
        for (std::size_t i = thread_idx; i < num_texts; i += num_threads) {
            frequency_map_t freq = count_letters(texts[i]);
            for (const auto& kv : freq) {
                local_freq[kv.first] += kv.second;
            }
        }
        // Store result
        {
            std::lock_guard<std::mutex> lock(results_mutex);
            partial_results[thread_idx] = local_freq;
        }
    };

    // Launch threads
    for (std::size_t t = 0U; t < num_threads; ++t) {
        threads.emplace_back(worker, t);
    }
    for (auto& th : threads) {
        th.join();
    }

    // Merge all partial results
    frequency_map_t final_freq;
    for (const auto& part : partial_results) {
        for (const auto& kv : part) {
            final_freq[kv.first] += kv.second;
        }
    }
    return final_freq;
}

}
