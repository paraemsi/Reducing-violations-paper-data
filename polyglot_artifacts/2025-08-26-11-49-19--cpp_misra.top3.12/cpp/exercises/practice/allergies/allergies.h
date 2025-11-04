#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace allergies {

typedef std::uint16_t score_type;

class allergy_test
{
public:
    explicit allergy_test(score_type score_in);

    bool is_allergic_to(std::string const& allergen) const;

    std::unordered_set<std::string> get_allergies(void) const;

private:
    score_type score;
};

}  // namespace allergies

#endif // ALLERGIES_H
