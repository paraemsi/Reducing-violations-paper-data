#include "allergies.h"

namespace allergies {

const std::array<allergen, 8> allergy_test::all_allergens{
    allergen::eggs, allergen::peanuts, allergen::shellfish,
    allergen::strawberries, allergen::tomatoes, allergen::chocolate,
    allergen::pollen, allergen::cats
};

allergy_test::allergy_test(int score) : score_{score} {
    for (auto item : allergy_test::all_allergens) {
        if (score_ & static_cast<int>(item)) {
            allergies_.emplace(item);
        }
    }
}

bool allergy_test::is_allergic_to(allergen item) const {
    return allergies_.find(item) != allergies_.end();
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    return allergies_;
}

}  // namespace allergies
