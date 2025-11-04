#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <functional>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint8_t {
    eggs,
    peanuts,
    shellfish,
    strawberries,
    tomatoes,
    chocolate,
    pollen,
    cats
};

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;

    [[nodiscard]] std::unordered_set<allergen> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

// Hash specialization for allergies::allergen to allow use in unordered_set on all supported standards
namespace std {
template <>
struct hash<allergies::allergen> {
    std::size_t operator()(const allergies::allergen& a) const noexcept
    {
        return (static_cast<std::size_t>(static_cast<std::uint8_t>(a)));
    }
};
}  // namespace std

#endif // ALLERGIES_H
