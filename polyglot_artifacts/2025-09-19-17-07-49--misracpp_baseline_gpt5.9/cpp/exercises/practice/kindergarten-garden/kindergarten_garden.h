#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };

enum class Plants { clover, grass, radishes, violets };

// Free function API expected by tests:
// Returns the four plants for the given student from the provided diagram.
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
    explicit garden(const std::string& diagram);
    std::vector<plant> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;

    static const std::vector<std::string>& default_students();
    static std::size_t student_index(const std::string& name);
    static plant from_char(char c);
};

}  // namespace kindergarten_garden
