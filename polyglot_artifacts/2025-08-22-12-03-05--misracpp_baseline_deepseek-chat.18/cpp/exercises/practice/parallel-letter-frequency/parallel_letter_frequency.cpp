#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <cctype>
#include <functional>
#include <map>
#include <vector>
#include <string>
#include <numeric>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // To use transform_reduce, we need to provide:
    // 1. An initial value which is a map
    // 2. A binary operation to combine two maps
    // 3. A transform operation to convert each text to a map
    
    // Define the binary operation to merge two maps
    auto merge_maps = [](std::map<char, int> lhs, const std::map<char, int>& rhs) {
        for (const auto& pair : rhs) {
            lhs[pair.first] += pair.second;
        }
        return lhs;
    };
    
    // Define the transform operation to count letters in a single text
    auto count_letters = [](const std::string& text) {
        std::map<char, int> counts;
        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                // Convert to lowercase to count 'A' and 'a' as the same
                char lower_c = std::tolower(static_cast<unsigned char>(c));
                counts[lower_c]++;
            }
        }
        return counts;
    };
    
    // Use transform_reduce to process in parallel
    // The initial value is an empty map
    return std::transform_reduce(
        std::execution::par,
        texts.begin(), texts.end(),
        std::map<char, int>(),
        merge_maps,
        count_letters
    );
}

}
