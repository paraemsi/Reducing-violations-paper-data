#include "allergies.h"

#include <unordered_set>
#include <string>
#include <map>

namespace allergies {

const std::map<std::string, unsigned int> allergen_map = {
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128}
};

allergy_test::allergy_test(unsigned int score) : score_(score) {}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    auto it = allergen_map.find(allergen);
    if (it == allergen_map.end()) {
        return false;
    }
    return (score_ & it->second) != 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& pair : allergen_map) {
        if ((score_ & pair.second) != 0) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
