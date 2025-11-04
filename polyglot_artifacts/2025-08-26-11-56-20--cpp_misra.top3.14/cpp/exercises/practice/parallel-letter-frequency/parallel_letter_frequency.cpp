#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <functional>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a string, return map
    parallel_letter_frequency::letter_frequency_map count_letters(const std::string& text) {
        parallel_letter_frequency::letter_frequency_map freq{};
        for(const char ch : text) {
            if((std::isalpha(static_cast<unsigned char>(ch))) != 0) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }

    // Helper: merge two frequency maps
    void merge_maps(parallel_letter_frequency::letter_frequency_map& target,
                    const parallel_letter_frequency::letter_frequency_map& source) {
        for(const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }
}

parallel_letter_frequency::letter_frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::thread> threads;
    std::vector<parallel_letter_frequency::letter_frequency_map> partial_results;
    std::mutex results_mutex;

    const std::size_t num_texts = texts.size();
    if(num_texts == 0U) {
        return {};
    }

    // Use at most hardware_concurrency threads, but not more than texts
    const std::size_t max_threads = std::min<std::size_t>(
        (std::thread::hardware_concurrency() == 0U) ? 2U : std::thread::hardware_concurrency(),
        num_texts
    );
    partial_results.resize(max_threads);

    auto worker = [&](std::size_t thread_idx) {
        parallel_letter_frequency::letter_frequency_map local_freq{};
        for(std::size_t i = thread_idx; i < num_texts; i += max_threads) {
            parallel_letter_frequency::letter_frequency_map freq = count_letters(texts[i]);
            merge_maps(local_freq, freq);
        }
        partial_results[thread_idx] = local_freq;
    };

    for(std::size_t t = 0U; t < max_threads; ++t) {
        threads.emplace_back(worker, t);
    }
    for(std::thread& th : threads) {
        if(th.joinable()) {
            th.join();
        }
    }

    // Merge all partial results
    parallel_letter_frequency::letter_frequency_map result{};
    for(const auto& freq : partial_results) {
        merge_maps(result, freq);
    }
    return result;
}

}
