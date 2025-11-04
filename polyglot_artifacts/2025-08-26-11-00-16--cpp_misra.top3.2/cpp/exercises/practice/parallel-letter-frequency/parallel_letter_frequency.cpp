#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <functional>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a string, case-insensitive, only a-z
    parallel_letter_frequency::letter_frequency_map count_letters(const std::string& text) {
        parallel_letter_frequency::letter_frequency_map freq{};
        for (const char ch : text) {
            if ((std::isalpha(static_cast<unsigned char>(ch))) != 0) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                // Only count a-z
                if (((lower >= 'a') && (lower <= 'z'))) {
                    ++freq[lower];
                }
            }
        }
        return freq;
    }

    // Helper: merge two frequency maps
    void merge_maps(parallel_letter_frequency::letter_frequency_map& target,
                    const parallel_letter_frequency::letter_frequency_map& source) {
        for (const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }
}

parallel_letter_frequency::letter_frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::thread> threads;
    std::vector<parallel_letter_frequency::letter_frequency_map> partial_results(texts.size());
    std::mutex result_mutex;

    // Launch a thread for each text (if texts.size() is small, this is fine)
    for (std::size_t i = 0U; i < texts.size(); ++i) {
        threads.emplace_back([&texts, &partial_results, i]() {
            partial_results[i] = count_letters(texts[i]);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // Merge all partial results
    parallel_letter_frequency::letter_frequency_map result{};
    for (const auto& freq : partial_results) {
        merge_maps(result, freq);
    }
    return result;
}

}
