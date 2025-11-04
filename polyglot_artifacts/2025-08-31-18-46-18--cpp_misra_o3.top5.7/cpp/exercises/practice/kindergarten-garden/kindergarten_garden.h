#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace kindergarten_garden {

enum class Plants {
    clover,
    grass,
    radishes,
    violets
};


/*  Convenience free function required by the unit-tests.
 *  It constructs an ephemeral garden from the given diagram
 *  and forwards the request for the specified student.
 */
[[nodiscard]] std::array<Plants, 4U> plants(const std::string& diagram,
                                            const std::string& student);

class garden {
public:
    [[nodiscard]] static std::vector<std::string> default_students();

    explicit garden(const std::string& diagram,
                    std::vector<std::string> students_in = default_students());

    [[nodiscard]] std::vector<Plants> plants(const std::string& student) const;

private:
    [[maybe_unused]] static constexpr std::array<char, 4U> plant_codes { 'C', 'G', 'R', 'V' };

    std::array<std::string, 2U> m_rows {};                      // two rows of cups
    std::vector<std::string> m_students {};                     // sorted list of student names
    std::unordered_map<std::string, std::size_t> m_index_map {}; // quick lookup table

    [[nodiscard]] static Plants code_to_plant(char code);
};

}  // namespace kindergarten_garden
