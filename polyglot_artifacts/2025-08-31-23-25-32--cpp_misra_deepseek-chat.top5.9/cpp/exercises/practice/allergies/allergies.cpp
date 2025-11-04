#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_(score) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    // Map allergens to their scores
    static const std::unordered_map<std::string, unsigned int> allergen_scores = {
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
        // Mask the score to only consider relevant bits
        unsigned int const masked_score = (score_ & 0xFFU);
        // Check if the corresponding bit is set in the score
        // Add proper parentheses
        return (((masked_score & it->second) != 0U));
    } else { 
        return false;
    }
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    // Define all possible allergens and their scores
    static const std::unordered_map<std::string, unsigned int> allergen_scores = {
        {"eggs", 1U},
        {"peanuts", 2U},
        {"shellfish", 4U},
        {"strawberries", 8U},
        {"tomatoes", 16U},
        {"chocolate", 32U},
        {"pollen", 64U},
        {"cats", 128U}
    };
    
    std::unordered_set<std::string> result;
    // Mask the score to only consider relevant bits
    unsigned int const masked_score = (score_ & 0xFFU);
    
    // Check each allergen
    for (const auto& pair : allergen_scores) {
        // Add proper parentheses
        if (((masked_score & pair.second) != 0U)) { 
            result.emplace(pair.first);
        } 
    }
    return result;
}

}  // namespace allergies
