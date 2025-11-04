#include "diamond.h"

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace diamond {

/*=====================================================================*/
/*  INTERNAL IMPLEMENTATION DETAILS                                    */
/*=====================================================================*/

/**
 * @brief Generate the vector of rows comprising the diamond.
 *
 * The function validates the supplied letter and constructs each row
 * strictly following the diamond-kata rules.  It is kept file-local
 * (static) to avoid polluting the public namespace.
 */
static auto generateRows(char letter) -> std::vector<std::string>
{
    using std::char_traits;
    using std::int32_t;
    using std::string;
    using std::uint64_t;
    using std::vector;
    using char_int_type = typename std::char_traits<char>::int_type;

    const int32_t baseCode =
        static_cast<int32_t>(char_traits<char>::to_int_type('A'));
    const int32_t targetCode =
        static_cast<int32_t>(char_traits<char>::to_int_type(letter));

    if ((targetCode < baseCode) || (targetCode > (baseCode + static_cast<int32_t>(25)))) {
        throw std::invalid_argument("Letter must be an uppercase character between 'A' and 'Z'");
    }

    const int32_t size = (targetCode - baseCode) + static_cast<int32_t>(1);

    vector<string> rowsVec;
    rowsVec.reserve(static_cast<uint64_t>(size) * static_cast<uint64_t>(2) -
                    static_cast<uint64_t>(1));

    for (int32_t i = static_cast<int32_t>(0); i < size; ++i) {
        const char currentChar = char_traits<char>::to_char_type(
            static_cast<char_int_type>(baseCode + i));

        const int32_t leading = (size - i) - static_cast<int32_t>(1);
        const int32_t internal = (i == static_cast<int32_t>(0)) ? static_cast<int32_t>(0)
                              : ((i * static_cast<int32_t>(2)) - static_cast<int32_t>(1));

        string row(static_cast<uint64_t>(leading), ' ');
        row += currentChar;
        if (i != static_cast<int32_t>(0)) {
            row += string(static_cast<uint64_t>(internal), ' ');
            row += currentChar;
        }
        row += string(static_cast<uint64_t>(leading), ' ');
        rowsVec.push_back(row);
    }

    for (int32_t i = size - static_cast<int32_t>(2); i >= static_cast<int32_t>(0); --i) {
        rowsVec.push_back(rowsVec[static_cast<uint64_t>(i)]);
    }

    return rowsVec;
}

/**
 * @brief Public helper returning the diamond as a vector of strings.
 */
auto rows(char letter) -> std::vector<std::string>
{
    return generateRows(letter);
}

auto buildDiamond(char letter) -> std::string
{
    const auto lines = generateRows(letter);

    std::string result;
    const std::size_t count = lines.size();
    for (std::size_t idx = static_cast<std::size_t>(0U); idx < count; ++idx) {
        result += lines[idx];
        if ((idx + static_cast<std::size_t>(1U)) < count) {
            result += '\n';
        }
    }
    return result;
}

}  // namespace diamond
