#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <cctype>
#include <algorithm>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a string, case-insensitive, only a-z
    std::map<char, int> count_letters(const std::string& text) {
        std::map<char, int> freq;
        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                ++freq[lower];
            }
        }
        return freq;
    }
}

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::vector<std::map<char, int>> partials(texts.size());
    std::vector<std::thread> threads;

    // Mutex not needed for partials, each thread writes to its own slot
    for (size_t i = 0; i < texts.size(); ++i) {
        threads.emplace_back([&texts, &partials, i]() {
            partials[i] = count_letters(texts[i]);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // Merge all partial results
    std::map<char, int> result;
    for (const auto& freq : partials) {
        for (const auto& [ch, count] : freq) {
            result[ch] += count;
        }
    }
    return result;
}

}
