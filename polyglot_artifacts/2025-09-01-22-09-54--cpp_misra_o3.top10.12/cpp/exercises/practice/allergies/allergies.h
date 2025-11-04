#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <cstdint>
#include <string>
#include <unordered_set>
#include <vector>

namespace allergies {

/*  Class that represents a person's allergy profile generated from a score. */
class allergy_test final {
public:
    /*  Construct from an allergy score. */
    explicit allergy_test(std::uint32_t score) noexcept;

    /*  Query if the person is allergic to the supplied allergen name. */
    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const;

    /*  Obtain the complete list of allergens the person is allergic to. */
    [[nodiscard]] std::vector<std::string> get_allergies() const;

private:
    std::uint32_t m_score;                               /* original score */
    std::unordered_set<std::string> m_allergens_present; /* set populated from m_score */
};

}  // namespace allergies

#endif // ALLERGIES_H
