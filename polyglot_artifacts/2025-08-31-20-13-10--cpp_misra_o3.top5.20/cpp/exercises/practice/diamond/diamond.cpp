#include "diamond.h"

#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>

namespace diamond {

auto generate(char letter) -> std::string
{
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    std::string output{};

    const std::size_t index{alphabet.find(letter)};
    if(index == std::string::npos) {
        return output;
    }

    for(std::size_t row{0U}; row <= index; ++row) {
        const std::size_t leading{index - row};

        output.append(leading, ' ');
        output.push_back(alphabet[row]);

        if(row != 0U) {
            const std::size_t inner{((row * 2U) - 1U)};
            output.append(inner, ' ');
            output.push_back(alphabet[row]);
        }

        output.append(leading, ' ');
        output.push_back('\n');
    }

    for(std::size_t row{index}; row > 0U; --row) {
        const std::size_t current{row - 1U};
        const std::size_t leading{index - current};

        output.append(leading, ' ');
        output.push_back(alphabet[current]);

        if(current != 0U) {
            const std::size_t inner{((current * 2U) - 1U)};
            output.append(inner, ' ');
            output.push_back(alphabet[current]);
        }

        output.append(leading, ' ');
        output.push_back('\n');
    }

    return output;
}

auto rows(char letter) -> std::vector<std::string>
{
    std::vector<std::string> result{};
    const std::string diamond_str{generate(letter)};
    if(diamond_str.empty()) {
        return result;
    }

    std::string current_row{};
    for(char ch : diamond_str) {
        if(ch == '\n') {
            result.push_back(current_row);
            current_row.clear();
        } else {
            current_row.push_back(ch);
        }
    }
    return result;
}

}  // namespace diamond
