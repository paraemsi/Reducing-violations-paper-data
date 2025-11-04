#include "allergies.h"
#include <array>

namespace allergies {

namespace {
    constexpr unsigned int mask = 0xFFu;
}

allergy_test::allergy_test(unsigned int score)
    : score_{score & mask} {}

bool allergy_test::is_allergic_to(allergen item) const {
    return (score_ & static_cast<unsigned int>(item)) != 0u;
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result;

    static constexpr std::array<allergen, 8> all_items = {
        allergen::eggs,
        allergen::peanuts,
        allergen::shellfish,
        allergen::strawberries,
        allergen::tomatoes,
        allergen::chocolate,
        allergen::pollen,
        allergen::cats
    };

    for (auto item : all_items) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }

    return result;
}

}  // namespace allergies
