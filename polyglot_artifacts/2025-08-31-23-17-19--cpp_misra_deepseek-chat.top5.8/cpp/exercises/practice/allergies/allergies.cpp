#include "allergies.h"
#include <string>
#include <unordered_set>
#include <map>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(score_t score) : score_(score & static_cast<score_t>(0xFF)) {
}

bool allergy_test::is_allergic_to(const std::string& item) const {
    static const std::map<std::string, score_t> allergen_scores = {
        {"eggs", static_cast<score_t>(1)},
        {"peanuts", static_cast<score_t>(2)},
        {"shellfish", static_cast<score_t>(4)},
        {"strawberries", static_cast<score_t>(8)},
        {"tomatoes", static_cast<score_t>(16)},
        {"chocolate", static_cast<score_t>(32)},
        {"pollen", static_cast<score_t>(64)},
        {"cats", static_cast<score_t>(128)}
    };
    
    auto it = allergen_scores.find(item);
    if (it != allergen_scores.end()) { 
        return ((score_ & it->second) != static_cast<score_t>(0));
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    static const std::map<score_t, std::string> score_allergens = {
        {static_cast<score_t>(1), "eggs"},
        {static_cast<score_t>(2), "peanuts"},
        {static_cast<score_t>(4), "shellfish"},
        {static_cast<score_t>(8), "strawberries"},
        {static_cast<score_t>(16), "tomatoes"},
        {static_cast<score_t>(32), "chocolate"},
        {static_cast<score_t>(64), "pollen"},
        {static_cast<score_t>(128), "cats"}
    };
    
    std::unordered_set<std::string> result;
    for (const auto& pair : score_allergens) {
        if ((score_ & pair.first) != static_cast<score_t>(0)) { 
            result.emplace(pair.second);
        }
    }
    return result;
}

}  // namespace allergies
