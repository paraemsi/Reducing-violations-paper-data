#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace kindergarten_garden {

enum class plant
{
    grass,
    clover,
    radishes,
    violets
};

/*  Alias required by the unit-tests.
 *  Enumerator names remain identical, therefore aliasing is sufficient
 *  and does not duplicate the underlying enumeration.
 */
using Plants = plant;

class garden
{
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students_in = {});

    [[nodiscard]] std::vector<plant> plants(const std::string& student) const;

private:
    static constexpr std::array<const char*, 12U> default_students_{
        "Alice",
        "Bob",
        "Charlie",
        "David",
        "Eve",
        "Fred",
        "Ginny",
        "Harriet",
        "Ileana",
        "Joseph",
        "Kincaid",
        "Larry"
    };

    std::unordered_map<std::string, std::vector<plant>> lookup_{};

    static plant char_to_plant(char c);
};

/*------------------------------------------------------------
 * Convenience free-function expected by the test-suite.
 * It builds a garden from the supplied diagram (and optional
 * student list) and returns the 4 plants belonging to the
 * requested student.
 *----------------------------------------------------------*/
[[nodiscard]] std::array<Plants, 4U> plants(const std::string& diagram,
                                            const std::string& student,
                                            const std::vector<std::string>& students_in = {});

}  // namespace kindergarten_garden
