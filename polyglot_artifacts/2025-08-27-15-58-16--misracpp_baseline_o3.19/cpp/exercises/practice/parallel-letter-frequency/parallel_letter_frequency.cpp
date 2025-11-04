#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <map>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

    // Count letters (a-z, case-insensitive) in a single text.
    static std::map<char, int> count_letters(std::string_view text) {
        std::map<char, int> counts;
        for (char ch : text) {
            unsigned char uch = static_cast<unsigned char>(ch);
            if (std::isalpha(uch)) {
                counts[static_cast<char>(std::tolower(uch))]++;
            }
        }
        return counts;
    }

    std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
        if (texts.empty()) {
            return {};
        }

        // Launch one async task per text.
        std::vector<std::future<std::map<char, int>>> futures;
        futures.reserve(texts.size());

        for (const auto& text : texts) {
            futures.emplace_back(std::async(std::launch::async, count_letters, text));
        }

        // Merge partial results.
        std::map<char, int> total;
        for (auto& fut : futures) {
            for (const auto& [ch, cnt] : fut.get()) {
                total[ch] += cnt;
            }
        }
        return total;
    }

    // Convenience overload – converts each std::string to std::string_view and
    // forwards to the main implementation above.
    std::map<char, int> frequency(const std::vector<std::string>& texts) {
        std::vector<std::string_view> views;
        views.reserve(texts.size());
        for (const auto& s : texts) {
            views.emplace_back(s);
        }
        return frequency(views);
    }


}
