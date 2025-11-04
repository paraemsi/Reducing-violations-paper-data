#include "allergies.h"
#include <unordered_map>
#include <vector>
#include <string>

namespace allergies {

allergies::allergies(int score)
    : score_{score & 0xFF} // Mask off any allergens beyond the defined set.
{}

// Check if the bit for the given allergen name is set in the stored score.
bool allergies::is_allergic_to(const std::string& item) const {
    static const std::unordered_map<std::string, allergen> allergen_map = {
        {"eggs", allergen::eggs}, {"peanuts", allergen::peanuts},
        {"shellfish", allergen::shellfish}, {"strawberries", allergen::strawberries},
        {"tomatoes", allergen::tomatoes}, {"chocolate", allergen::chocolate},
        {"pollen", allergen::pollen}, {"cats", allergen::cats}};
    auto it = allergen_map.find(item);
    if (it == allergen_map.end()) {
        return false;
    }
    return (score_ & static_cast<int>(it->second)) != 0;
}

// Build and return a set of all allergens whose bits are set.
std::unordered_set<std::string> allergies::get_allergies() const {
    std::unordered_set<std::string> result;
    static const std::vector<std::string> allergens = {
        "eggs", "peanuts", "shellfish", "strawberries",
        "tomatoes", "chocolate", "pollen", "cats"};
    for (const auto& item : allergens) {
        if (is_allergic_to(item)) {
            result.emplace(item);
        }
    }
    return result;
}

}  // namespace allergies
