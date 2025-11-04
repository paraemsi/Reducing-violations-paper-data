#include "allergies.h"
#include <unordered_map>

namespace allergies {

    static const std::vector<std::string> allergen_names = {
        "eggs",
        "peanuts",
        "shellfish",
        "strawberries",
        "tomatoes",
        "chocolate",
        "pollen",
        "cats"
    };

    static const std::unordered_map<std::string, unsigned int> allergen_map = {
        {"eggs", 1},
        {"peanuts", 2},
        {"shellfish", 4},
        {"strawberries", 8},
        {"tomatoes", 16},
        {"chocolate", 32},
        {"pollen", 64},
        {"cats", 128}
    };

    allergies::allergy_test::allergy_test(unsigned int score)
        : score_(score) {}

    bool allergies::allergy_test::is_allergic_to(const std::string& allergen) const {
        auto it = allergen_map.find(allergen);
        if (it == allergen_map.end()) return false;
        return (score_ & it->second) != 0;
    }

    std::unordered_set<std::string> allergies::allergy_test::get_allergies() const {
        std::unordered_set<std::string> result;
        for (const auto& name : allergen_names) {
            if (is_allergic_to(name)) {
                result.emplace(name);
            }
        }
        return result;
    }

}  // namespace allergies
