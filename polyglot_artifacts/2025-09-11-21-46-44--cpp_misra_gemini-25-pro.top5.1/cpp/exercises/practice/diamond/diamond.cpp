#include "diamond.h"

#include <cstdint>
#include <string>
#include <vector>

namespace diamond {

// Helper function to satisfy MISRA C++ rule about not using numeric value of a character.
static char get_char_from_index(std::uint64_t index)
{
    // A direct lookup like "ABC..."[index] could be flagged.
    // This switch is unambiguous.
    switch (index)
    {
        case 0: { return 'A'; }
        case 1: { return 'B'; }
        case 2: { return 'C'; }
        case 3: { return 'D'; }
        case 4: { return 'E'; }
        case 5: { return 'F'; }
        case 6: { return 'G'; }
        case 7: { return 'H'; }
        case 8: { return 'I'; }
        case 9: { return 'J'; }
        case 10: { return 'K'; }
        case 11: { return 'L'; }
        case 12: { return 'M'; }
        case 13: { return 'N'; }
        case 14: { return 'O'; }
        case 15: { return 'P'; }
        case 16: { return 'Q'; }
        case 17: { return 'R'; }
        case 18: { return 'S'; }
        case 19: { return 'T'; }
        case 20: { return 'U'; }
        case 21: { return 'V'; }
        case 22: { return 'W'; }
        case 23: { return 'X'; }
        case 24: { return 'Y'; }
        case 25: { return 'Z'; }
        default: { return ' '; } // Should not happen for valid letters
    }
}

static std::uint64_t get_index_from_int(LetterInt letter)
{
    // Using integer literals to avoid using the numeric value of a character.
    switch (letter)
    {
        case 65: { return 0U; }  // 'A'
        case 66: { return 1U; }  // 'B'
        case 67: { return 2U; }  // 'C'
        case 68: { return 3U; }  // 'D'
        case 69: { return 4U; }  // 'E'
        case 70: { return 5U; }  // 'F'
        case 71: { return 6U; }  // 'G'
        case 72: { return 7U; }  // 'H'
        case 73: { return 8U; }  // 'I'
        case 74: { return 9U; }  // 'J'
        case 75: { return 10U; } // 'K'
        case 76: { return 11U; } // 'L'
        case 77: { return 12U; } // 'M'
        case 78: { return 13U; } // 'N'
        case 79: { return 14U; } // 'O'
        case 80: { return 15U; } // 'P'
        case 81: { return 16U; } // 'Q'
        case 82: { return 17U; } // 'R'
        case 83: { return 18U; } // 'S'
        case 84: { return 19U; } // 'T'
        case 85: { return 20U; } // 'U'
        case 86: { return 21U; } // 'V'
        case 87: { return 22U; } // 'W'
        case 88: { return 23U; } // 'X'
        case 89: { return 24U; } // 'Y'
        case 90: { return 25U; } // 'Z'
        default: { return 26U; } // sentinel for invalid
    }
}

std::vector<std::string> rows(LetterInt letter) {
    const std::uint64_t max_index = get_index_from_int(letter);

    if (max_index > 25U)
    {
        return {};
    }

    const std::uint64_t two = 2U;
    const std::uint64_t one = 1U;
    const std::uint64_t max_index_times_2 = (two * max_index);
    const std::uint64_t dimension = (max_index_times_2 + one);

    std::vector<std::string> result;
    result.reserve(dimension);

    // Top half including middle
    for (std::uint64_t i = 0U; i <= max_index; ++i) {
        const std::uint64_t outer_spaces = (max_index - i);
        std::string row;
        row.reserve(dimension);
        row.append(outer_spaces, ' ');
        row += get_char_from_index(i);

        if (i > 0U) {
            const std::uint64_t i_times_2 = (two * i);
            const std::uint64_t inner_spaces = (i_times_2 - one);
            row.append(inner_spaces, ' ');
            row += get_char_from_index(i);
        }
        row.append(outer_spaces, ' ');
        result.push_back(row);
    }

    // Bottom half
    for (std::uint64_t i = max_index; i > 0U; --i) {
        result.push_back(result[(i - one)]);
    }

    return result;
}

}  // namespace diamond
