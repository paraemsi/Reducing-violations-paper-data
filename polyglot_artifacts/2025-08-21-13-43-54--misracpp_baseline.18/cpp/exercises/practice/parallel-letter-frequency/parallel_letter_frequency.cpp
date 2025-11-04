#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <cctype>
#include <algorithm>
#include <iterator>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a single string, case-insensitive, only a-z
    std::map<char, int> count_letters(const std::string& text) {
        std::map<char, int> freq;
        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                freq[lower]++;
            }
        }
        return freq;
    }

    // Helper: merge two frequency maps
    void merge_freq(std::map<char, int>& target, const std::map<char, int>& source) {
        for (const auto& [ch, count] : source) {
            target[ch] += count;
        }
    }
}

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return {};
    }

    unsigned int num_threads = std::min<unsigned int>(std::thread::hardware_concurrency(), texts.size());
    if (num_threads == 0) num_threads = 1;

    std::vector<std::map<char, int>> partial_results(num_threads);
    std::vector<std::thread> threads(num_threads);

    auto worker = [&](size_t thread_idx) {
        for (size_t i = thread_idx; i < texts.size(); i += num_threads) {
            auto freq = count_letters(texts[i]);
            merge_freq(partial_results[thread_idx], freq);
        }
    };

    for (size_t t = 0; t < num_threads; ++t) {
        threads[t] = std::thread(worker, t);
    }
    for (auto& th : threads) {
        th.join();
    }

    std::map<char, int> result;
    for (const auto& partial : partial_results) {
        merge_freq(result, partial);
    }
    return result;
}

}
