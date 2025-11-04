#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <iterator>
#include <string_view>
#include <thread>

namespace parallel_letter_frequency {

namespace {

// Count letters in the supplied range of texts.
frequency_map count_chunk(std::vector<std::string_view>::const_iterator begin,
                          std::vector<std::string_view>::const_iterator end) {
    frequency_map local{};
    for (auto it = begin; it != end; ++it) {
        for (char ch : *it) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++local[lower];
            }
        }
    }
    return local;
}

// Merge counts from src into dst.
void merge_into(frequency_map& dst, const frequency_map& src) {
    for (auto const& [ch, cnt] : src) {
        dst[ch] += cnt;
    }
}

}  // namespace

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t max_threads =
        std::max<std::size_t>(1, std::thread::hardware_concurrency());
    const std::size_t task_count = std::min(max_threads, texts.size());
    const std::size_t chunk_size = (texts.size() + task_count - 1) / task_count;

    std::vector<std::future<frequency_map>> futures;
    futures.reserve(task_count);

    auto chunk_begin = texts.cbegin();
    for (std::size_t i = 0; i < task_count && chunk_begin != texts.cend(); ++i) {
        auto remaining = static_cast<std::size_t>(std::distance(chunk_begin, texts.cend()));
        auto chunk_end = std::next(chunk_begin, std::min(chunk_size, remaining));

        futures.emplace_back(std::async(std::launch::async,
                                        &count_chunk, chunk_begin, chunk_end));
        chunk_begin = chunk_end;
    }

    frequency_map result;
    for (auto& fut : futures) {
        merge_into(result, fut.get());
    }
    return result;
}

}  // namespace parallel_letter_frequency
