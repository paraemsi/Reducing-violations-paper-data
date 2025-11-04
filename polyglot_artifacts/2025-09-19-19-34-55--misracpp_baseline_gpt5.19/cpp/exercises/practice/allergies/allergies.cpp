#include "allergies.h"

#include <array>

namespace {
struct Item {
    const char* name;
    unsigned int mask;
};

constexpr std::array<Item, 8> kItems{{
    {"eggs", 1u},
    {"peanuts", 2u},
    {"shellfish", 4u},
    {"strawberries", 8u},
    {"tomatoes", 16u},
    {"chocolate", 32u},
    {"pollen", 64u},
    {"cats", 128u},
}};

inline unsigned int mask_for(const std::string& item) noexcept {
    for (const auto& i : kItems) {
        if (item == i.name) {
            return i.mask;
        }
    }
    return 0u; // unknown item
}
}  // namespace

namespace allergies {

allergy_test::allergy_test(unsigned int score) noexcept : score_{score} {}

bool allergy_test::is_allergic_to(const std::string& item) const noexcept {
    return allergic_to(item);
}

bool allergy_test::allergic_to(const std::string& item) const noexcept {
    const unsigned int mask = mask_for(item);
    return mask != 0u && (score_ & mask) != 0u;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& i : kItems) {
        if ((score_ & i.mask) != 0u) {
            result.emplace(i.name);
        }
    }
    return result;
}

}  // namespace allergies
