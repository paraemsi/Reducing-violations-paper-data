#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

namespace allergies {

typedef std::uint16_t allergy_score_t;

class allergy_test
{
public:
    explicit allergy_test(allergy_score_t score_in);

    bool is_allergic_to(std::string const& allergen) const;
    std::vector<std::string> get_allergies(void) const;

private:
    allergy_score_t score;
};

}  // namespace allergies

#endif // ALLERGIES_H
