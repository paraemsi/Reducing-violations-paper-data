#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(score_t score) : score_(score & static_cast<score_t>(0xFFU)) {
    // Mask to only consider the first 8 bits (up to 255)
    // This ignores allergens not in the predefined list
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    static const std::unordered_map<std::string, score_t> allergen_scores = {
        {"eggs", static_cast<score_t>(1U)},
        {"peanuts", static_cast<score_t>(2U)},
        {"shellfish", static_cast<score_t>(4U)},
        {"strawberries", static_cast<score_t>(8U)},
        {"tomatoes", static_cast<score_t>(16U)},
        {"chocolate", static_cast<score_t>(32U)},
        {"pollen", static_cast<score_t>(64U)},
        {"cats", static_cast<score_t>(128U)}
    };
    
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        return ((score_ & it->second) != static_cast<score_t>(0U));
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    static const std::unordered_map<score_t, std::string> score_allergens = {
        {static_cast<score_t>(1U), "eggs"},
        {static_cast<score_t>(2U), "peanuts"},
        {static_cast<score_t>(4U), "shellfish"},
        {static_cast<score_t>(8U), "strawberries"},
        {static_cast<score_t>(16U), "tomatoes"},
        {static_cast<score_t>(32U), "chocolate"},
        {static_cast<score_t>(64U), "pollen"},
        {static_cast<score_t>(128U), "cats"}
    };
    
    std::unordered_set<std::string> result;
    for (const auto& pair : score_allergens) {
        if ((score_ & pair.first) != static_cast<score_t>(0U)) {
            result.emplace(pair.second);
        }
    }
    return result;
}

}  // namespace allergies
