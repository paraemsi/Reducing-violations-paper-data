#include "allergies.h"

#include <array>
#include <utility>

namespace allergies {

namespace {
    // Mapping of allergen names to their bitmask values.
    static const std::pair<const char*, unsigned int> allergen_map[] = {
        {"eggs", 1u},
        {"peanuts", 2u},
        {"shellfish", 4u},
        {"strawberries", 8u},
        {"tomatoes", 16u},
        {"chocolate", 32u},
        {"pollen", 64u},
        {"cats", 128u}
    };
} // namespace

allergy_test::allergy_test(unsigned int score) noexcept
    : score_{score} {}

unsigned int allergy_test::mask_for(const std::string& item) {
    for (const auto& entry : allergen_map) {
        if (item == entry.first) {
            return entry.second;
        }
    }
    return 0u;
}

bool allergy_test::is_allergic_to(const std::string& item) const {
    const unsigned int mask = mask_for(item);
    return (score_ & mask) != 0u;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& entry : allergen_map) {
        if ((score_ & entry.second) != 0u) {
            result.emplace(entry.first);
        }
    }
    return result;
}

}  // namespace allergies
