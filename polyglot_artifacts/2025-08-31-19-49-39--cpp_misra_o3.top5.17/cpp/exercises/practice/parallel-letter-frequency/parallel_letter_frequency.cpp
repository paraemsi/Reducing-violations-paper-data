#include "parallel_letter_frequency.h"

#include <algorithm>
#include <array>
#include <execution>
#include <string_view>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    /*  One array of 26 counters per input text – filled in parallel
     *  then reduced sequentially. */
    std::vector<std::array<std::uint32_t, 26U>> partials(texts.size());

    /*  Parallel phase: count per-text occurrences without sharing data. */
    std::for_each(
        std::execution::par,
        texts.begin(),
        texts.end(),
        [&partials, &texts](const std::string_view& text) {
            /*  Obtain the element’s index in a well-defined manner.
             *  Signed pointer difference is explicitly converted to the
             *  required unsigned type – the value is guaranteed to be
             *  non-negative because both pointers reference elements of
             *  the same std::vector. */
            const std::size_t index =
                static_cast<std::size_t>((&text) - (texts.data()));

            auto& local = partials[index];
            local.fill(0U);

            for (char const ch : text) {
                switch (ch) {
                    case 'a': case 'A': ++local[0U]; break;
                    case 'b': case 'B': ++local[1U]; break;
                    case 'c': case 'C': ++local[2U]; break;
                    case 'd': case 'D': ++local[3U]; break;
                    case 'e': case 'E': ++local[4U]; break;
                    case 'f': case 'F': ++local[5U]; break;
                    case 'g': case 'G': ++local[6U]; break;
                    case 'h': case 'H': ++local[7U]; break;
                    case 'i': case 'I': ++local[8U]; break;
                    case 'j': case 'J': ++local[9U]; break;
                    case 'k': case 'K': ++local[10U]; break;
                    case 'l': case 'L': ++local[11U]; break;
                    case 'm': case 'M': ++local[12U]; break;
                    case 'n': case 'N': ++local[13U]; break;
                    case 'o': case 'O': ++local[14U]; break;
                    case 'p': case 'P': ++local[15U]; break;
                    case 'q': case 'Q': ++local[16U]; break;
                    case 'r': case 'R': ++local[17U]; break;
                    case 's': case 'S': ++local[18U]; break;
                    case 't': case 'T': ++local[19U]; break;
                    case 'u': case 'U': ++local[20U]; break;
                    case 'v': case 'V': ++local[21U]; break;
                    case 'w': case 'W': ++local[22U]; break;
                    case 'x': case 'X': ++local[23U]; break;
                    case 'y': case 'Y': ++local[24U]; break;
                    case 'z': case 'Z': ++local[25U]; break;
                    default:                             break;
                }
            }
        });

    /*  Sequential reduction of per-text counters into the final map. */
    std::array<std::uint32_t, 26U> total {};
    for (const auto& part : partials) {
        for (std::size_t i = 0U; i < 26U; ++i) {
            total[i] += part[i];
        }
    }

    constexpr std::array<char, 26U> letters {
        'a','b','c','d','e','f','g','h','i','j','k','l','m',
        'n','o','p','q','r','s','t','u','v','w','x','y','z'
    };

    frequency_map result {};
    for (std::size_t i = 0U; i < 26U; ++i) {
        if (total[i] != 0U) {
            result[letters[i]] = total[i];
        }
    }

    return result;
}

}   // namespace parallel_letter_frequency
