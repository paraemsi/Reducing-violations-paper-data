#include "allergies.h"

namespace allergies {

namespace {
constexpr std::uint32_t bit_mask_for(allergy a) noexcept {
    switch (a) {
        case allergy::eggs: {
            return (static_cast<std::uint32_t>(1) << 0);
        }
        case allergy::peanuts: {
            return (static_cast<std::uint32_t>(1) << 1);
        }
        case allergy::shellfish: {
            return (static_cast<std::uint32_t>(1) << 2);
        }
        case allergy::strawberries: {
            return (static_cast<std::uint32_t>(1) << 3);
        }
        case allergy::tomatoes: {
            return (static_cast<std::uint32_t>(1) << 4);
        }
        case allergy::chocolate: {
            return (static_cast<std::uint32_t>(1) << 5);
        }
        case allergy::pollen: {
            return (static_cast<std::uint32_t>(1) << 6);
        }
        case allergy::cats: {
            return (static_cast<std::uint32_t>(1) << 7);
        }
        default: {
            return static_cast<std::uint32_t>(0);
        }
    }
}
}  // unnamed namespace

allergy_test::allergy_test(std::uint32_t score) noexcept
    : m_score(score) {
}

bool allergy_test::is_allergic_to(allergy item) const noexcept {
    const std::uint32_t relevant = (m_score & static_cast<std::uint32_t>(255));
    const std::uint32_t mask = bit_mask_for(item);
    return ((relevant & mask) != static_cast<std::uint32_t>(0));
}

allergy_set allergy_test::get_allergies() const {
    const std::uint32_t relevant = (m_score & static_cast<std::uint32_t>(255));
    allergy_set result{};

    if ((relevant & bit_mask_for(allergy::eggs)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::eggs);
    }
    if ((relevant & bit_mask_for(allergy::peanuts)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::peanuts);
    }
    if ((relevant & bit_mask_for(allergy::shellfish)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::shellfish);
    }
    if ((relevant & bit_mask_for(allergy::strawberries)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::strawberries);
    }
    if ((relevant & bit_mask_for(allergy::tomatoes)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::tomatoes);
    }
    if ((relevant & bit_mask_for(allergy::chocolate)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::chocolate);
    }
    if ((relevant & bit_mask_for(allergy::pollen)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::pollen);
    }
    if ((relevant & bit_mask_for(allergy::cats)) != static_cast<std::uint32_t>(0)) {
        (void)result.emplace(allergy::cats);
    }

    return result;
}

}  // namespace allergies
