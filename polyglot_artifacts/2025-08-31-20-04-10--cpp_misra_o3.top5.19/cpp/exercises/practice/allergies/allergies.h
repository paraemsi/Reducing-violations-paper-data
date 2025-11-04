#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <array>
#include <functional>   // for std::hash specialisation

namespace allergies {

/* MISRA C++ rule compliance:
 * - Use fixed-width integer types (<cstdint>)
 * - No plain ‘int’ or built-in unsigned/signed types
 */

/* Enumeration of possible allergens. The explicit underlying
 * type ensures the bit-values are the intended fixed width.
 */
enum class allergen : std::uint32_t {
    eggs         = 1u,
    peanuts      = 2u,
    shellfish    = 4u,
    strawberries = 8u,
    tomatoes     = 16u,
    chocolate    = 32u,
    pollen       = 64u,
    cats         = 128u
};

/* Provide a hash so allergen can be used in unordered containers
 * (required on toolchains that lack the generic enum hash).
 * NOTE: must come before the first appearance of unordered_set<allergen>.
 */
}  // namespace allergies

namespace std {
/* NOLINTNEXTLINE(cert-dcl58-cpp) – specialising std::hash for user type is allowed */
template<>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen a) const noexcept
    {
        return std::hash<std::uint32_t>{}(static_cast<std::uint32_t>(a));
    }
};
}  // namespace std

namespace allergies {

namespace allergies {

/* Class representing the result of an allergy test. */
class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;
    [[nodiscard]] std::unordered_set<allergen> get_allergies() const noexcept;

private:
    std::uint32_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
