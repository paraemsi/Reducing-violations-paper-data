#include "allergies.h"

#include <string>
#include <unordered_map>
#include <unordered_set>

namespace allergies {

static const std::unordered_map<std::string, unsigned int> allergen_scores{
    {"eggs", 1},
    {"peanuts", 2},
    {"shellfish", 4},
    {"strawberries", 8},
    {"tomatoes", 16},
    {"chocolate", 32},
    {"pollen", 64},
    {"cats", 128}};

allergy_test::allergy_test(unsigned int score) : score_(score & 255) {}

bool allergy_test::is_allergic_to(const std::string &item) const {
    const auto it = allergen_scores.find(item);
    return it != allergen_scores.end() && (score_ & it->second);
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto &allergen : allergen_scores) {
        if (score_ & allergen.second) {
            result.emplace(allergen.first);
        }
    }
    return result;
}

}  // namespace allergies
