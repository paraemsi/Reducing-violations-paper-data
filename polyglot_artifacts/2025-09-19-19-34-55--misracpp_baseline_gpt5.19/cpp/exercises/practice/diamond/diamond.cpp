#include "diamond.h"
#include <cctype>
#include <utility>

namespace diamond {

namespace {
inline bool is_alpha_letter(char ch) {
    unsigned char uch = static_cast<unsigned char>(ch);
    return (uch >= 'A' && uch <= 'Z') || (uch >= 'a' && uch <= 'z');
}
}  // namespace

static std::vector<std::string> make_diamond(char letter) {
    if (!is_alpha_letter(letter)) {
        return {};
    }
    char L = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
    const std::size_t n = static_cast<std::size_t>(L - 'A' + 1);
    const std::size_t size = 2 * n - 1;
    const std::size_t center = n - 1;

    std::vector<std::string> rows;
    rows.reserve(size);

    for (std::size_t r = 0; r < size; ++r) {
        std::size_t k = (r <= center) ? r : (size - 1 - r);
        char ch = static_cast<char>('A' + k);

        std::string line(size, ' ');
        std::size_t left = center - k;
        std::size_t right = center + k;
        line[left] = ch;
        line[right] = ch;

        rows.push_back(std::move(line));
    }

    return rows;
}

std::vector<std::string> rows(char letter) {
    return make_diamond(letter);
}

std::vector<std::string> rows_for(char letter) {
    return rows(letter);
}

std::string to_string(char letter) {
    const auto lines = rows(letter);
    std::string out;
    if (lines.empty()) return out;
    std::size_t total = 0;
    for (const auto& s : lines) total += s.size();
    if (lines.size() > 1) total += lines.size() - 1;
    out.reserve(total);
    for (std::size_t i = 0; i < lines.size(); ++i) {
        if (i > 0) out += '\n';
        out += lines[i];
    }
    return out;
}

}  // namespace diamond
