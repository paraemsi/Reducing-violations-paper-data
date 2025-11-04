#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(int score) : score_(static_cast<score_t>((static_cast<unsigned int>(score) & 0xFFU))) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    static const std::unordered_map<std::string, score_t> allergen_values = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    
    auto it = allergen_values.find(allergen);
    if (it != allergen_values.end()) {
        // Ensure proper parentheses
        return (((score_ & it->second) != 0));
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    static const std::unordered_map<score_t, std::string> value_allergens = {
        {1, "eggs"},
        {2, "peanuts"},
        {4, "shellfish"},
        {8, "strawberries"},
        {16, "tomatoes"},
        {32, "chocolate"},
        {64, "pollen"},
        {128, "cats"}
    };
    
    std::unordered_set<std::string> result;
    for (const auto& pair : value_allergens) {
        // Ensure proper parentheses
        if (((score_ & pair.first) != 0)) {
            result.emplace(pair.second);
        }
    }
    return result;
}

}  // namespace allergies
