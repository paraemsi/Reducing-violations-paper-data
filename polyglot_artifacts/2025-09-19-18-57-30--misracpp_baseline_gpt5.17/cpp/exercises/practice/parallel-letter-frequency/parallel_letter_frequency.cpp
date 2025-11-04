#include "parallel_letter_frequency.h"
#include <algorithm>
#include <array>
#include <cctype>
#include <future>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {


frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t num_texts = texts.size();
    unsigned int hc = std::thread::hardware_concurrency();
    std::size_t num_workers = hc == 0 ? 2u : static_cast<std::size_t>(hc);
    if (num_workers > num_texts) {
        num_workers = num_texts;
    }

    const std::size_t chunk_size = (num_texts + num_workers - 1) / num_workers;

    std::vector<std::future<std::array<int, 26>>> futures;
    futures.reserve(num_workers);

    for (std::size_t i = 0; i < num_workers; ++i) {
        const std::size_t begin = i * chunk_size;
        if (begin >= num_texts) {
            break;
        }
        const std::size_t end = std::min(begin + chunk_size, num_texts);
        futures.emplace_back(std::async(std::launch::async, [begin, end, &texts]() {
            std::array<int, 26> counts{};
            for (std::size_t idx = begin; idx < end; ++idx) {
                std::string_view s = texts[idx];
                for (char ch : s) {
                    const unsigned char uc = static_cast<unsigned char>(ch);
                    const char c = static_cast<char>(std::tolower(uc));
                    if (c >= 'a' && c <= 'z') {
                        counts[static_cast<std::size_t>(c - 'a')]++;
                    }
                }
            }
            return counts;
        }));
    }

    std::array<int, 26> total{};
    for (auto& fut : futures) {
        const auto counts = fut.get();
        for (std::size_t i = 0; i < 26; ++i) {
            total[i] += counts[i];
        }
    }

    frequency_map result;
    for (std::size_t i = 0; i < 26; ++i) {
        if (total[i] > 0) {
            result[static_cast<char>('a' + i)] = total[i];
        }
    }
    return result;
}

}
