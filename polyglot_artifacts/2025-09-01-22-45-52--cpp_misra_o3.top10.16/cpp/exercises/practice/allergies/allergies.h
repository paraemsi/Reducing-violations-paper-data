#ifndef ALLERGIES_H
#define ALLERGIES_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <unordered_set>
#include <array>

namespace allergies {

enum class allergen : std::uint32_t {
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};

struct allergen_hash
{
    std::size_t operator()(const allergen& a) const noexcept
    {
        return std::hash<std::uint32_t>{}(static_cast<std::uint32_t>(a));
    }
};

class allergy_test
{
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    [[nodiscard]] bool is_allergic_to(allergen item) const noexcept;
    [[nodiscard]] std::unordered_set<allergen, allergen_hash> get_allergies() const;

private:
    std::uint32_t m_score;
};

} // namespace allergies

#endif // ALLERGIES_H
