#include "parallel_letter_frequency.h"
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>

namespace parallel_letter_frequency {

    namespace {
        // Helper: count letters in a single string
        std::map<char, int> count_letters(const std::string& text) {
            std::map<char, int> freq;
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    char lower = std::tolower(static_cast<unsigned char>(c));
                    ++freq[lower];
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
        std::vector<std::map<char, int>> partials(texts.size());
        std::vector<std::thread> threads;

        // Launch a thread for each text
        for (size_t i = 0; i < texts.size(); ++i) {
            threads.emplace_back([&texts, &partials, i]() {
                partials[i] = count_letters(texts[i]);
            });
        }

        // Join all threads
        for (auto& t : threads) {
            t.join();
        }

        // Merge all partial results
        std::map<char, int> result;
        for (const auto& freq : partials) {
            merge_freq(result, freq);
        }
        return result;
    }

}
