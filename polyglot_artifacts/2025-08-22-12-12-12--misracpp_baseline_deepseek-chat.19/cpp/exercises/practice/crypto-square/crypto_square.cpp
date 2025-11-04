#include "crypto_square.h"
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>
using namespace std;

namespace crypto_square {

cipher::cipher(const string& text) {
    for (char c : text) {
        if (isalnum(c)) {
            normalized += tolower(c);
        }
    }
}

string cipher::normalize_plain_text() const {
    return normalized;
}

size_t cipher::size() const {
    if (normalized.empty()) return 0;
    // Calculate the number of columns which is the ceiling of the square root of the length
    return static_cast<size_t>(ceil(sqrt(normalized.size())));
}

string cipher::cipher_text() const {
    if (normalized.empty()) return "";
    size_t c = size();
    // The number of rows is the ceiling of length / columns
    size_t r = (normalized.size() + c - 1) / c;
    
    // Read down the columns, only adding characters that exist
    string result;
    for (size_t col = 0; col < c; col++) {
        for (size_t row = 0; row < r; row++) {
            size_t index = row * c + col;
            if (index < normalized.size()) {
                result += normalized[index];
            }
            // No padding with spaces
        }
    }
    return result;
}

string cipher::normalized_cipher_text() const {
    if (normalized.empty()) return "";
    size_t c = size();
    size_t r = (normalized.size() + c - 1) / c;
    
    // To get chunks, we need to split into c parts of length r
    // Some of the last parts may need to be padded with spaces
    string result;
    
    for (size_t col = 0; col < c; col++) {
        if (col != 0) {
            result += ' ';
        }
        for (size_t row = 0; row < r; row++) {
            size_t index = row * c + col;
            if (index < normalized.size()) {
                result += normalized[index];
            } else {
                result += ' ';
            }
        }
    }
    return result;
}

}  // namespace crypto_square
