#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <future>
#include <map>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

namespace {

/* Build a frequency map for a single text */
[[nodiscard]] auto local_frequency(std::string_view text)
    -> std::map<char, int> {
    std::map<char, int> local{};

    for (char ch : text) {
        if (std::isalpha(static_cast<unsigned char>(ch)) != 0) {
            const char lower_ch =
                static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            ++local[lower_ch];
        }
    }

    return local;
}

/* Merge `source` into `destination` */
void merge_into(std::map<char, int>& destination,
                const std::map<char, int>& source) {
    for (const auto& [key, value] : source) {
        destination[key] += value;
    }
}

}  // namespace

[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts)
    -> std::map<char, int> {
    std::map<char, int> result{};

    if (texts.empty()) {
        return result;
    }

    const std::size_t hw_threads =
        (std::thread::hardware_concurrency() == 0U)
            ? 2U
            : static_cast<std::size_t>(std::thread::hardware_concurrency());

    const std::size_t task_count =
        (texts.size() < hw_threads) ? texts.size() : hw_threads;

    /* Ceiling-divide the texts across the tasks */
    const std::size_t chunk_size =
        ((texts.size() + task_count) - 1U) / task_count;

    std::vector<std::future<std::map<char, int>>> futures{};
    futures.reserve(task_count);

    for (std::size_t task_idx = 0U; task_idx < task_count; ++task_idx) {
        const std::size_t begin = task_idx * chunk_size;
        const std::size_t end =
            std::min<std::size_t>(begin + chunk_size, texts.size());

        futures.emplace_back(std::async(
            std::launch::async, [begin, end, &texts]() {
                std::map<char, int> local{};
                for (std::size_t idx = begin; idx < end; ++idx) {
                    const auto sub = local_frequency(texts[idx]);
                    merge_into(local, sub);
                }
                return local;
            }));
    }

    for (auto& fut : futures) {
        merge_into(result, fut.get());
    }

    return result;
}

}  // namespace parallel_letter_frequency
