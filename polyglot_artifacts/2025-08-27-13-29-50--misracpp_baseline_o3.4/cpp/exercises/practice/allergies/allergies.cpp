#include "allergies.h"
#include <utility>

namespace allergies {

static const std::vector<std::pair<std::string, unsigned int>> kAllAllergens{
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128}
};

allergy_test::allergy_test(unsigned int score) {
    for (const auto& allergen : kAllAllergens) {
        const std::string& name = allergen.first;
        unsigned int value = allergen.second;
        if (score & value) {
            allergies_.emplace(name);
        }
    }
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    return allergies_.find(allergen) != allergies_.end();
}

std::vector<std::string> allergy_test::get_allergies() const {
    std::vector<std::string> result;
    result.reserve(allergies_.size());
    for (const auto& allergen : kAllAllergens) {
        const std::string& name = allergen.first;
        if (allergies_.count(name)) {
            result.push_back(name);
        }
    }
    return result;
}

}  // namespace allergies
