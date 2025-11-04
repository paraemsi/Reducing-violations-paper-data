#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <locale>
#include <string_view>

namespace parallel_letter_frequency {

/*
 * Implementation utilises C++17 parallel algorithms: every input string
 * is transformed into its own frequency_map in parallel.  The merge step
 * then combines these partial maps into the final result.  This avoids
 * shared-state contention while still providing concurrency.
 */
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    /* Handle the trivial case early */
    if(texts.empty())
    {
        return {};
    }

    /* One partial result map per input text */
    std::vector<frequency_map> partials(texts.size());

    const std::locale loc{};

    /* Parallel transform – populate the partial maps */
    std::transform(std::execution::par,
                   texts.begin(),
                   texts.end(),
                   partials.begin(),
                   [&loc](const std::string_view& str) -> frequency_map
                   {
                       frequency_map local_result{};

                       for(char ch : str)
                       {
                           if(std::isalpha(static_cast<unsigned char>(ch), loc) != 0)
                           {
                               const char lowered =
                                   std::tolower(static_cast<unsigned char>(ch), loc);
                               ++local_result[lowered];
                           }
                       }

                       return local_result;
                   });

    /* Merge partial results */
    frequency_map total{};
    for(const auto& part : partials)
    {
        for(const auto& kv : part)
        {
            total[kv.first] += kv.second;
        }
    }

    return total;
}

}
