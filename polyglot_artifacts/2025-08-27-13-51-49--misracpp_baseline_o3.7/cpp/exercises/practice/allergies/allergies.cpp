#include "allergies.h"

namespace allergies {

const std::unordered_map<std::string, unsigned int> allergy_test::allergen_values_{
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128}
};

allergy_test::allergy_test(unsigned int score) : score_{score} {}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    auto it = allergen_values_.find(allergen);
    if (it == allergen_values_.end()) {
        return false;
    }
    return (score_ & it->second) != 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& allergen_pair : allergen_values_) {
        const std::string& name  = allergen_pair.first;
        unsigned int value       = allergen_pair.second;
        if ((score_ & value) != 0) {
            result.emplace(name);
        }
    }
    return result;
}

}  // namespace allergies
