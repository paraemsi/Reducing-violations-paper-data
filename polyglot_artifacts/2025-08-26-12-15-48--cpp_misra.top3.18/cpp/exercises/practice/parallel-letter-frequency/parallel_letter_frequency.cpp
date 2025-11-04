#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a string, case-insensitive, only a-z
    letter_frequency_map count_letters(const std::string& text) {
        letter_frequency_map freq;
        for(char ch : text) {
            if((std::isalpha(static_cast<unsigned char>(ch))) != 0) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                // Only count a-z
                if(((lower >= 'a') && (lower <= 'z'))) {
                    ++freq[lower];
                }
            }
        }
        return freq;
    }

    // Helper: merge two frequency maps
    void merge_maps(letter_frequency_map& target, const letter_frequency_map& source) {
        for(const auto& kv : source) {
            target[kv.first] += kv.second;
        }
    }
}

letter_frequency_map letter_frequency(const std::vector<std::string>& texts) {
    std::vector<std::thread> threads;
    std::vector<letter_frequency_map> partials(texts.size());

    for(std::size_t i = 0U; i < texts.size(); ++i) {
        threads.emplace_back([&texts, &partials, i]() {
            partials[i] = count_letters(texts[i]);
        });
    }

    for(auto& t : threads) {
        if(t.joinable()) {
            t.join();
        }
    }

    letter_frequency_map result;
    for(const auto& part : partials) {
        merge_maps(result, part);
    }
    return result;
}

// Alias for compatibility with test expectations
letter_frequency_map frequency(const std::vector<std::string>& texts) {
    return letter_frequency(texts);
}

}
