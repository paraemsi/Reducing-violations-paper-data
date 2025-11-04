#include "allergies.h"
#include <array>
#include <unordered_map>
#include <string>

namespace allergies {

namespace {
// Ordered list of all allergens we care about
constexpr std::array<Allergen, 8> kAllAllergens{
    Allergen::eggs,
    Allergen::peanuts,
    Allergen::shellfish,
    Allergen::strawberries,
    Allergen::tomatoes,
    Allergen::chocolate,
    Allergen::pollen,
    Allergen::cats
};
}  // namespace

Allergies::Allergies(unsigned int score) {
    for (const auto item : kAllAllergens) {
        if (score & static_cast<unsigned int>(item)) {
            allergies_.emplace(item);
        }
    }
}

bool Allergies::is_allergic_to(Allergen item) const {
    return allergies_.find(item) != allergies_.end();
}

namespace {
// Map between string names and enum values
const std::unordered_map<std::string, Allergen> kNameToAllergen{
    {"eggs",        Allergen::eggs},
    {"peanuts",     Allergen::peanuts},
    {"shellfish",   Allergen::shellfish},
    {"strawberries",Allergen::strawberries},
    {"tomatoes",    Allergen::tomatoes},
    {"chocolate",   Allergen::chocolate},
    {"pollen",      Allergen::pollen},
    {"cats",        Allergen::cats},
};
} // namespace

bool Allergies::is_allergic_to(const std::string& item) const {
    auto it = kNameToAllergen.find(item);
    if (it == kNameToAllergen.end()) {
        return false;
    }
    return is_allergic_to(it->second);
}

std::unordered_set<std::string> Allergies::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& kv : kNameToAllergen) {
        if (is_allergic_to(kv.second)) {
            result.emplace(kv.first);
        }
    }
    return result;
}

}  // namespace allergies
