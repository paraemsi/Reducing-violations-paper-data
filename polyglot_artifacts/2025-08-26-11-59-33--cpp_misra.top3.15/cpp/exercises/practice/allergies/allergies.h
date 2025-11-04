#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace allergies {

typedef std::uint16_t allergy_score_t;

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
