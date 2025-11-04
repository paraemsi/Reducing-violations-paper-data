#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <type_traits>
#include <unordered_set>

namespace allergies {

/* Enumeration of the supported allergens and their bit-flag values */
enum class allergen : std::uint32_t
{
    eggs         = 1u,
    peanuts      = 2u,
    shellfish    = 4u,
    strawberries = 8u,
    tomatoes     = 16u,
    chocolate    = 32u,
    pollen       = 64u,
    cats         = 128u
};

/* Class representing the allergy test result for a single person */
class allergy_test
{
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen a) const noexcept;
    [[nodiscard]] std::unordered_set<allergen> get_allergies() const noexcept;

private:
    std::uint32_t m_score;   /* raw allergy score returned by the test */
};

}  // namespace allergies

namespace std {
/* hash specialisation enabling use of allergies::allergen in unordered containers */
template <>
struct hash<allergies::allergen>
{
    std::size_t operator()(const allergies::allergen& a) const noexcept
    {
        return std::hash<std::uint32_t>{}(static_cast<std::uint32_t>(a));
    }
};
} // namespace std

#endif // ALLERGIES_H
