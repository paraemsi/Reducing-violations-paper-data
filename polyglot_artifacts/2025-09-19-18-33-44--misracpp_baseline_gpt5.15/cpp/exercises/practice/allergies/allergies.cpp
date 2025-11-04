#include "allergies.h"

#include <array>

namespace allergies {

namespace {
struct Allergen {
    const char* name;
    unsigned int bit;
};

constexpr std::array<Allergen, 8> kAllergens{{
    {"eggs", 1u},
    {"peanuts", 2u},
    {"shellfish", 4u},
    {"strawberries", 8u},
    {"tomatoes", 16u},
    {"chocolate", 32u},
    {"pollen", 64u},
    {"cats", 128u},
}};
}  // namespace

allergy_test::allergy_test(unsigned int score)
    : score_{score & 0xFFu} {}

bool allergy_test::is_allergic_to(const std::string& item) const {
    for (const auto& a : kAllergens) {
        if (item == a.name) {
            return (score_ & a.bit) != 0u;
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& a : kAllergens) {
        if ((score_ & a.bit) != 0u) {
            result.emplace(a.name);
        }
    }
    return result;
}

}  // namespace allergies
