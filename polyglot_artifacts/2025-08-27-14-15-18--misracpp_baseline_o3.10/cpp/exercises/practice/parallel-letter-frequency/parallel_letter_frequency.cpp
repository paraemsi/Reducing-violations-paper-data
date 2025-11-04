#include "parallel_letter_frequency.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <future>
#include <thread>
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::array<int, 26> total_counts{};  // zero-initialised
    if (texts.empty()) {
        return {};
    }

    const std::size_t hw_threads =
        std::max(1u, std::thread::hardware_concurrency());
    const std::size_t num_threads = std::min<std::size_t>(texts.size(), hw_threads);

    std::vector<std::future<std::array<int, 26>>> futures;
    futures.reserve(num_threads);

    const std::size_t block_size = (texts.size() + num_threads - 1) / num_threads;

    for (std::size_t t = 0; t < num_threads; ++t) {
        const std::size_t start = t * block_size;
        if (start >= texts.size()) {
            break;
        }
        const std::size_t end = std::min(texts.size(), start + block_size);

        futures.emplace_back(std::async(std::launch::async,
                                        [start, end, &texts]() {
                                            std::array<int, 26> counts{};
                                            for (std::size_t i = start; i < end; ++i) {
                                                for (char ch : texts[i]) {
                                                    if (std::isalpha(
                                                            static_cast<unsigned char>(ch))) {
                                                        char lower = static_cast<char>(
                                                            std::tolower(static_cast<unsigned char>(ch)));
                                                        if (lower >= 'a' && lower <= 'z') {
                                                            counts[lower - 'a']++;
                                                        }
                                                    }
                                                }
                                            }
                                            return counts;
                                        }));
    }

    for (auto& fut : futures) {
        auto counts = fut.get();
        for (std::size_t i = 0; i < 26; ++i) {
            total_counts[i] += counts[i];
        }
    }

    std::map<char, int> result;
    for (int i = 0; i < 26; ++i) {
        if (total_counts[i] > 0) {
            result[static_cast<char>('a' + i)] = total_counts[i];
        }
    }
    return result;
}

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    // Reuse the existing implementation by copying to std::string.
    std::vector<std::string> copied(texts.begin(), texts.end());
    return frequency(copied);
}

} // namespace parallel_letter_frequency
