#include "allergies.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace allergies {

namespace {

const std::unordered_map<std::string, std::uint32_t> allergen_scores = {
    {"eggs", 1U},
    {"peanuts", 2U},
    {"shellfish", 4U},
    {"strawberries", 8U},
    {"tomatoes", 16U},
    {"chocolate", 32U},
    {"pollen", 64U},
    {"cats", 128U}
};

} // namespace

allergy_test::allergy_test(std::uint32_t score) : score_(score & 0xFFU) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        // Add parentheses according to MISRA rules
        return ((score_ & it->second) != 0U);
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& pair : allergen_scores) {
        // Add parentheses according to MISRA rules
        if ((score_ & pair.second) != 0U) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
