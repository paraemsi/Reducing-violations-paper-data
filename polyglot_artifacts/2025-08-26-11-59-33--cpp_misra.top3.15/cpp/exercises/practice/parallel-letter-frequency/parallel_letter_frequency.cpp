#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#include <string>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a single string
    parallel_letter_frequency::frequency_map count_letters(const std::string& text) {
        parallel_letter_frequency::frequency_map freq;
        for(const char ch : text) {
            if((std::isalpha(static_cast<unsigned char>(ch))) != 0) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }

    // Helper: merge two frequency maps
    void merge_maps(parallel_letter_frequency::frequency_map& target, const parallel_letter_frequency::frequency_map& source) {
        for(const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }
}

parallel_letter_frequency::frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::thread> threads;
    std::vector<parallel_letter_frequency::frequency_map> results;
    std::mutex results_mutex;

    std::size_t num_texts = texts.size();
    if(num_texts == 0U) {
        return parallel_letter_frequency::frequency_map{};
    }

    // Use at most hardware_concurrency threads, but not more than texts
    std::uint32_t num_threads = std::thread::hardware_concurrency();
    if((num_threads == 0U) || (num_threads > num_texts)) {
        num_threads = static_cast<std::uint32_t>(num_texts);
    }

    results.resize(num_threads);

    auto worker = [&](std::uint32_t thread_idx) {
        parallel_letter_frequency::frequency_map local_freq;
        for(std::size_t i = thread_idx; i < num_texts; i += num_threads) {
            parallel_letter_frequency::frequency_map freq = count_letters(texts[i]);
            merge_maps(local_freq, freq);
        }
        results[thread_idx] = local_freq;
    };

    for(std::uint32_t i = 0U; i < num_threads; ++i) {
        threads.emplace_back(worker, i);
    }

    for(std::thread& t : threads) {
        t.join();
    }

    // Merge all thread results
    parallel_letter_frequency::frequency_map final_freq;
    for(const auto& freq : results) {
        merge_maps(final_freq, freq);
    }

    return final_freq;
}

}
