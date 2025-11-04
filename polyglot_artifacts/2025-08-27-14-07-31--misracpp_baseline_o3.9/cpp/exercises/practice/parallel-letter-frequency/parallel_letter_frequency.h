#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

 // Compute the frequency of each letter (a–z, case-insensitive) in the given
 // texts. The work is distributed across multiple threads using std::async.
using frequency_map = std::map<char, int>;
frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

