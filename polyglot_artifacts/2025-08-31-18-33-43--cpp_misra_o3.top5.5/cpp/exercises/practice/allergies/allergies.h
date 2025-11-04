#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <functional>
#include <type_traits>

namespace allergies {

// Fixed-width underlying type obeys MISRA: use std::uint8_t
enum class allergen : std::uint8_t {
    eggs         = 1u,
    peanuts      = 2u,
    shellfish    = 4u,
    strawberries = 8u,
    tomatoes     = 16u,
    chocolate    = 32u,
    pollen       = 64u,
    cats         = 128u
};

} // namespace allergies

// Provide a hash specialization so that allergen can be used in std::unordered_set
namespace std {
template<>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& key) const noexcept
    {
        using underlying_t = std::underlying_type_t<allergies::allergen>;
        return std::hash<underlying_t>()(static_cast<underlying_t>(key));
    }
};
} // namespace std

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score_in) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;

    [[nodiscard]] std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score;
};

}  // namespace allergies

#endif // ALLERGIES_H
