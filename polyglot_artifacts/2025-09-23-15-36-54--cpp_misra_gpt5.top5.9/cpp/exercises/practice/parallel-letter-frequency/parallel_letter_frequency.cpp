#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <locale>
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {
    // Worker that processes a subrange of texts and returns a local frequency map.
    template <typename It>
    auto worker_range(It first,
                      It last,
                      const std::locale& loc) -> frequency_map
    {
        frequency_map local{};

        for (auto it = first; it != last; ++it) {
            const std::string& text = *it;

            for (const char ch : text) {
                // Use locale-aware classification and conversion.
                if (std::isalpha(ch, loc)) {
                    const char lower = std::tolower(ch, loc);
                    // Increment the count for this letter.
                    ++local[lower];
                }
            }
        }

        return local;
    }
}  // namespace

// Helper to compute frequencies with a configurable number of workers for any text container.
template <typename TextContainer>
auto compute_frequency(const TextContainer& texts, std::size_t worker_count) -> frequency_map
{
    if ((worker_count == 0U)) {
        worker_count = 1U;
    }

    const std::size_t n = texts.size();

    if (((worker_count > n) && (n > 0U))) {
        worker_count = n;
    }

    const std::locale loc = std::locale::classic();
    std::vector<std::future<frequency_map>> futures{};
    futures.reserve(worker_count);

    // Ceil division to determine chunk size.
    const std::size_t chunk = ((n + (worker_count - 1U)) / worker_count);

    auto begin = texts.cbegin();
    for (std::size_t i = 0U; i < worker_count; ++i) {
        auto chunk_begin = begin;
        auto chunk_end = chunk_begin;

        std::size_t advanced = 0U;
        while (((advanced < chunk) && (chunk_end != texts.cend()))) {
            ++chunk_end;
            ++advanced;
        }

        if (chunk_begin == chunk_end) {
            break;
        }

        futures.emplace_back(std::async(std::launch::async, [chunk_begin, chunk_end, loc]() -> frequency_map {
            return worker_range(chunk_begin, chunk_end, loc);
        }));

        begin = chunk_end;
        if (begin == texts.cend()) {
            break;
        }
    }

    frequency_map result{};

    for (auto& fut : futures) {
        frequency_map partial = fut.get();
        for (const auto& kv : partial) {
            const char key = kv.first;
            const count_type val = kv.second;
            count_type& target = result[key];
            target = (target + val);
        }
    }

    return result;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::size_t threads = static_cast<std::size_t>(std::thread::hardware_concurrency());
    if ((threads == 0U)) {
        threads = 2U;
    }
    return frequency(texts, threads);
}

auto frequency(const std::vector<std::string>& texts, std::size_t worker_count) -> frequency_map
{
    return compute_frequency(texts, worker_count);
}

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    std::vector<std::string> copied{};
    copied.reserve(texts.size());
    for (const std::string_view sv : texts) {
        copied.emplace_back(sv);
    }
    return frequency(copied);
}

auto frequency(const std::vector<std::string_view>& texts, std::size_t worker_count) -> frequency_map
{
    std::vector<std::string> copied{};
    copied.reserve(texts.size());
    for (const std::string_view sv : texts) {
        copied.emplace_back(sv);
    }
    return frequency(copied, worker_count);
}

}  // namespace parallel_letter_frequency
