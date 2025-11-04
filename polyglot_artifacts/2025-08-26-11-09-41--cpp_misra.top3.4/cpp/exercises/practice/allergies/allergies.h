#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace allergies {

using allergy_score_t = std::uint16_t;

class allergy_test
{
public:
    explicit allergy_test(allergy_score_t score_in);

    [[nodiscard]] bool is_allergic_to(const std::string& allergen) const;
    [[nodiscard]] std::unordered_set<std::string> get_allergies() const;

private:
    allergy_score_t score;
};

}  // namespace allergies

#endif // ALLERGIES_H
