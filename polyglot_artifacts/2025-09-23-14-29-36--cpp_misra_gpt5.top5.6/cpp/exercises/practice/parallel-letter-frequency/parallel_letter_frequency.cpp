#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    frequency_map result{};

    const std::size_t text_count = texts.size();
    if (text_count == static_cast<std::size_t>(0U)) {
        return result;
    }

    std::size_t concurrency = static_cast<std::size_t>(std::thread::hardware_concurrency());
    if ((concurrency == static_cast<std::size_t>(0U)) || (concurrency > text_count)) {
        concurrency = text_count;
    }

    std::vector<std::thread> threads{};
    threads.reserve(concurrency);

    std::vector<frequency_map> partials(concurrency);

    auto worker = [&](const std::size_t idx_begin, const std::size_t idx_end, frequency_map& out) {
        for (std::size_t i = idx_begin; i < idx_end; ++i) {
            const std::string_view s = texts.at(i);
            for (const char ch : s) {
                const std::char_traits<char>::int_type ii = std::char_traits<char>::to_int_type(ch);
                if ((std::isalpha(ii)) != 0) {
                    const std::char_traits<char>::int_type li = std::tolower(ii);
                    const char lower = std::char_traits<char>::to_char_type(li);

                    auto it = out.find(lower);
                    if (it == out.end()) {
                        out.emplace(lower, static_cast<std::uint32_t>(1U));
                    } else {
                        it->second = (it->second + static_cast<std::uint32_t>(1U));
                    }
                }
            }
        }
    };

    const std::size_t block = (text_count / concurrency);
    const std::size_t remainder = (text_count % concurrency);
    std::size_t start = static_cast<std::size_t>(0U);

    for (std::size_t t = static_cast<std::size_t>(0U); t < concurrency; ++t) {
        const std::size_t count = (block + ((t < remainder) ? static_cast<std::size_t>(1U) : static_cast<std::size_t>(0U)));
        const std::size_t end = (start + count);
        threads.emplace_back(worker, start, end, std::ref(partials.at(t)));
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    for (const auto& m : partials) {
        for (const auto& kv : m) {
            const char key = kv.first;
            const std::uint32_t val = kv.second;

            auto it = result.find(key);
            if (it == result.end()) {
                result.emplace(key, val);
            } else {
                it->second = (it->second + val);
            }
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
