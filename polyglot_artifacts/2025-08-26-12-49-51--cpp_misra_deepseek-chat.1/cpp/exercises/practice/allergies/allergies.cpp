#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

namespace {

const std::unordered_map<std::string, unsigned int> ALLERGENS = {
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128}
};

} // namespace

allergy_test::allergy_test(unsigned int score) : score_(score) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    auto it = ALLERGENS.find(allergen);
    if (it != ALLERGENS.end()) {
        // Mask the score to only consider relevant bits
        unsigned int masked_score = score_ & 0xFF;
        // Check if the corresponding bit is set
        return ((masked_score & it->second) != 0);
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    // Mask the score to only consider relevant bits
    unsigned int masked_score = score_ & 0xFF;
    
    for (const auto& allergen : ALLERGENS) {
        if (((masked_score & allergen.second) != 0)) {
            result.emplace(allergen.first);
        }
    }
    return result;
}

}  // namespace allergies
