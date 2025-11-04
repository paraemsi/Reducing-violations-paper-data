#include "allergies.h"
#include <vector>

namespace allergies {

struct allergen_entry
{
    const char* name;
    std::uint32_t value;
};

static const std::vector<allergen_entry> allergen_table{
    {"eggs", 1U},
    {"peanuts", 2U},
    {"shellfish", 4U},
    {"strawberries", 8U},
    {"tomatoes", 16U},
    {"chocolate", 32U},
    {"pollen", 64U},
    {"cats", 128U}
};

allergy_test::allergy_test(std::uint32_t score) : score_{score}, allergy_set_{}
{
    populate_allergies();
}

bool allergy_test::is_allergic_to(const std::string& item) const
{
    return (allergy_set_.find(item) != allergy_set_.end());
}

std::vector<std::string> allergy_test::get_allergies() const
{
    std::vector<std::string> result{};
    result.reserve(allergen_table.size());

    for (const auto& entry : allergen_table)
    {
        if (((score_ & entry.value) != static_cast<std::uint32_t>(0U)))
        {
            result.emplace_back(entry.name);
        }
    }

    return result;
}

void allergy_test::populate_allergies()
{
    for (const auto& entry : allergen_table)
    {
        if (((score_ & entry.value) != static_cast<std::uint32_t>(0U)))
        {
            (void)allergy_set_.emplace(entry.name);
        }
    }
}

}  // namespace allergies
