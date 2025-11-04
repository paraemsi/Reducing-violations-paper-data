#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace allergies {

namespace {

const std::unordered_map<std::string, std::uint32_t> allergen_scores = {
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128}
};

}  // namespace

allergy_test::allergy_test(std::uint32_t score) : score_(score) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        // Mask the score to only consider relevant bits
        std::uint32_t const masked_score = (score_ & 0xFFU);
        // Check if the corresponding bit is set using parentheses
        return ((masked_score & it->second) != 0U);
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    // Mask the score to only consider relevant bits
    std::uint32_t const masked_score = (score_ & 0xFFU);
    
    // Check each allergen
    for (const auto& pair : allergen_scores) {
        if ((masked_score & pair.second) != 0U) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
