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

namespace {
    // Helper: merge two frequency maps
    void merge_maps(letter_frequency_map& target, const letter_frequency_map& source) {
        for(const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }

    // Helper: count letters in a single string
    letter_frequency_map count_letters(const std::string& text) {
        letter_frequency_map freq;
        for(char ch : text) {
            if(std::isalpha(static_cast<unsigned char>(ch))) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }
}

letter_frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::thread> threads;
    std::vector<letter_frequency_map> results(texts.size());

    for(std::size_t i = 0U; i < texts.size(); ++i) {
        threads.emplace_back([&results, &texts, i]() {
            results[i] = count_letters(texts[i]);
        });
    }

    for(std::thread& t : threads) {
        if(t.joinable()) {
            t.join();
        }
    }

    letter_frequency_map total;
    for(const auto& freq : results) {
        merge_maps(total, freq);
    }
    return total;
}

}
