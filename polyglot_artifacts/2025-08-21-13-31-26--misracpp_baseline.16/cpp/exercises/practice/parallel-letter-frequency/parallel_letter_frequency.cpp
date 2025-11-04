#include "parallel_letter_frequency.h"
#include <algorithm>
#include <cctype>
#include <future>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

    namespace {
        // Helper: count letters in a single string
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

        // Helper: merge two frequency maps
        void merge_freq(std::map<char, int>& dest, const std::map<char, int>& src) {
            for (const auto& [ch, count] : src) {
                dest[ch] += count;
            }
        }
    }

    std::map<char, int> frequency(const std::vector<std::string>& texts) {
        if (texts.empty()) {
            return {};
        }

        std::vector<std::future<std::map<char, int>>> futures;
        futures.reserve(texts.size());

        // Launch a thread for each text
        for (const auto& text : texts) {
            futures.push_back(std::async(std::launch::async, count_letters, std::cref(text)));
        }

        // Merge all results
        std::map<char, int> result;
        for (auto& fut : futures) {
            merge_freq(result, fut.get());
        }

        return result;
    }

}
