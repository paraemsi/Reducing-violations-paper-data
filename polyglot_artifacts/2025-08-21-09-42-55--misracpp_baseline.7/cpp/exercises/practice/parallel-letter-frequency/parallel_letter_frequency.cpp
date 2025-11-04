#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <cctype>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

namespace parallel_letter_frequency {

    namespace {
        // Helper: count letters in a single string, return map
        std::map<char, int> count_letters(const std::string& text) {
            std::map<char, int> freq;
            for (char ch : text) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
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
        if (texts.empty()) return {};

        std::vector<std::map<char, int>> partials(texts.size());
        std::vector<std::thread> threads;

        // Mutex not needed since each thread writes to its own map
        for (size_t i = 0; i < texts.size(); ++i) {
            threads.emplace_back([&texts, &partials, i]() {
                partials[i] = count_letters(texts[i]);
            });
        }

        for (auto& t : threads) {
            t.join();
        }

        // Merge all partial maps into result
        std::map<char, int> result;
        for (const auto& freq : partials) {
            merge_freq(result, freq);
        }
        return result;
    }

}
