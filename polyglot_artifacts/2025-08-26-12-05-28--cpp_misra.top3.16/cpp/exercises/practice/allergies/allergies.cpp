#include "allergies.h"

namespace allergies {

const std::vector<std::pair<std::string, std::uint16_t>>& Allergies::allergen_list() {
    static const std::vector<std::pair<std::string, std::uint16_t>> allergens = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    return allergens;
}

Allergies::Allergies(std::uint16_t score) {
    for(const auto& allergen : allergen_list()) {
        if(((score & allergen.second) != 0)) {
            allergies_.emplace(allergen.first);
        }
    }
}

bool Allergies::is_allergic_to(const std::string& allergen) const {
    return (allergies_.find(allergen) != allergies_.end());
}

std::vector<std::string> Allergies::get_allergies() const {
    std::vector<std::string> result;
    for(const auto& allergen : allergen_list()) {
        if((allergies_.find(allergen.first) != allergies_.end())) {
            result.push_back(allergen.first);
        }
    }
    return result;
}

Allergies allergy_test(std::uint16_t score) {
    return Allergies(score);
}

}  // namespace allergies
