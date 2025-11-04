#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <vector>

namespace allergies {

using score_type = std::uint32_t;

// Enumeration of all supported allergens
enum class allergen : score_type
{
    eggs = 1U,
    peanuts = 2U,
    shellfish = 4U,
    strawberries = 8U,
    tomatoes = 16U,
    chocolate = 32U,
    pollen = 64U,
    cats = 128U
};

// Class representing the result of an allergy test
class allergy_test
{
public:
    // Construct with the raw allergy score
    explicit allergy_test(score_type score) noexcept;

    // Returns true if the person is allergic to the given allergen name
    [[nodiscard]] bool is_allergic_to(const std::string& item) const;

    // Returns a list containing all allergens the person is allergic to
    [[nodiscard]] std::vector<std::string> get_allergies() const;

private:
    score_type m_score; // stored allergy score
};

}  // namespace allergies

#endif // ALLERGIES_H
