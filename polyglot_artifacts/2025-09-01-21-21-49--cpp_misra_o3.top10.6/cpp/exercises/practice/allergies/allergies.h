#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <vector>
#include <unordered_set>
#include <string>
#include <functional>

namespace allergies {

/*  Enumeration of known allergens with fixed-width underlying type
 *  Values correspond to the bit positions supplied in the exercise
 */
enum class allergen : std::uint8_t {
    eggs        = 1U,
    peanuts     = 2U,
    shellfish   = 4U,
    strawberries= 8U,
    tomatoes    = 16U,
    chocolate   = 32U,
    pollen      = 64U,
    cats        = 128U
};

/*  Hash specialization for enum class allergen so it can be stored in
 *  unordered associative containers. Adding this specialization inside
 *  namespace std is permitted for user-defined types.
 */
}  // namespace allergies

namespace std {
template <> struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen a) const noexcept
    {
        /*  Widening to size_t, same unsigned integral category – MISRA compliant */
        return static_cast<std::size_t>(a);
    }
};
}  // namespace std

namespace allergies {

class allergy {
public:
    explicit allergy(std::uint32_t score_in) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;

    [[nodiscard]] std::vector<allergen> get_allergies() const noexcept;

private:
    std::uint32_t score_;
};

/*  Wrapper class expected by the unit tests. Internally delegates work
 *  to the previously-defined `allergy` implementation but exposes the
 *  string-based API and return types required by the tests.
 */
class allergy_test {
public:
    explicit allergy_test(std::uint32_t score_in) noexcept;

    [[nodiscard]] bool is_allergic_to(const std::string& item) const noexcept;

    [[nodiscard]] std::unordered_set<std::string> get_allergies() const noexcept;

private:
    allergy impl_;
};

}  // namespace allergies

#endif // ALLERGIES_H
