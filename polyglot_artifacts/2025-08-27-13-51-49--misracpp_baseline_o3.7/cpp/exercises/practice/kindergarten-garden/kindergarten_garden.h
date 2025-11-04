#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>

namespace kindergarten_garden {

enum class Plants { grass, clover, radishes, violets };

class garden {
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {});

    std::vector<Plants> plants_for(const std::string& student) const;

private:
    std::unordered_map<std::string, std::vector<Plants>> assignments;
    static const std::vector<std::string> default_students;
};

// Free helper function expected by the tests
std::array<Plants, 4> plants(const std::string& diagram,
                             const std::string& student,
                             const std::vector<std::string>& students = {});

}  // namespace kindergarten_garden
