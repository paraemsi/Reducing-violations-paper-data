#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace allergies {

using allergy_score_t = std::uint16_t;

class allergy_test
{
public:
    explicit allergy_test(allergy_score_t score);

    bool is_allergic_to(const std::string& allergen) const;

    std::unordered_set<std::string> get_allergies(void) const;

private:
    allergy_score_t m_score;
};

}  // namespace allergies

#endif // ALLERGIES_H
