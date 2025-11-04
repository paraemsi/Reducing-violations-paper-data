#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <iterator>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a string, thread-safe
    parallel_letter_frequency::frequency_map count_letters(const std::string& text) {
        parallel_letter_frequency::frequency_map freq;
        for (char ch : text) {
            if (std::isalpha(static_cast<unsigned char>(ch)) != 0) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }

    // Helper: merge two frequency maps
    void merge_maps(parallel_letter_frequency::frequency_map& target, const parallel_letter_frequency::frequency_map& source) {
        for (const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }
}

// The tests expect the function to be named 'frequency'
auto frequency(const std::vector<std::string>& texts) -> parallel_letter_frequency::frequency_map {
    std::vector<std::thread> threads;
    std::vector<parallel_letter_frequency::frequency_map> results(texts.size());
    std::mutex results_mutex;

    // Launch a thread for each text (but don't oversubscribe)
    std::size_t max_threads = std::min(texts.size(), static_cast<std::size_t>(std::thread::hardware_concurrency()));
    if (max_threads == 0U) {
        max_threads = 2U;
    }

    std::atomic<std::size_t> next_index{0U};

    auto worker = [&]() {
        while (true) {
            std::size_t idx = next_index.fetch_add(1U);
            if (idx >= texts.size()) {
                break;
            }
            results[idx] = count_letters(texts[idx]);
        }
    };

    threads.reserve(max_threads);
    for (std::size_t i = 0U; i < max_threads; ++i) {
        threads.emplace_back(worker);
    }
    for (auto& t : threads) {
        t.join();
    }

    // Merge all results
    parallel_letter_frequency::frequency_map total;
    for (const auto& freq : results) {
        merge_maps(total, freq);
    }
    return total;
}

}
