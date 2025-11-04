#include "parallel_letter_frequency.h"

#include <cctype>
#include <future>
#include <map>
#include <string>
#include <vector>
#include <string_view>
#include <cstdint>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string>& texts) -> std::map<char, counter_t>
{
    std::vector<std::future<std::map<char, counter_t>>> tasks {};
    tasks.reserve(texts.size());

    const std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};

    for (const auto& text : texts) {
        tasks.emplace_back(std::async(std::launch::async, [text, alphabet]() {
            std::map<char, counter_t> local_counts {};

            for (const char ch : text) {
                const unsigned char uch {static_cast<unsigned char>(ch)};
                if (std::isalpha(uch) != 0) {
                    const char lowered {static_cast<char>(std::tolower(uch))};
                    if (alphabet.find(lowered) != std::string::npos) {
                        ++local_counts[lowered];
                    }
                }
            }

            return local_counts;
        }));
    }

    std::map<char, counter_t> result {};

    for (auto& task : tasks) {
        const auto local_map {task.get()};
        for (const auto& kv : local_map) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

auto frequency(const std::vector<std::string_view>& texts) -> std::map<char, counter_t>
{
    std::vector<std::future<std::map<char, counter_t>>> tasks {};
    tasks.reserve(texts.size());

    const std::string_view alphabet {"abcdefghijklmnopqrstuvwxyz"};

    for (const auto text : texts) {
        tasks.emplace_back(std::async(std::launch::async, [text, alphabet]() {
            std::map<char, counter_t> local_counts {};

            for (const char ch : text) {
                const unsigned char uch {static_cast<unsigned char>(ch)};
                if (std::isalpha(uch) != 0) {
                    const char lowered {static_cast<char>(std::tolower(uch))};
                    if (alphabet.find(lowered) != std::string_view::npos) {
                        ++local_counts[lowered];
                    }
                }
            }

            return local_counts;
        }));
    }

    std::map<char, counter_t> result {};

    for (auto& task : tasks) {
        const auto local_map {task.get()};
        for (const auto& kv : local_map) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
