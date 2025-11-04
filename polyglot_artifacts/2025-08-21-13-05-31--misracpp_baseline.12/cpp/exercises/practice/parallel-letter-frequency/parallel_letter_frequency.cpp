#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <cctype>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::vector<std::map<char, int>> partial_results(texts.size());
    std::vector<std::thread> threads;

    auto count_letters = [](const std::string& text, std::map<char, int>& result) {
        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char lower = std::tolower(static_cast<unsigned char>(c));
                ++result[lower];
            }
        }
    };

    // Launch a thread for each text
    for (size_t i = 0; i < texts.size(); ++i) {
        threads.emplace_back(count_letters, std::cref(texts[i]), std::ref(partial_results[i]));
    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    // Merge all partial results
    std::map<char, int> final_result;
    for (const auto& partial : partial_results) {
        for (const auto& kv : partial) {
            final_result[kv.first] += kv.second;
        }
    }

    return final_result;
}

}
