#include "allergies.h"

namespace {
    struct Allergen {
        const char* name;
        unsigned int value;
    };
    constexpr Allergen kAllergens[] = {
        {"eggs", 1u},
        {"peanuts", 2u},
        {"shellfish", 4u},
        {"strawberries", 8u},
        {"tomatoes", 16u},
        {"chocolate", 32u},
        {"pollen", 64u},
        {"cats", 128u},
    };
}

namespace allergies {

allergy_test::allergy_test(unsigned int score)
    : score_(score & 0xFFu) {}

bool allergy_test::is_allergic_to(const std::string& allergen) const {
    for (const auto& a : kAllergens) {
        if (allergen == a.name) {
            return (score_ & a.value) != 0u;
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& a : kAllergens) {
        if ((score_ & a.value) != 0u) {
            result.emplace(a.name);
        }
    }
    return result;
}



}  // namespace allergies
