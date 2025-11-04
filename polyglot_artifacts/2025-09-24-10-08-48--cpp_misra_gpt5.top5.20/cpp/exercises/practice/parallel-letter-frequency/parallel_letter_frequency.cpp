#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cstddef>
#include <future>
#include <locale>
#include <map>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

namespace {
frequency_map count_range(const std::vector<std::string_view>::const_iterator begin_it,
                          const std::vector<std::string_view>::const_iterator end_it,
                          const std::locale& loc)
{
    frequency_map local{};
    const std::ctype<char>& facet = std::use_facet<std::ctype<char>>(loc);

    for (auto it = begin_it; it != end_it; ++it) {
        const std::string_view s = *it;
        for (const char ch : s) {
            if (facet.is(std::ctype_base::alpha, ch)) {
                const char lower = facet.tolower(ch);
                auto found = local.find(lower);
                if (found == local.end()) {
                    local.emplace(lower, static_cast<std::uint32_t>(1U));
                } else {
                    found->second = (found->second + static_cast<std::uint32_t>(1U));
                }
            } else {
                // non-letter; ignore
            }
        }
    }
    return local;
}
}  // anonymous namespace

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    frequency_map result{};

    if (texts.empty()) {
        return result;
    } else {
        // continue to compute
    }

    const std::locale loc{};
    const std::size_t hw = static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t max_blocks = (hw == 0U) ? 2U : hw;
    const std::size_t blocks = (texts.size() < max_blocks) ? texts.size() : max_blocks;

    if (blocks <= 1U) {
        frequency_map single = count_range(texts.cbegin(), texts.cend(), loc);
        for (const auto& kv : single) {
            const char key = kv.first;
            const std::uint32_t value = kv.second;
            result[key] = (result[key] + value);
        }
        return result;
    } else {
        // proceed with parallel execution
    }

    std::vector<std::future<frequency_map>> futures{};
    futures.reserve(blocks);

    const std::size_t base = (texts.size() / blocks);
    const std::size_t rem = (texts.size() % blocks);

    std::size_t start_index = 0U;
    for (std::size_t i = 0U; i < blocks; ++i) {
        const std::size_t extra = (i < rem) ? 1U : 0U;
        const std::size_t count = (base + extra);

        const auto begin_it = texts.cbegin() + static_cast<std::ptrdiff_t>(start_index);
        const auto end_it = begin_it + static_cast<std::ptrdiff_t>(count);

        futures.emplace_back(std::async(std::launch::async, [begin_it, end_it, loc]() {
            return count_range(begin_it, end_it, loc);
        }));

        start_index = (start_index + count);
    }

    for (auto& fut : futures) {
        frequency_map partial = fut.get();
        for (const auto& kv : partial) {
            const char key = kv.first;
            const std::uint32_t value = kv.second;
            result[key] = (result[key] + value);
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
