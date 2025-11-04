#include "allergies.h"
#include <array>
#include <string>
#include <unordered_set>

namespace allergies {

allergy_test::allergy_test(int score) : score_{score} {}

bool allergy_test::is_allergic_to(allergen a) const {
    return (score_ & a) != 0;
}

bool allergy_test::is_allergic_to(const std::string& allergen_name) const {
    static const std::array<std::pair<allergen, const char*>, 8> mapping{{
        {eggs, "eggs"},
        {peanuts, "peanuts"},
        {shellfish, "shellfish"},
        {strawberries, "strawberries"},
        {tomatoes, "tomatoes"},
        {chocolate, "chocolate"},
        {pollen, "pollen"},
        {cats, "cats"}
    }};
    for (const auto& p : mapping) {
        if (allergen_name == p.second) {
            return is_allergic_to(p.first);
        }
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    static const std::array<std::pair<allergen, const char*>, 8> mapping{{
        {eggs, "eggs"},
        {peanuts, "peanuts"},
        {shellfish, "shellfish"},
        {strawberries, "strawberries"},
        {tomatoes, "tomatoes"},
        {chocolate, "chocolate"},
        {pollen, "pollen"},
        {cats, "cats"}
    }};
    for (const auto& p : mapping) {
        if (is_allergic_to(p.first)) {
            result.emplace(p.second);
        }
    }
    return result;
}

}  // namespace allergies
