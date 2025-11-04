#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(unsigned int score) : score_(score) {}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    // Map allergens to their scores
    static const std::unordered_map<std::string, unsigned int> allergen_scores = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        // Check if the corresponding bit is set in the score
        // We need to mask out any bits beyond the ones we care about (0-255)
        unsigned int masked_score = score_ & 0xFF;
        return (masked_score & it->second) != 0;
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    // Map scores to allergens
    static const std::unordered_map<unsigned int, std::string> score_allergens = {
        {1, "eggs"},
        {2, "peanuts"},
        {4, "shellfish"},
        {8, "strawberries"},
        {16, "tomatoes"},
        {32, "chocolate"},
        {64, "pollen"},
        {128, "cats"}
    };
    
    std::unordered_set<std::string> allergies;
    // Mask the score to only consider relevant bits
    unsigned int masked_score = score_ & 0xFF;
    
    // Check each possible allergen
    for (const auto& pair : score_allergens) {
        if ((masked_score & pair.first) != 0) {
            allergies.emplace(pair.second);
        }
    }
    return allergies;
}

}  // namespace allergies
