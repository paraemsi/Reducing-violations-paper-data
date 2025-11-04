#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <cstddef>
#include <unordered_set>
#include <string>
#include <functional>

namespace allergies {

enum class Allergen : std::uint8_t {
    eggs        = static_cast<std::uint8_t>(1u),
    peanuts     = static_cast<std::uint8_t>(2u),
    shellfish   = static_cast<std::uint8_t>(4u),
    strawberries= static_cast<std::uint8_t>(8u),
    tomatoes    = static_cast<std::uint8_t>(16u),
    chocolate   = static_cast<std::uint8_t>(32u),
    pollen      = static_cast<std::uint8_t>(64u),
    cats        = static_cast<std::uint8_t>(128u)
};

class Allergies {
public:
    explicit Allergies(std::uint32_t allergy_score) noexcept;

    [[nodiscard]] bool is_allergic_to(Allergen allergen) const noexcept;
    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const noexcept;
    [[nodiscard]] std::unordered_set<std::string> get_allergies() const;

private:
    std::uint32_t m_score;
};

    [[nodiscard]] Allergies allergy_test(std::uint32_t allergy_score) noexcept;

}  // namespace allergies

namespace std {
template <>
struct hash<allergies::Allergen> {
    std::size_t operator()(const allergies::Allergen& allergen) const noexcept
    {
        return static_cast<std::size_t>(allergen);
    }
};
}  // namespace std

#endif // ALLERGIES_H
