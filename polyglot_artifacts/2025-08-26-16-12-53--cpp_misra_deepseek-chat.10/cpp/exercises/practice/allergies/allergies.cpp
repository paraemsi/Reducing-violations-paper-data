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

allergy_test::allergy_test(std::int32_t score) : score_(static_cast<std::uint32_t>(score) & 0xFFU) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    auto it = allergen_scores.find(allergen);
    if (it != allergen_scores.end()) {
        return (score_ & it->second) != 0U;
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& pair : allergen_scores) {
        if ((score_ & pair.second) != 0U) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
