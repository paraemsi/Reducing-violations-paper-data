#pragma once

#include <string>
#include <vector>
#include <array>

namespace kindergarten_garden {

enum class plant { clover, grass, radishes, violets };
using Plants = plant;

class garden {
public:
    explicit garden(const std::string& diagram);
    garden(const std::string& diagram, const std::vector<std::string>& students);

    std::vector<plant> plants(const std::string& student) const;

    // Named accessors for convenience
    std::vector<plant> alice() const;
    std::vector<plant> bob() const;
    std::vector<plant> charlie() const;
    std::vector<plant> david() const;
    std::vector<plant> eve() const;
    std::vector<plant> fred() const;
    std::vector<plant> ginny() const;
    std::vector<plant> harriet() const;
    std::vector<plant> ileana() const;
    std::vector<plant> joseph() const;
    std::vector<plant> kincaid() const;
    std::vector<plant> larry() const;

private:
    std::string row1_;
    std::string row2_;
    std::vector<std::string> students_;

    static plant from_char(char c);
};

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
