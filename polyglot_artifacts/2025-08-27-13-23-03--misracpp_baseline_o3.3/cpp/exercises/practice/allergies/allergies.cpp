#include "allergies.h"
#include <utility>

namespace allergies {

namespace {
constexpr std::array<Allergen, 8> kKnownAllergens{{
    Allergen::eggs,
    Allergen::peanuts,
    Allergen::shellfish,
    Allergen::strawberries,
    Allergen::tomatoes,
    Allergen::chocolate,
    Allergen::pollen,
    Allergen::cats
}};
constexpr std::array<std::pair<const char*, Allergen>, 8> kAllergenPairs{{
    {"eggs", Allergen::eggs},
    {"peanuts", Allergen::peanuts},
    {"shellfish", Allergen::shellfish},
    {"strawberries", Allergen::strawberries},
    {"tomatoes", Allergen::tomatoes},
    {"chocolate", Allergen::chocolate},
    {"pollen", Allergen::pollen},
    {"cats", Allergen::cats}
}};
}  // namespace

Allergies::Allergies(unsigned int score) : score_{score} {}

bool Allergies::is_allergic_to(Allergen allergen) const {
    return (score_ & static_cast<unsigned int>(allergen)) != 0u;
}

bool Allergies::is_allergic_to(const std::string& allergen) const {
    for (const auto& pair : kAllergenPairs) {
        if (allergen == pair.first) {
            return is_allergic_to(pair.second);
        }
    }
    return false;
}

std::unordered_set<std::string> Allergies::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& pair : kAllergenPairs) {
        if (is_allergic_to(pair.second)) {
            result.emplace(pair.first);
        }
    }
    return result;
}

}  // namespace allergies
