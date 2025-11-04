#include "allergies.h"

namespace allergies {

allergy_test::allergy_test(std::uint32_t score) noexcept
    : score_{score} {
}

std::uint32_t allergy_test::mask_for(allergen item) noexcept {
    switch (item) {
        case allergen::eggs: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(0));
        }
        case allergen::peanuts: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(1));
        }
        case allergen::shellfish: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(2));
        }
        case allergen::strawberries: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(3));
        }
        case allergen::tomatoes: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(4));
        }
        case allergen::chocolate: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(5));
        }
        case allergen::pollen: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(6));
        }
        case allergen::cats: {
            return (static_cast<std::uint32_t>(1) << static_cast<std::uint32_t>(7));
        }
        default: {
            return static_cast<std::uint32_t>(0);
        }
    }
}

bool allergy_test::is_allergic_to(allergen item) const noexcept {
    const std::uint32_t mask = mask_for(item);
    return ((score_ & mask) != static_cast<std::uint32_t>(0));
}

std::unordered_set<allergen> allergy_test::get_allergies() const {
    std::unordered_set<allergen> result{};

    for (const allergen a : {
             allergen::eggs,
             allergen::peanuts,
             allergen::shellfish,
             allergen::strawberries,
             allergen::tomatoes,
             allergen::chocolate,
             allergen::pollen,
             allergen::cats}) {
        if (is_allergic_to(a)) {
            (void)result.emplace(a);
        }
    }

    return result;
}

}  // namespace allergies
