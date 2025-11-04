#pragma once

#include <map>
#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants { radishes, clover, grass, violets };

class garden {
public:
    explicit garden(const std::string& diagram,
                    const std::vector<std::string>& students = {
                        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid",
                        "Larry"});

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::map<std::string, std::vector<Plants>> assignments_;

    static Plants char_to_plant(char c);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
