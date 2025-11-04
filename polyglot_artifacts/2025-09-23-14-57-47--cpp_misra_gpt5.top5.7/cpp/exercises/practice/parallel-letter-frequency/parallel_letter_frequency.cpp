#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {
    // Count letters in [begin, end) range of texts into 'out'.
    void count_range(const std::vector<std::string_view>& texts,
                     const std::size_t begin,
                     const std::size_t end,
                     frequency_map& out)
    {
        for (std::size_t idx = begin; idx < end; ++idx) {
            const std::string_view s = texts[idx];
            for (char ch : s) {
                const auto ich = std::char_traits<char>::to_int_type(ch);
                if ((std::isalpha(ich) != 0)) {
                    const auto lower_i = std::tolower(ich);
                    const char lower = std::char_traits<char>::to_char_type(lower_i);
                    ++out[lower];
                }
            }
        }
    }
}  // namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    frequency_map result{};

    const std::size_t n = texts.size();
    if (n == 0U) {
        return result;
    }

    const std::size_t hc = static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t max_threads =
        ((hc == 0U) ? static_cast<std::size_t>(2U) : hc);
    const std::size_t n_threads = ((n < max_threads) ? n : max_threads);

    if (n_threads <= 1U) {
        count_range(texts, 0U, n, result);
        return result;
    }

    std::vector<frequency_map> partials(n_threads);
    std::vector<std::thread> threads{};
    threads.reserve(n_threads);

    const std::size_t base = (n / n_threads);
    const std::size_t rem = (n % n_threads);

    std::size_t start = 0U;
    for (std::size_t t = 0U; t < n_threads; ++t) {
        const std::size_t count = (base + ((t < rem) ? 1U : 0U));
        const std::size_t end = (start + count);

        threads.emplace_back([&texts, start, end, &partials, t]() {
            frequency_map local{};
            for (std::size_t idx = start; idx < end; ++idx) {
                const std::string_view s = texts[idx];
                for (char ch : s) {
                    const auto ich = std::char_traits<char>::to_int_type(ch);
                    if ((std::isalpha(ich) != 0)) {
                        const auto lower_i = std::tolower(ich);
                        const char lower = std::char_traits<char>::to_char_type(lower_i);
                        ++local[lower];
                    }
                }
            }
            partials[t] = std::move(local);
        });

        start = end;
    }

    for (std::thread& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    // Merge partial maps into the final result.
    for (const frequency_map& fm : partials) {
        for (const auto& kv : fm) {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
