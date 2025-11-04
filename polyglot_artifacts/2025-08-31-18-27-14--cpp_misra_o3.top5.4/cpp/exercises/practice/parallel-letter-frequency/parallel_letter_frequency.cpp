#include "parallel_letter_frequency.h"

#include <future>

namespace parallel_letter_frequency {

namespace {

/*  Count letters inside a single text.
 *  This helper avoids any numeric manipulation of
 *  character values – it relies solely on equality
 *  comparisons, which complies with the MISRA rule
 *  regarding character usage.                      */
frequency_map count_letters_in_text(const std::string& text)
{
    frequency_map local{};

    for (char c : text)
    {
        switch (c)
        {
            case 'a': case 'A': ++local['a']; break;
            case 'b': case 'B': ++local['b']; break;
            case 'c': case 'C': ++local['c']; break;
            case 'd': case 'D': ++local['d']; break;
            case 'e': case 'E': ++local['e']; break;
            case 'f': case 'F': ++local['f']; break;
            case 'g': case 'G': ++local['g']; break;
            case 'h': case 'H': ++local['h']; break;
            case 'i': case 'I': ++local['i']; break;
            case 'j': case 'J': ++local['j']; break;
            case 'k': case 'K': ++local['k']; break;
            case 'l': case 'L': ++local['l']; break;
            case 'm': case 'M': ++local['m']; break;
            case 'n': case 'N': ++local['n']; break;
            case 'o': case 'O': ++local['o']; break;
            case 'p': case 'P': ++local['p']; break;
            case 'q': case 'Q': ++local['q']; break;
            case 'r': case 'R': ++local['r']; break;
            case 's': case 'S': ++local['s']; break;
            case 't': case 'T': ++local['t']; break;
            case 'u': case 'U': ++local['u']; break;
            case 'v': case 'V': ++local['v']; break;
            case 'w': case 'W': ++local['w']; break;
            case 'x': case 'X': ++local['x']; break;
            case 'y': case 'Y': ++local['y']; break;
            case 'z': case 'Z': ++local['z']; break;
            default:
                /* ignore non-alphabetic characters */
                break;
        }
    }

    return local;
}

} // unnamed namespace

frequency_map frequency(const std::vector<std::string>& texts)
{
    std::vector<std::future<frequency_map>> futures{};
    futures.reserve(texts.size());

    for (const std::string& txt : texts)
    {
        futures.emplace_back(
            std::async(std::launch::async, &count_letters_in_text, std::cref(txt))
        );
    }

    frequency_map result{};

    for (std::future<frequency_map>& fut : futures)
    {
        frequency_map local = fut.get();
        for (const auto& kv : local)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

} // namespace parallel_letter_frequency
