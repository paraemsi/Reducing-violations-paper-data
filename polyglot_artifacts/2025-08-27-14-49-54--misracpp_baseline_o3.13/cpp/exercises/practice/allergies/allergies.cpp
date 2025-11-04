#include "allergies.h"

namespace allergies {

const std::unordered_map<std::string, unsigned int> allergy_test::allergen_map_ = {
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128},
};

allergy_test::allergy_test(unsigned int score) : score_(score & 0xFF) {}

bool allergy_test::is_allergic_to(const std::string& item) const {
    auto it = allergen_map_.find(item);
    if (it == allergen_map_.end()) {
        return false;
    }
    return (score_ & it->second) != 0;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& kv : allergen_map_) {
        if (score_ & kv.second) {
            result.emplace(kv.first);
        }
    }
    return result;
}

}  // namespace allergies
