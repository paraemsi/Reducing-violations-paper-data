#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

namespace {

const std::unordered_map<std::string, unsigned int> allergen_scores = {
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
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        // Check if the corresponding bit is set in the score
        // We need to mask out bits beyond the ones we care about
        // Since the note says to ignore components not in the list, we can AND with 255
        // But the maximum score from known allergens is 1+2+4+8+16+32+64+128=255
        unsigned int masked_score = score_ & 255;
        return (masked_score & it->second) != 0;
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    // Mask the score to only consider relevant bits
    unsigned int masked_score = score_ & 255;
    
    // Check each allergen
    for (const auto& pair : allergen_scores) {
        if ((masked_score & pair.second) != 0) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
