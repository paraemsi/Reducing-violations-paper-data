#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace kindergarten_garden {

/* Enumeration of the possible plants in the garden */
enum class Plant : std::uint8_t {
    grass,
    clover,
    radishes,
    violets
};

/* Alias demanded by the test suite – same enumeration type, different name */
using Plants = Plant;

class Garden {
public:
    /* Construct with the default (alphabetical) list of students */
    explicit Garden(const std::string& diagram);

    /* Construct with a caller-supplied, already-ordered list of students */
    Garden(const std::string& diagram, const std::vector<std::string>& students);

    /* Return the four plants belonging to the given student */
    [[nodiscard]] std::vector<Plant> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::vector<Plant>> student_plants_;

    static Plant char_to_plant(char code);

    static void assign_plants(const std::string& row1,
                              const std::string& row2,
                              const std::vector<std::string>& students,
                              std::unordered_map<std::string, std::vector<Plant>>& out_map);
};  // class Garden

/* Free convenience helper expected by the tests */
[[nodiscard]] std::array<Plants, 4U> plants(const std::string& diagram,
                                            const std::string& student);

}  // namespace kindergarten_garden
