#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <unordered_set>
#include <functional>
#include <cstddef>

namespace allergies {

enum class allergy : std::uint16_t {
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};

struct allergy_hash {
    std::size_t operator()(allergy a) const noexcept
    {
        return std::hash<std::uint16_t>{}(static_cast<std::uint16_t>(a));
    }
};

using allergy_set = std::unordered_set<allergy, allergy_hash>;

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score) noexcept;

    bool is_allergic_to(allergy item) const noexcept;

    allergy_set get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies


#endif // ALLERGIES_H
