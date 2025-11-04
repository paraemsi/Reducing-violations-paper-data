#if !defined(ALLERGIES_H)
#define ALLERGIES_H

#include <string>
#include <unordered_set>
#include <vector>
#include <cstdint>

namespace allergies {

class allergy_test
{
public:
    explicit allergy_test(std::uint32_t score);

    bool is_allergic_to(const std::string& item) const;

    std::vector<std::string> get_allergies() const;

private:
    std::uint32_t score_;
    std::unordered_set<std::string> allergy_set_;

    void populate_allergies();
};

}  // namespace allergies

#endif // ALLERGIES_H
