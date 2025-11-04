#include "allergies.h"

#include <array>

namespace allergies {

    namespace {
        constexpr std::array<allergen, 8> all_items{
            allergen::eggs,
            allergen::peanuts,
            allergen::shellfish,
            allergen::strawberries,
            allergen::tomatoes,
            allergen::chocolate,
            allergen::pollen,
            allergen::cats
        };
    } // namespace

    allergy_test::allergy_test(unsigned int score) {
        for (const auto item : all_items) {
            const auto value = static_cast<unsigned int>(item);
            if (score & value) {
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
