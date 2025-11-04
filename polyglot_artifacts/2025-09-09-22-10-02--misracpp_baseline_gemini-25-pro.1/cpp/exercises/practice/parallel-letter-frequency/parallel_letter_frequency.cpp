#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <iterator>
#include <thread>

namespace parallel_letter_frequency {

namespace {
letter_counts
count_letters(std::vector<std::string_view>::const_iterator begin,
              std::vector<std::string_view>::const_iterator end) {
    letter_counts result{};
    for (auto it = begin; it != end; ++it) {
        for (char c : *it) {
            if (std::isalpha(c)) {
                result[std::tolower(c)]++;
            }
        }
    }
    return result;
}
} // namespace

letter_counts frequency(const std::vector<std::string_view> &texts) {
    if (texts.empty()) {
        return {};
    }

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }

    std::vector<std::future<letter_counts>> futures{};
    const size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;

    auto it = texts.cbegin();
    for (unsigned int i = 0; i < num_threads && it != texts.cend(); ++i) {
        auto next_it = it;
        const size_t distance_to_advance =
            std::min(chunk_size, (size_t)std::distance(it, texts.cend()));
        std::advance(next_it, distance_to_advance);
        futures.push_back(
            std::async(std::launch::async, count_letters, it, next_it));
        it = next_it;
    }

    letter_counts total_frequency{};
    for (auto &f : futures) {
        const letter_counts partial_map = f.get();
        for (const auto &pair : partial_map) {
            total_frequency[pair.first] += pair.second;
        }
    }

    return total_frequency;
}

} // namespace parallel_letter_frequency
