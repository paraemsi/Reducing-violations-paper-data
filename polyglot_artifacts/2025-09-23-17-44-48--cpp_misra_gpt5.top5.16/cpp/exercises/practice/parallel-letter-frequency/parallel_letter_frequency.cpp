#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <cstdint>
#include <execution>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

namespace
{
    using count_array = std::array<std::int32_t, 26>;

    // Count letters a-z (case-insensitive) in a single text.
    // Uses <cctype> helpers and std::char_traits to avoid direct arithmetic on char.
    auto count_one(const std::string_view& text) -> count_array
    {
        count_array counts{};  // zero-initialized
        const std::int32_t ia = static_cast<std::int32_t>(std::char_traits<char>::to_int_type('a'));
        const std::int32_t iz = static_cast<std::int32_t>(std::char_traits<char>::to_int_type('z'));

        for (const char ch : text)
        {
            const std::int32_t ich = static_cast<std::int32_t>(std::char_traits<char>::to_int_type(ch));

            if (std::isalpha(ich) != 0)
            {
                const std::int32_t lower_ich = static_cast<std::int32_t>(std::tolower(ich));

                if ((lower_ich >= ia) && (lower_ich <= iz))
                {
                    const std::size_t idx = static_cast<std::size_t>(lower_ich - ia);
                    counts[idx] = counts[idx] + static_cast<std::int32_t>(1);
                }
            }
        }

        return counts;
    }

    // Element-wise sum of two count arrays.
    auto sum_arrays(const count_array& a, const count_array& b) -> count_array
    {
        count_array r{};
        for (std::size_t i = 0U; i < r.size(); ++i)
        {
            r[i] = a[i] + b[i];
        }
        return r;
    }
}  // namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    // Parallel transform-reduce over the collection of texts.
    const count_array total =
        std::transform_reduce(std::execution::par, texts.cbegin(), texts.cend(), count_array{}, sum_arrays, count_one);

    frequency_map result{};

    const std::int32_t ia = static_cast<std::int32_t>(std::char_traits<char>::to_int_type('a'));
    for (std::size_t i = 0U; i < total.size(); ++i)
    {
        if (total[i] > 0)
        {
            const std::int32_t code = ia + static_cast<std::int32_t>(i);
            const char letter = std::char_traits<char>::to_char_type(code);
            // total[i] is std::int32_t; mapped type is int.
            result.insert({letter, static_cast<int>(total[i])});
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
