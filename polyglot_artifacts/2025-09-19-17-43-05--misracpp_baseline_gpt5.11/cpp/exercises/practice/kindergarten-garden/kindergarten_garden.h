#pragma once

#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class Plants { clover, grass, radishes, violets };

class garden {
public:
    explicit garden(const std::string& diagram,
                    std::vector<std::string> students = {
                        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
                        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"});

    std::vector<Plants> plants(const std::string& student) const;

private:
    std::string row1_;
    std::string row2_;
    std::vector<std::string> students_;

    static Plants char_to_plant(char c);
    static void trim_carriage_return(std::string& s);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
