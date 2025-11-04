#include "allergies.h"

#include <array>
#include <utility>
#include <vector>
#include <string>

namespace allergies {

namespace {
    // Helper: mapping of allergen enum values to their score values.
    constexpr std::array<std::pair<allergen, unsigned int>, 8> allergen_map{{
        {allergen::eggs, 1},
        {allergen::peanuts, 2},
        {allergen::shellfish, 4},
        {allergen::strawberries, 8},
        {allergen::tomatoes, 16},
        {allergen::chocolate, 32},
        {allergen::pollen, 64},
        {allergen::cats, 128}
    }};

    // Convert allergen enum to its canonical string representation
    inline const char* to_string(allergen a) {
        switch (a) {
            case allergen::eggs: return "eggs";
            case allergen::peanuts: return "peanuts";
            case allergen::shellfish: return "shellfish";
            case allergen::strawberries: return "strawberries";
            case allergen::tomatoes: return "tomatoes";
            case allergen::chocolate: return "chocolate";
            case allergen::pollen: return "pollen";
            case allergen::cats: return "cats";
            default: return "";
        }
    }
} // namespace

allergies::allergies(unsigned int score)
    : score_{score} {
    compute_allergies();
}

void allergies::allergies::compute_allergies() {
    for (const auto& [type, value] : allergen_map) {
        if (score_ & value) {
            allergies_.emplace(type);
        }
    }
}

bool allergies::allergies::is_allergic_to(allergen allergen) const {
    return allergies_.find(allergen) != allergies_.end();
}

bool allergies::allergies::is_allergic_to(const std::string& allergen_name) const {
    for (const auto& [type, value] : allergen_map) {
        if (allergen_name == to_string(type)) {
            return allergies_.count(type);
        }
    }
    return false;
}

std::vector<std::string> allergies::allergies::get_allergies() const {
    std::vector<std::string> result;
    for (const auto& [type, value] : allergen_map) {
        if (allergies_.count(type)) {
            result.emplace_back(to_string(type));
        }
    }
    return result;
}

}  // namespace allergies
