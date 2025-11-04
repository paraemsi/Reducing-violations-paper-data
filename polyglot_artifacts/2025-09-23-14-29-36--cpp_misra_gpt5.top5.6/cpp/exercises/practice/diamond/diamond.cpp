#include "diamond.h"

#include <string>
#include <vector>

namespace diamond {

namespace {

// Upper- and lowercase alphabets used for lookup without relying on character arithmetic.
constexpr const char* kAlphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
constexpr const char* kAlphabetLower = "abcdefghijklmnopqrstuvwxyz";

// Find the alphabet index (0-based) of the given character.
// - Matches against uppercase first, then lowercase.
// - Sets ok to true on success; index is unspecified if ok is false.
std::size_t find_alpha_index(char ch, bool& ok) {
    ok = false;

    const std::string upper(kAlphabetUpper);
    const std::string lower(kAlphabetLower);

    const std::size_t pos_upper = upper.find(ch);
    if (pos_upper != std::string::npos) {
        ok = true;
        return pos_upper;
    }

    const std::size_t pos_lower = lower.find(ch);
    if (pos_lower != std::string::npos) {
        ok = true;
        return pos_lower;
    }

    return static_cast<std::size_t>(0);
}

char letter_at(std::size_t index) {
    // index must be within [0, 25]; caller ensures bounds.
    return kAlphabetUpper[index];
}

}  // namespace

std::vector<std::string> make_diamond(char letter) {
    bool ok = false;
    const std::size_t n = find_alpha_index(letter, ok);

    if (!ok) {
        return std::vector<std::string>();
    }

    const std::size_t size = ((static_cast<std::size_t>(2) * n) + static_cast<std::size_t>(1));

    std::vector<std::string> rows;
    rows.reserve(size);

    for (std::size_t i = static_cast<std::size_t>(0); i < size; ++i) {
        const std::size_t li = ((i <= n) ? i : ((static_cast<std::size_t>(2) * n) - i));
        const std::size_t outer = (n - li);

        std::string row;
        row.reserve(size);

        row.append(outer, ' ');

        const char c = letter_at(li);
        row.push_back(c);

        if (li != static_cast<std::size_t>(0)) {
            const std::size_t inner = ((static_cast<std::size_t>(2) * li) - static_cast<std::size_t>(1));
            row.append(inner, ' ');
            row.push_back(c);
        }

        row.append(outer, ' ');

        rows.push_back(row);
    }

    return rows;
}

std::vector<std::string> rows(char letter) {
    return make_diamond(letter);
}

}  // namespace diamond
