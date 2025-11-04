#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <array>
#include <stdexcept>

namespace kindergarten_garden {

enum class Plants {
    grass,
    clover,
    radishes,
    violets
};

class garden {
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    const std::array<Plants, 4>& plants(const std::string& student) const;

private:
    static Plants char_to_plant(char c);
    static const std::vector<std::string> default_students;

    std::unordered_map<std::string, std::array<Plants, 4>> assignments_;
};

// Convenience free-function API expected by the tests
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student);

}  // namespace kindergarten_garden
