#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace allergies {

using allergy_score_t = std::uint16_t;

class Allergies
{
public:
    explicit Allergies(allergy_score_t score);

    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const;

    [[nodiscard]] std::unordered_set<std::string> get_allergies() const;

private:
    allergy_score_t m_score;
};

// Factory function for test compatibility
inline Allergies allergy_test(allergy_score_t score)
{
    return Allergies(score);
}

}  // namespace allergies

#endif // ALLERGIES_H
