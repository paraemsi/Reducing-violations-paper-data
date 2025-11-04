#include "crypto_square.h"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <string>
#include <vector>

namespace crypto_square {

using std::size_t;
using std::string;
using std::vector;

cipher::cipher(const std::string& text) : input_(text) {}

string cipher::normalize_plain_text() const {
    string out;
    out.reserve(input_.size());
    for (unsigned char ch : input_) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

size_t cipher::cols_count(const std::string& normalized) const {
    const size_t n = normalized.size();
    if (n == 0) return 0;
    const double root = std::sqrt(static_cast<double>(n));
    const size_t c = static_cast<size_t>(std::ceil(root));
    return c;
}

size_t cipher::rows_count(const std::string& normalized) const {
    const size_t n = normalized.size();
    if (n == 0) return 0;
    const size_t c = cols_count(normalized);
    size_t r = static_cast<size_t>(std::floor(std::sqrt(static_cast<double>(n))));
    if (r * c < n) {
        r = c;
    }
    return r;
}

vector<string> cipher::plain_text_segments() const {
    const string norm = normalize_plain_text();
    const size_t c = cols_count(norm);
    vector<string> segs;
    if (c == 0) return segs;
    segs.reserve((norm.size() + c - 1) / c);
    for (size_t i = 0; i < norm.size(); i += c) {
        segs.emplace_back(norm.substr(i, std::min(c, norm.size() - i)));
    }
    return segs;
}

string cipher::cipher_text() const {
    const vector<string> segs = plain_text_segments();
    if (segs.empty()) return {};
    const size_t c = segs.front().size(); // number of columns
    string out;
    out.reserve(normalize_plain_text().size());
    for (size_t col = 0; col < c; ++col) {
        for (const auto& row : segs) {
            if (col < row.size()) {
                out.push_back(row[col]);
            }
        }
    }
    return out;
}

string cipher::normalized_cipher_text() const {
    const vector<string> segs = plain_text_segments();
    if (segs.empty()) return {};
    const size_t r = segs.size();
    const size_t c = segs.front().size();
    string out;
    // Reserve: cipher text size + spaces between chunks + padding spaces
    const size_t n = normalize_plain_text().size();
    out.reserve(n + (c ? c - 1 : 0) + (c * r > n ? (c * r - n) : 0));
    for (size_t col = 0; col < c; ++col) {
        // build one chunk of length r
        for (size_t row = 0; row < r; ++row) {
            if (col < segs[row].size()) {
                out.push_back(segs[row][col]);
            } else {
                out.push_back(' ');
            }
        }
        if (col + 1 < c) {
            out.push_back(' ');
        }
    }
    return out;
}

}  // namespace crypto_square
