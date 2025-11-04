#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <unordered_set>

namespace allergies {

enum class allergen {
    eggs,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats
};

}  // namespace allergies

/* hash specialization moved above to be visible before use */

namespace allergies {

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(allergen item) const noexcept;

    std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score_;

    static std::uint32_t mask_for(allergen item) noexcept;
};

}  // namespace allergies

namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept {
        using U = std::underlying_type<allergies::allergen>::type;
        return std::hash<U>{}(static_cast<U>(a));
    }
};
}  // namespace std

#endif // ALLERGIES_H
