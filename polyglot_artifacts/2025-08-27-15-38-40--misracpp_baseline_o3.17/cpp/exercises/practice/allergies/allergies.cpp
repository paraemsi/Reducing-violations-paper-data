#include "allergies.h"

#include <unordered_map>
#include <vector>

namespace allergies {

namespace {

const std::unordered_map<std::string, unsigned int> allergen_scores{
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128},
};

const std::vector<std::string> allergen_names{
    "eggs",
    "peanuts",
    "shellfish",
    "strawberries",
    "tomatoes",
    "chocolate",
    "pollen",
    "cats",
};

}  // namespace

allergy_test::allergy_test(unsigned int score) : score_{score} {
    for (const auto& [item, value] : allergen_scores) {
        if (score_ & value) {
            allergies_.emplace(item);
        }
    }
}

bool allergy_test::is_allergic_to(const std::string& item) const {
    return allergies_.find(item) != allergies_.end();
}

std::vector<std::string> allergy_test::get_allergies() const {
    std::vector<std::string> result;
    for (const auto& name : allergen_names) {
        if (allergies_.find(name) != allergies_.end()) {
            result.emplace_back(name);
        }
    }
    return result;
}

}  // namespace allergies
