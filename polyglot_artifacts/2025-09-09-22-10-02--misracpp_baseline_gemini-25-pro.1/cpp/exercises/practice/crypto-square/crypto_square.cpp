#include "crypto_square.h"

#include <cctype>

namespace crypto_square {

cipher::cipher(const std::string& text) : col_count_{0}, row_count_{0} {
    for(const char c : text) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            normalized_text_ += std::tolower(static_cast<unsigned char>(c));
        }
    }
    if (!normalized_text_.empty()) {
        size_t len = normalized_text_.length();
        size_t c = 0;
        while (c * c < len) {
            c++;
        }
        col_count_ = c;
        if (c > 0) {
            row_count_ = (len + c - 1) / c;
        }
    }
}

std::string cipher::normalize_plain_text() const {
    return normalized_text_;
}

std::vector<std::string> cipher::plain_text_segments() const {
    if (normalized_text_.empty()) {
        return {};
    }

    std::vector<std::string> segments;
    for (size_t i = 0; i < normalized_text_.length(); i += col_count_) {
        segments.push_back(normalized_text_.substr(i, col_count_));
    }

    return segments;
}

std::string cipher::cipher_text() const {
    if (normalized_text_.empty()) {
        return "";
    }

    std::string result;
    result.reserve(normalized_text_.length());

    for (size_t j = 0; j < col_count_; ++j) {
        for (size_t i = 0; i < row_count_; ++i) {
            size_t index = i * col_count_ + j;
            if (index < normalized_text_.length()) {
                result += normalized_text_[index];
            }
        }
    }

    return result;
}

std::string cipher::normalized_cipher_text() const {
    if (normalized_text_.empty()) {
        return "";
    }

    std::string padded_text = normalized_text_;
    padded_text.resize(row_count_ * col_count_, ' ');

    std::vector<std::string> columns;
    for (size_t j = 0; j < col_count_; ++j) {
        std::string column;
        column.reserve(row_count_);
        for (size_t i = 0; i < row_count_; ++i) {
            column += padded_text[i * col_count_ + j];
        }
        columns.push_back(column);
    }

    std::string result;
    result.reserve(row_count_ * col_count_ + col_count_ - 1);

    for (size_t i = 0; i < columns.size(); ++i) {
        result += columns[i];
        if (i < columns.size() - 1) {
            result += ' ';
        }
    }

    return result;
}

}  // namespace crypto_square
