#pragma once

#include <string>
#include <vector>
#include <map>
#include <array>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

extern const std::vector<std::string> default_students;

class garden {
public:
    explicit garden(std::string diagram,
                    std::vector<std::string> students = default_students);

    const std::vector<Plants>& plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants>> garden_map_;
    static Plants char_to_plant(char c);
};

// Convenience free function expected by the tests.
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             std::vector<std::string> students = default_students);

}  // namespace kindergarten_garden
