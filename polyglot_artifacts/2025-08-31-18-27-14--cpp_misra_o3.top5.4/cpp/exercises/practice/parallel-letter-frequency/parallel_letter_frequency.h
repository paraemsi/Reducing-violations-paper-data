#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <cstddef>
#include <unordered_map>
#include <string>
#include <vector>

namespace parallel_letter_frequency {

/*  Counter type for individual letter counts.
 *  Using an alias avoids direct usage of the built-in
 *  signed integer type name, satisfying the MISRA rule. */
using counter_t = std::uint32_t;

/*  Custom hash that does not rely on the numeric
 *  value of the character – it maps each supported
 *  letter to a unique integral constant explicitly.   */
struct LetterHash final
{
    std::size_t operator()(char c) const noexcept
    {
        switch (c)
        {
            case 'a': return 0u;
            case 'b': return 1u;
            case 'c': return 2u;
            case 'd': return 3u;
            case 'e': return 4u;
            case 'f': return 5u;
            case 'g': return 6u;
            case 'h': return 7u;
            case 'i': return 8u;
            case 'j': return 9u;
            case 'k': return 10u;
            case 'l': return 11u;
            case 'm': return 12u;
            case 'n': return 13u;
            case 'o': return 14u;
            case 'p': return 15u;
            case 'q': return 16u;
            case 'r': return 17u;
            case 's': return 18u;
            case 't': return 19u;
            case 'u': return 20u;
            case 'v': return 21u;
            case 'w': return 22u;
            case 'x': return 23u;
            case 'y': return 24u;
            case 'z': return 25u;
            default:  return 26u; /* non-alphabetic */
        }
    }
};

/*  Alias holding the result type:
 *  maps a letter to its occurrence count           */
using frequency_map = std::unordered_map<char, counter_t, LetterHash>;

/*  Compute the frequency of Latin letters [A-Z][a-z]
 *  in the supplied collection of texts using parallel
 *  execution.
 *
 *  Only alphabetic characters are counted; any other
 *  characters are ignored.                          */
frequency_map frequency(const std::vector<std::string>& texts);

} // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

