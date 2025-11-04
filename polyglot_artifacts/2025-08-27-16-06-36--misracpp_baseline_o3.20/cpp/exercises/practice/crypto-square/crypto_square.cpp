#include "crypto_square.h"

#include <cctype>
#include <cmath>

namespace crypto_square {

namespace {

std::string normalize(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (unsigned char ch : text) {
        if (std::isalnum(ch)) {
            out.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    return out;
}

} // namespace

cipher::cipher(std::string text)
    : raw_(std::move(text))
{
    normalized_ = normalize(raw_);
    compute_rectangle();
}

void cipher::compute_rectangle() {
    const std::size_t len = normalized_.size();
    if (len == 0) {
        rows_ = cols_ = 0;
        return;
    }

    const double root = std::sqrt(static_cast<double>(len));
    rows_ = static_cast<std::size_t>(std::floor(root));
    cols_ = static_cast<std::size_t>(std::ceil(root));
    if (rows_ * cols_ < len) {
        ++rows_;
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    std::vector<std::string> segments;
    if (normalized_.empty()) {
        return segments;
    }

    for (std::size_t i = 0; i < normalized_.size(); i += cols_) {
        segments.emplace_back(normalized_.substr(i, cols_));
    }
    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized_.empty()) {
        return {};
    }

    std::string out;
    out.reserve(normalized_.size());

    for (std::size_t c = 0; c < cols_; ++c) {
        for (std::size_t r = 0; r < rows_; ++r) {
            const std::size_t idx = r * cols_ + c;
            if (idx < normalized_.size()) {
                out.push_back(normalized_[idx]);
            }
        }
    }
    return out;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_.empty()) {
        return {};
    }

    std::string out;
    for (std::size_t c = 0; c < cols_; ++c) {
        if (c != 0) {
            out.push_back(' ');
        }

        for (std::size_t r = 0; r < rows_; ++r) {
            const std::size_t idx = r * cols_ + c;
            if (idx < normalized_.size()) {
                out.push_back(normalized_[idx]);
            } else {
                out.push_back(' ');
            }
        }
    }
    return out;
}

}  // namespace crypto_square
