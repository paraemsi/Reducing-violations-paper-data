#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <cstddef>
#include <string>
#include <string_view>
#include <thread>

namespace parallel_letter_frequency {

namespace {
constexpr std::size_t alphabet_size = 26U;
constexpr std::array<char, alphabet_size> letters{
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z'
};
}  // namespace

auto frequency(const std::vector<std::string>& texts) -> frequency_map {
    // Early return for empty input
    if (texts.empty()) {
        return {};
    }

    // Decide thread count
    std::size_t thread_count = static_cast<std::size_t>(std::thread::hardware_concurrency());
    if (thread_count == 0U) {
        thread_count = 1U;
    }
    if (thread_count > texts.size()) {
        thread_count = texts.size();
    }

    // Fallback to single-thread if it would be the same as number of items
    if (thread_count == 0U) {
        thread_count = 1U;
    }

    // Prepare workers
    std::vector<std::thread> workers{};
    workers.reserve(thread_count);

    // Each worker will produce its own local counts to avoid data races
    std::vector<std::array<std::uint32_t, alphabet_size>> local_counts{};
    local_counts.resize(thread_count);

    // Launch threads over contiguous chunks
    const std::size_t n = texts.size();
    const std::size_t base = (n / thread_count);
    const std::size_t rem = (n % thread_count);

    for (std::size_t t = 0U; t < thread_count; ++t) {
        const std::size_t start = (t * base) + ((t < rem) ? t : rem);
        const std::size_t stop = start + base + ((t < rem) ? 1U : 0U);

        workers.emplace_back([t, start, stop, &texts, &local_counts]() {
            // Zero-initialize local accumulator
            std::array<std::uint32_t, alphabet_size> local{};
            for (std::size_t i = 0U; i < alphabet_size; ++i) {
                local[i] = 0U;
            }

            using char_int_t = std::char_traits<char>::int_type;

            for (std::size_t i = start; i < stop; ++i) {
                const std::string& s = texts[i];
                for (const char ch : s) {
                    const char_int_t ci = std::char_traits<char>::to_int_type(ch);
                    const char_int_t lower = std::tolower(ci);

                    // Map only ASCII letters a-z after lowering
                    const char_int_t a_code = std::char_traits<char>::to_int_type('a');
                    const char_int_t z_code = std::char_traits<char>::to_int_type('z');

                    if ((lower >= a_code) && (lower <= z_code)) {
                        const std::size_t idx = static_cast<std::size_t>(static_cast<std::uint32_t>(lower - a_code));
                        ++(local[idx]);
                    }
                }
            }

            local_counts[t] = local;
        });
    }

    // Join threads
    for (std::thread& th : workers) {
        if (th.joinable()) {
            th.join();
        }
    }

    // Reduce local counts into a single array
    std::array<std::uint32_t, alphabet_size> total{};
    for (std::size_t i = 0U; i < alphabet_size; ++i) {
        total[i] = 0U;
    }

    for (const auto& lc : local_counts) {
        for (std::size_t i = 0U; i < alphabet_size; ++i) {
            total[i] = static_cast<std::uint32_t>(total[i] + lc[i]);
        }
    }

    // Build result map (omit zero entries)
    frequency_map result{};
    result.reserve(alphabet_size);
    for (std::size_t i = 0U; i < alphabet_size; ++i) {
        if (total[i] != 0U) {
            result[letters[i]] = total[i];
        }
    }

    return result;
}

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map {
    if (texts.empty()) {
        return {};
    }

    std::vector<std::string> owned{};
    owned.reserve(texts.size());
    for (const std::string_view sv : texts) {
        owned.emplace_back(sv);
    }
    return frequency(owned);
}

}  // namespace parallel_letter_frequency
