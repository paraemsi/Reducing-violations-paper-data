#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <iterator>
#include <map>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

[[nodiscard]] frequency_map frequency(const std::vector<std::string_view>& texts) {

    if (texts.empty()) {
        return {};
    }

    const unsigned int hardware_threads =
        std::max(1u, std::thread::hardware_concurrency());
    const size_t worker_count = std::min<size_t>(hardware_threads, texts.size());
    const size_t chunk_size = (texts.size() + worker_count - 1) / worker_count;

    std::vector<std::future<frequency_map>> futures;
    futures.reserve(worker_count);

    auto chunk_begin = texts.cbegin();
    for (size_t i = 0; i < worker_count && chunk_begin != texts.cend(); ++i) {
        auto chunk_end = chunk_begin;
        const auto remaining = static_cast<size_t>(std::distance(chunk_begin, texts.cend()));
        std::advance(chunk_end, std::min(chunk_size, remaining));

        futures.emplace_back(std::async(
            std::launch::async, [chunk_begin, chunk_end]() {
                frequency_map local;
                for (auto it = chunk_begin; it != chunk_end; ++it) {
                    for (char ch : *it) {
                        if (std::isalpha(static_cast<unsigned char>(ch))) {
                            ch = static_cast<char>(
                                std::tolower(static_cast<unsigned char>(ch)));
                            ++local[ch];
                        }
                    }
                }
                return local;
            }));

        chunk_begin = chunk_end;
    }

    frequency_map total;
    for (auto& fut : futures) {
        for (const auto& [ch, count] : fut.get()) {
            total[ch] += count;
        }
    }

    return total;
}

}  // namespace parallel_letter_frequency
