#include "allergies.h"

#include <array>
#include <vector>
#include <unordered_set>
#include <string>

namespace allergies {

namespace {
constexpr std::array<allergen, 8> all_allergens{{
    allergen::eggs,
    allergen::peanuts,
    allergen::shellfish,
    allergen::strawberries,
    allergen::tomatoes,
    allergen::chocolate,
    allergen::pollen,
    allergen::cats
}};
}  // namespace

allergy_test::allergy_test(unsigned int score) : score_{score} {}

bool allergy_test::is_allergic_to(allergen a) const {
    return (score_ & static_cast<unsigned int>(a)) != 0u;
}

std::vector<allergen> allergy_test::get_allergens() const {
    std::vector<allergen> result;
    for (auto a : all_allergens) {
        if (is_allergic_to(a)) {
            result.push_back(a);
        }
    }
    return result;
}

bool allergy_test::is_allergic_to(const std::string& allergen_name) const {
    allergen a{};
    if (allergen_name == "eggs")
        a = allergen::eggs;
    else if (allergen_name == "peanuts")
        a = allergen::peanuts;
    else if (allergen_name == "shellfish")
        a = allergen::shellfish;
    else if (allergen_name == "strawberries")
        a = allergen::strawberries;
    else if (allergen_name == "tomatoes")
        a = allergen::tomatoes;
    else if (allergen_name == "chocolate")
        a = allergen::chocolate;
    else if (allergen_name == "pollen")
        a = allergen::pollen;
    else if (allergen_name == "cats")
        a = allergen::cats;
    else
        return false;  // unknown allergen name
    return is_allergic_to(a);
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (auto a : all_allergens) {
        if (is_allergic_to(a)) {
            switch (a) {
                case allergen::eggs: result.insert("eggs"); break;
                case allergen::peanuts: result.insert("peanuts"); break;
                case allergen::shellfish: result.insert("shellfish"); break;
                case allergen::strawberries: result.insert("strawberries"); break;
                case allergen::tomatoes: result.insert("tomatoes"); break;
                case allergen::chocolate: result.insert("chocolate"); break;
                case allergen::pollen: result.insert("pollen"); break;
                case allergen::cats: result.insert("cats"); break;
            }
        }
    }
    return result;
}

}  // namespace allergies
