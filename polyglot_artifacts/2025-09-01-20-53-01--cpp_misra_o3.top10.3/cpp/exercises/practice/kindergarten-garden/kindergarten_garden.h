#pragma once

#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstdint>

namespace kindergarten_garden {

 // Strongly-typed representation of each plant
enum class Plants : std::uint8_t {
    violets,
    radishes,
    clover,
    grass
};

class garden final {
public:
    // Provide a reference to the default student roster
    static const std::vector<std::string>& default_student_list();

    // Create a garden from a diagram using the default student roster
    explicit garden(const std::string& diagram);

    // Create a garden from a diagram with an explicit (possibly empty) student list
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students);

    // Return the four plants assigned to a student
    [[nodiscard]] std::array<Plants, 4> plants(const std::string& student) const;

private:
    std::unordered_map<std::string, std::array<Plants, 4>> assignments_;
};

[[nodiscard]] std::array<Plants, 4> plants(const std::string& diagram,
                                           const std::string& student);

[[nodiscard]] std::array<Plants, 4> plants(const std::string& diagram,
                                           const std::vector<std::string>& students,
                                           const std::string& student);

}  // namespace kindergarten_garden
