#include "allergies.h"

namespace allergies {

namespace {
struct item { const char* name; unsigned int value; };

constexpr item kAllergens[] = {
    {"eggs", 1u},
    {"peanuts", 2u},
    {"shellfish", 4u},
    {"strawberries", 8u},
    {"tomatoes", 16u},
    {"chocolate", 32u},
    {"pollen", 64u},
    {"cats", 128u}
};

inline unsigned int value_for(const std::string& name) {
    for (const auto& a : kAllergens) {
        if (name == a.name) {
            return a.value;
        }
    }
    return 0u;
}
}  // unnamed namespace

allergy_test::allergy_test(unsigned int score)
    : score_{score & 0xFFu} {}

bool allergy_test::is_allergic_to(const std::string& item) const {
    return (score_ & value_for(item)) != 0u;
}

std::unordered_set<std::string> allergy_test::get_allergies() const {
    std::unordered_set<std::string> result;
    for (const auto& a : kAllergens) {
        if ((score_ & a.value) != 0u) {
            result.emplace(a.name);
        }
    }
    return result;
}

}  // namespace allergies
