#include "allergies.h"
#include <string>
#include <unordered_set>
#include <map>

namespace allergies {

namespace {

const std::map<std::string, int> ALLERGENS = {
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

allergy_test::allergy_test(int score) : score_(score & 0xFF) {
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    auto it = ALLERGENS.find(allergen);
    if (it != ALLERGENS.end()) {
        return (score_ & it->second) != 0;
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& pair : ALLERGENS) {
        if ((score_ & pair.second) != 0) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
