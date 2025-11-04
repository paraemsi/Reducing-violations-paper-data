#include "parallel_letter_frequency.h"

#include <future>
#include <iterator>
#include <locale>
#include <string_view>
#include <thread>
#include <cstddef>

namespace parallel_letter_frequency {

[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts) -> std::map<char, std::uint32_t> {
    if (texts.empty()) {
        return {};
    }

    const std::locale loc {};

    std::size_t thread_count = static_cast<std::size_t>(std::thread::hardware_concurrency());
    if ((thread_count == 0U) || (thread_count > texts.size())) {
        thread_count = texts.size();
    }
    if (thread_count == 0U) {
        thread_count = 1U;
    }

    std::vector<std::future<std::map<char, std::uint32_t>>> futures {};
    futures.reserve(thread_count);

    const std::size_t base_chunk_size = texts.size() / thread_count;
    const std::size_t remainder = texts.size() % thread_count;

    auto chunk_begin = texts.begin();

    for (std::size_t i = 0U; i < thread_count; ++i) {
        const std::size_t current_chunk_size = base_chunk_size + ((i < remainder) ? 1U : 0U);
        auto chunk_end = chunk_begin;
        std::advance(chunk_end, static_cast<std::ptrdiff_t>(current_chunk_size));

        futures.emplace_back(std::async(
            std::launch::async,
            [chunk_begin, chunk_end, &loc]() -> std::map<char, std::uint32_t> {
                std::map<char, std::uint32_t> local_result {};
                for (auto it = chunk_begin; it != chunk_end; ++it) {
                    for (const char ch_raw : *it) {
                        if (std::isalpha(ch_raw, loc) != 0) {
                            const char ch_lower = static_cast<char>(std::tolower(ch_raw, loc));
                            ++local_result[ch_lower];
                        }
                    }
                }
                return local_result;
            }));

        chunk_begin = chunk_end;
    }

    std::map<char, std::uint32_t> result {};
    for (auto& fut : futures) {
        const auto local_map = fut.get();
        for (const auto& pair : local_map) {
            result[pair.first] += pair.second;
        }
    }

    return result;
}

[[nodiscard]] auto frequency(const std::vector<std::string>& texts) -> std::map<char, std::uint32_t> {
    std::vector<std::string_view> views {};
    views.reserve(texts.size());
    for (const auto& str : texts) {
        views.emplace_back(str);
    }
    return frequency(views);
}

} // namespace parallel_letter_frequency
