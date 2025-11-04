#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

letter_frequency_map frequency(const std::vector<std::string>& texts) {
    return letter_frequency(texts);
}

namespace {
    // Helper: count letters in a string, return map
    parallel_letter_frequency::letter_frequency_map count_letters(const std::string& text) {
        parallel_letter_frequency::letter_frequency_map freq{};
        for (const char ch : text) {
            if ((std::isalpha(static_cast<unsigned char>(ch))) != 0) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }

    // Helper: merge two maps
    void merge_maps(parallel_letter_frequency::letter_frequency_map& target,
                    const parallel_letter_frequency::letter_frequency_map& source) {
        for (const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }
}

parallel_letter_frequency::letter_frequency_map letter_frequency(const std::vector<std::string>& texts) {
    std::vector<std::thread> threads;
    std::vector<parallel_letter_frequency::letter_frequency_map> partial_results(texts.size());
    std::mutex result_mutex;

    for (std::size_t i = 0U; i < texts.size(); ++i) {
        threads.emplace_back([&texts, &partial_results, i]() {
            partial_results[i] = count_letters(texts[i]);
        });
    }

    for (std::thread& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    parallel_letter_frequency::letter_frequency_map result{};
    for (const auto& partial : partial_results) {
        merge_maps(result, partial);
    }
    return result;
}

}
