#include "allergies.h"
#include <string>
#include <unordered_set>
#include <map>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(std::int32_t score) : masked_score(static_cast<std::uint32_t>(static_cast<std::uint32_t>(score) & 0xFFU)) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    static const std::map<std::string, std::uint32_t> allergen_scores = {
        {"eggs", 1U},
        {"peanuts", 2U},
        {"shellfish", 4U},
        {"strawberries", 8U},
        {"tomatoes", 16U},
        {"chocolate", 32U},
        {"pollen", 64U},
        {"cats", 128U}
    };
    
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        return ((masked_score & it->second) != 0U);
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    static const std::map<std::uint32_t, std::string> score_allergens = {
        {1U, "eggs"},
        {2U, "peanuts"},
        {4U, "shellfish"},
        {8U, "strawberries"},
        {16U, "tomatoes"},
        {32U, "chocolate"},
        {64U, "pollen"},
        {128U, "cats"}
    };
    
    std::unordered_set<std::string> result;
    for (const auto& pair : score_allergens) {
        if (((masked_score & pair.first) != 0U)) {
            result.emplace(pair.second);
        }
    }
    return result;
}

}  // namespace allergies
