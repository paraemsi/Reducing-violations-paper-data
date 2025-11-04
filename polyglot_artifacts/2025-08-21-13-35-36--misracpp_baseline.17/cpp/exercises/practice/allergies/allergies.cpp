#include "allergies.h"

namespace allergies {

const std::vector<std::string> allergy_test::allergen_list = {
    "eggs",
    "peanuts",
    "shellfish",
    "strawberries",
    "tomatoes",
    "chocolate",
    "pollen",
    "cats"
};

const std::vector<unsigned int> allergy_test::allergen_scores = {
    1,    // eggs
    2,    // peanuts
    4,    // shellfish
    8,    // strawberries
    16,   // tomatoes
    32,   // chocolate
    64,   // pollen
    128   // cats
};

allergy_test::allergy_test(unsigned int score) : score_(score) {
    parse_allergies();
}

void allergy_test::parse_allergies() {
    unsigned int masked_score = score_;
    for (size_t i = 0; i < allergen_list.size(); ++i) {
        if (masked_score & allergen_scores[i]) {
            allergies_.emplace(allergen_list[i]);
        }
    }
}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    return allergies_.find(allergen) != allergies_.end();
}

std::vector<std::string> allergy_test::get_allergies() const {
    std::vector<std::string> result;
    for (const auto& allergen : allergen_list) {
        if (allergies_.find(allergen) != allergies_.end()) {
            result.push_back(allergen);
        }
    }
    return result;
}

std::unordered_set<std::string> allergy_test::get_allergies_set() const {
    return allergies_;
}

}  // namespace allergies
