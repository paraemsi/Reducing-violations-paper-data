#include "crypto_square.h"

#include <cstddef>
#include <locale>
#include <utility>

namespace crypto_square {

cipher::cipher(const std::string& text) : normalized_{normalize(text)} {}

/* static */ std::string cipher::normalize(const std::string& text)
{
    const std::locale loc{};
    std::string result{};

    for (char ch : text) {
        /*  Promote to unsigned char first to avoid implementation-defined behaviour
            when converting a potentially negative plain `char` to `int`.   */
        const unsigned char uch{static_cast<unsigned char>(ch)};

        if (std::isalnum(static_cast<int>(uch), loc) != 0) {
            result.push_back(
                static_cast<char>(std::tolower(static_cast<int>(uch), loc)));
        }
    }

    return result;
}

std::string cipher::normalize_plain_text() const
{
    return normalized_;
}

std::pair<std::size_t, std::size_t> cipher::rectangle_dimensions() const
{
    const std::size_t length{normalized_.length()};

    if (length == 0U) {
        return {0U, 0U};
    }

    std::size_t columns{1U};
    while ((columns * columns) < length) {
        ++columns;
    }

    const std::size_t rows{(length + columns - 1U) / columns};

    return {rows, columns};
}

std::vector<std::string> cipher::plain_text_segments() const
{
    const auto [rows, columns] = rectangle_dimensions();

    std::vector<std::string> segments{};

    for (std::size_t idx_row{0U}; idx_row < rows; ++idx_row) {
        const std::size_t start_index{idx_row * columns};
        segments.emplace_back(normalized_.substr(start_index, columns));
    }

    return segments;
}

std::string cipher::cipher_text() const
{
    const auto segments = plain_text_segments();
    if (segments.empty()) {
        return std::string{};
    }

    const std::size_t columns{segments.front().length()};
    const std::size_t rows{segments.size()};

    std::string output{};
    output.reserve(normalized_.length());

    for (std::size_t idx_col{0U}; idx_col < columns; ++idx_col) {
        for (std::size_t idx_row{0U}; idx_row < rows; ++idx_row) {
            const std::string& segment_ref = segments[idx_row];
            if (idx_col < segment_ref.length()) {
                output.push_back(segment_ref[idx_col]);
            }
        }
    }

    return output;
}

std::string cipher::normalized_cipher_text() const
{
    const auto segments = plain_text_segments();
    if (segments.empty()) {
        return std::string{};
    }

    const std::size_t columns{segments.front().length()};
    const std::size_t rows{segments.size()};

    std::vector<std::string> column_chunks{};
    column_chunks.reserve(columns);

    for (std::size_t idx_col{0U}; idx_col < columns; ++idx_col) {
        std::string chunk{};
        chunk.reserve(rows);

        for (std::size_t idx_row{0U}; idx_row < rows; ++idx_row) {
            const std::string& segment_ref = segments[idx_row];
            if (idx_col < segment_ref.length()) {
                chunk.push_back(segment_ref[idx_col]);
            } else {
                chunk.push_back(' ');
            }
        }

        column_chunks.push_back(chunk);
    }

    std::string output{};
    for (std::size_t idx_col{0U}; idx_col < column_chunks.size(); ++idx_col) {
        output.append(column_chunks[idx_col]);
        if ((idx_col + 1U) < column_chunks.size()) {
            output.push_back(' ');
        }
    }

    return output;
}

}  // namespace crypto_square
