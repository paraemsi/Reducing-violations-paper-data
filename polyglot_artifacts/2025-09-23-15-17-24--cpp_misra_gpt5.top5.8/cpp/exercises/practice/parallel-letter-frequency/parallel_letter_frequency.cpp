#include "parallel_letter_frequency.h"

#include <cctype>
#include <cstddef>
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace {

// Helper to count letters in a single text (case-insensitive, letters only)
auto count_text(const std::string_view& text) -> parallel_letter_frequency::frequency_map
{
    parallel_letter_frequency::frequency_map local{};

    for (const std::string_view::value_type ch : text) {
        // Use cctype helpers; do not rely on numeric character values
        const std::char_traits<char>::int_type ch_int =
            std::char_traits<char>::to_int_type(static_cast<char>(ch));
        if ((std::isalpha(ch_int) != 0)) {
            const std::char_traits<char>::int_type lower_int = std::tolower(ch_int);
            const char lower = std::char_traits<char>::to_char_type(lower_int);
            ++(local[lower]);
        }
    }

    return local;
}

}  // namespace

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const std::size_t total = texts.size();
    if ((total == static_cast<std::size_t>(0U))) {
        return {};
    }

    const std::size_t hc_reported = static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t hc = ((hc_reported == static_cast<std::size_t>(0U)) ? static_cast<std::size_t>(2U)
                                          : hc_reported);
    const std::size_t thread_count = (hc < total) ? hc : total;

    std::vector<frequency_map> partials(thread_count);
    std::vector<std::thread> workers{};
    workers.reserve(thread_count);

    const std::size_t base = total / thread_count;
    const std::size_t rem = total % thread_count;

    std::size_t begin = static_cast<std::size_t>(0U);
    for (std::size_t i = static_cast<std::size_t>(0U); i < thread_count; ++i) {
        const std::size_t chunk = base + ((i < rem) ? static_cast<std::size_t>(1U) : static_cast<std::size_t>(0U));
        const std::size_t end = begin + chunk;

        workers.emplace_back([&texts, &partials, i, begin, end]() {
            frequency_map local{};
            for (std::size_t idx = begin; idx < end; ++idx) {
                const frequency_map counted = count_text(texts[idx]);
                for (const auto& kv : counted) {
                    local[kv.first] = static_cast<std::uint32_t>(local[kv.first] + kv.second);
                }
            }
            partials[i] = std::move(local);
        });

        begin = end;
    }

    for (auto& t : workers) {
        if (t.joinable()) {
            t.join();
        }
    }

    frequency_map result{};
    for (const auto& part : partials) {
        for (const auto& kv : part) {
            result[kv.first] = static_cast<std::uint32_t>(result[kv.first] + kv.second);
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
