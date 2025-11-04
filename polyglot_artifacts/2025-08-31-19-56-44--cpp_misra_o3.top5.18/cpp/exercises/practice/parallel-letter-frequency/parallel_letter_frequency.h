#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/**
 * \brief Count the frequency of each ASCII letter (case–insensitive) in a list
 *        of input texts, using parallel computation.
 *
 * \param input_texts A collection of texts to analyse.
 * \return A map that holds the count for every letter that occurs at least once.
 *
 * \note The public interface must match the Exercism tests, therefore the map
 *       uses \c char keys and \c int values.
 */
std::map<char, int> frequency(const std::vector<std::string_view>& input_texts);

}   // namespace parallel_letter_frequency

#endif

