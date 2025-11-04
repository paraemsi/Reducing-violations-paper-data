#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <cstddef>

namespace allergies {

enum class allergen : std::uint16_t {
    eggs = 1,
    peanuts = 2,
    shellfish = 4,
    strawberries = 8,
    tomatoes = 16,
    chocolate = 32,
    pollen = 64,
    cats = 128
};

struct allergen_hash final {
    auto operator()(allergen a) const noexcept -> std::size_t
    {
        return static_cast<std::size_t>(static_cast<std::uint16_t>(a));
    }
};

using allergen_set = std::unordered_set<allergen, allergen_hash>;

class allergy_test final {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    auto is_allergic_to(allergen item) const noexcept -> bool;
    auto get_allergies() const -> allergen_set;

private:
    std::uint32_t m_score;
};

}  // namespace allergies


#endif // ALLERGIES_H
