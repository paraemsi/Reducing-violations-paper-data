#include "parallel_letter_frequency.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <execution>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

namespace {
    using counts_array = std::array<std::size_t, 26>;

    inline counts_array make_counts(std::string_view text) {
        counts_array counts{};
        for (unsigned char ch : text) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = static_cast<unsigned char>(ch - 'A' + 'a');
            }
            if (ch >= 'a' && ch <= 'z') {
                counts[static_cast<std::size_t>(ch - 'a')]++;
            }
        }
        return counts;
    }

    inline counts_array combine_counts(const counts_array& a, const counts_array& b) {
        counts_array out{};
        for (std::size_t i = 0; i < out.size(); ++i) {
            out[i] = a[i] + b[i];
        }
        return out;
    }
}  // namespace

frequency_map frequency(const std::vector<std::string_view>& texts) {
    // Transform each string into a local count array and reduce them in parallel.
    const counts_array total = std::transform_reduce(
        std::execution::par,
        texts.begin(), texts.end(),
        counts_array{},
        combine_counts,
        make_counts
    );

    frequency_map result;
    for (std::size_t i = 0; i < total.size(); ++i) {
        if (total[i] != 0) {
            result.emplace(static_cast<char>('a' + static_cast<int>(i)),
                           static_cast<int>(total[i]));
        }
    }
    return result;
}

frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}  // namespace parallel_letter_frequency
