#include "allergies.h"
#include <string>
#include <unordered_set>
#include <map>
#include <cstdint>

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) : score_(score & 0xFF) {
}

bool allergy_test::is_allergic_to(const std::string& item) const {
    static const std::map<std::string, std::uint32_t> allergen_values = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };
    
    auto it = allergen_values.find(item);
    if (it != allergen_values.end()) {
        return ((score_ & it->second) != 0);
    }
    return false;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    static const std::map<std::uint32_t, std::string> value_allergens = {
        {1, "eggs"},
        {2, "peanuts"},
        {4, "shellfish"},
        {8, "strawberries"},
        {16, "tomatoes"},
        {32, "chocolate"},
        {64, "pollen"},
        {128, "cats"}
    };
    
    std::unordered_set<std::string> result;
    for (const auto& pair : value_allergens) {
        if ((score_ & pair.first) != 0) {
            result.emplace(pair.second);
        }
    }
    return result;
}

}  // namespace allergies
