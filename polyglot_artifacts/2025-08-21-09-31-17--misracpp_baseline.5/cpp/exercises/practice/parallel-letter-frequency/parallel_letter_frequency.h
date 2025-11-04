#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>

namespace parallel_letter_frequency {

typedef std::map<char, int> frequency_map;

frequency_map frequency(const std::vector<std::string>& texts);

} // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

