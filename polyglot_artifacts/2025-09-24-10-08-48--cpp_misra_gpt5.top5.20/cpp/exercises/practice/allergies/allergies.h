#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstddef>
#include <cstdint>
#include <unordered_set>

namespace allergies {

enum class allergen : std::uint16_t {
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};

struct AllergenHash {
    constexpr std::size_t operator()(allergen a) const noexcept
    {
        return static_cast<std::size_t>(static_cast<std::uint16_t>(a));
    }
};

using allergen_set = std::unordered_set<allergen, AllergenHash>;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;
    bool is_allergic_to(allergen item) const noexcept;
    allergen_set get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

#endif // ALLERGIES_H
