#pragma once

#include <string>
#include <vector>
#include <map>

namespace kindergarten_garden {

enum class Plant {
    violets,
    radishes,
    clover,
    grass
};

class kindergarten_garden {
public:
    kindergarten_garden(const std::string& diagram,
                        const std::vector<std::string>& students);

    std::vector<Plant> plants(const std::string& student) const;

    static const std::vector<std::string> default_students;

private:
    std::map<std::string, std::vector<Plant>> student_plants_;
};

}  // namespace kindergarten_garden
