#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <array>
#include <unordered_map>
#include <vector>

namespace kindergarten_garden {

/* Enumeration of the possible plants in the garden. */
enum class plant : std::uint8_t {
    grass,
    clover,
    radishes,
    violets
};

/* Alias required by the test-suite – refers to the same enumeration. */
using Plants = plant;

/* Class that parses the garden diagram and answers plant queries. */
class garden {
public:
    /* Construct from a diagram and (optionally) a custom-ordered list of students. */
    explicit garden(std::string_view diagram,
                    std::vector<std::string> students = {});

    /* Return the four plants belonging to the requested student. */
    [[nodiscard]] std::vector<plant> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::vector<plant>> student_plants_{};

    static plant char_to_plant(char c);
    static std::vector<std::string> default_students();
};

/* Free helper that constructs a garden and returns the requested student's plants. */
[[nodiscard]] std::array<Plants, static_cast<std::size_t>(4U)>
plants(std::string_view diagram,
       std::string_view student,
       std::vector<std::string> students = {});

}  // namespace kindergarten_garden
