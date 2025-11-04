#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <unordered_set>

namespace allergies {

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

struct allergen_hash {
    auto operator()(const allergen &a) const noexcept -> std::size_t
    {
        return static_cast<std::size_t>(a);
    }
};

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] auto is_allergic_to(allergen item) const noexcept -> bool;
    [[nodiscard]] auto get_allergies() const -> std::unordered_set<allergen, allergen_hash>;

private:
    std::uint32_t m_score;
};

}  // namespace allergies


#endif // ALLERGIES_H
