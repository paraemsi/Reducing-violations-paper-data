#include "parallel_letter_frequency.h"

#include <cctype>
#include <future>
#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

namespace {

// Count letters in a single text (case-insensitive, ASCII letters A-Z).
inline frequency_map count_letters(std::string_view text) {
    frequency_map counts;
    for (unsigned char ch : text) {
        char c = static_cast<char>(ch);
        if (c >= 'A' && c <= 'Z') {
            c = static_cast<char>(c - 'A' + 'a');
        }
        if (c >= 'a' && c <= 'z') {
            ++counts[c];
        }
    }
    return counts;
}

}  // namespace

frequency_map frequency(const std::vector<std::string_view>& texts) {
    std::vector<std::future<frequency_map>> futures;
    futures.reserve(texts.size());

    for (const auto& text : texts) {
        futures.emplace_back(std::async(std::launch::async, [t = text] {
            return count_letters(t);
        }));
    }

    frequency_map result;
    for (auto& fut : futures) {
        frequency_map partial = fut.get();
        for (const auto& kv : partial) {
            result[kv.first] += kv.second;
        }
    }
    return result;
}

}
