#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_set>

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

class allergy_test {
public:
    explicit allergy_test(std::uint32_t score);

    bool is_allergic_to(const std::string& allergen_name) const;

    std::unordered_set<std::string> get_allergies() const;

private:
    std::uint32_t score_;
};

}  // namespace allergies

#endif // ALLERGIES_H
