#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_set>

namespace allergies {

 // Class modelling a person's allergies based on an encoded score
class allergy_test final {
public:
    // Construct from numeric allergy score
    explicit allergy_test(std::uint32_t score_in) noexcept;

    // Return true if the person is allergic to the supplied item
    [[nodiscard]] bool is_allergic_to(const std::string& item) const noexcept;

    // Return the full set of allergens the person is allergic to
    [[nodiscard]] std::unordered_set<std::string> get_allergies() const noexcept;

private:
    std::uint32_t score_;   // encoded allergy score
};

}  // namespace allergies

#endif // ALLERGIES_H
