#include "parallel_letter_frequency.h"

#include <future>
#include <string_view>

namespace parallel_letter_frequency {

namespace
{

// Normalize a character to its lowercase alphabetic form.
// Returns '\0' if the input is not an alphabetic letter.
constexpr char normalize_letter(const char ch) noexcept
{
    switch (ch)
    {
        case 'A': case 'a': { return 'a'; }
        case 'B': case 'b': { return 'b'; }
        case 'C': case 'c': { return 'c'; }
        case 'D': case 'd': { return 'd'; }
        case 'E': case 'e': { return 'e'; }
        case 'F': case 'f': { return 'f'; }
        case 'G': case 'g': { return 'g'; }
        case 'H': case 'h': { return 'h'; }
        case 'I': case 'i': { return 'i'; }
        case 'J': case 'j': { return 'j'; }
        case 'K': case 'k': { return 'k'; }
        case 'L': case 'l': { return 'l'; }
        case 'M': case 'm': { return 'm'; }
        case 'N': case 'n': { return 'n'; }
        case 'O': case 'o': { return 'o'; }
        case 'P': case 'p': { return 'p'; }
        case 'Q': case 'q': { return 'q'; }
        case 'R': case 'r': { return 'r'; }
        case 'S': case 's': { return 's'; }
        case 'T': case 't': { return 't'; }
        case 'U': case 'u': { return 'u'; }
        case 'V': case 'v': { return 'v'; }
        case 'W': case 'w': { return 'w'; }
        case 'X': case 'x': { return 'x'; }
        case 'Y': case 'y': { return 'y'; }
        case 'Z': case 'z': { return 'z'; }
        default:               { return '\0'; }
    }
}

// Compute the frequency map for a single text.
frequency_map local_frequency(const std::string_view text)
{
    frequency_map result {};

    for (const char ch : text)
    {
        const char letter { normalize_letter(ch) };
        if (letter != '\0')
        {
            ++result[letter];
        }
    }

    return result;
}

} // unnamed namespace

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    std::vector<std::future<frequency_map>> tasks {};
    tasks.reserve(texts.size());

    for (const std::string_view text : texts)
    {
        tasks.emplace_back(
            std::async(std::launch::async, local_frequency, text));
    }

    frequency_map aggregate {};

    for (std::future<frequency_map>& task : tasks)
    {
        const frequency_map local { task.get() };
        for (const auto& kv : local)
        {
            aggregate[kv.first] += kv.second;
        }
    }

    return aggregate;
}

}
