#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<frequency_map> partials(texts.size());
    std::vector<std::thread> threads;

    // Lambda to count letters in a single string
    auto count_letters = [](const std::string& text, frequency_map& freq) {
        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char lower = std::tolower(static_cast<unsigned char>(c));
                ++freq[lower];
            }
        }
    };

    // Launch threads for each text
    for (size_t i = 0; i < texts.size(); ++i) {
        threads.emplace_back(count_letters, std::cref(texts[i]), std::ref(partials[i]));
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    // Merge all partial frequency maps
    frequency_map result;
    for (const auto& freq : partials) {
        for (const auto& pair : freq) {
            result[pair.first] += pair.second;
        }
    }

    return result;
}

}
