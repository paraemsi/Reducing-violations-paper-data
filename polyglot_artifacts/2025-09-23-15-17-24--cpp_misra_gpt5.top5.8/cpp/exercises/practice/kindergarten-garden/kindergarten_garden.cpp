#include "kindergarten_garden.h"

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

namespace kindergarten_garden {

namespace {
    constexpr std::array<const char*, 12U> default_students{
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };

    inline plant decode(const char ch) {
        if ((ch == 'G')) {
            return plant::grass;
        } else {
            if ((ch == 'C')) {
                return plant::clover;
            } else {
                if ((ch == 'R')) {
                    return plant::radishes;
                } else {
                    if ((ch == 'V')) {
                        return plant::violets;
                    } else {
                        throw std::invalid_argument("Unknown plant code");
                    }
                }
            }
        }
    }
}  // namespace

garden::garden(const std::string& diagram) {
    const std::string::size_type pos = diagram.find('\n');
    if ((pos == std::string::npos)) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    } else {
        const std::string::size_type one = static_cast<std::string::size_type>(1);
        rows_[0] = diagram.substr(0U, pos);
        rows_[1] = diagram.substr((pos + one));
        if ((rows_[0].size() != rows_[1].size())) {
            throw std::invalid_argument("Both rows must have the same number of cups");
        }
    }
}

std::vector<plant> garden::plants(const std::string& student_name) const {
    std::size_t idx = 0U;
    bool found = false;
    for (std::size_t i = 0U; (i < default_students.size()); ++i) {
        if ((student_name == default_students[i])) {
            idx = i;
            found = true;
            break;
        }
    }

    if ((!found)) {
        throw std::invalid_argument("Unknown student name");
    }

    const std::size_t base = (static_cast<std::size_t>(2U) * idx);

    // Basic sanity check to avoid out-of-range access on malformed diagrams
    if (((rows_[0].size() <= (base + static_cast<std::size_t>(1U))) || (rows_[1].size() <= (base + static_cast<std::size_t>(1U))))) {
        throw std::out_of_range("Diagram does not contain enough cups for the requested student");
    }

    std::vector<plant> result{};
    result.reserve(4U);
    result.push_back(decode(rows_[0][base]));
    result.push_back(decode(rows_[0][(base + static_cast<std::size_t>(1U))]));
    result.push_back(decode(rows_[1][base]));
    result.push_back(decode(rows_[1][(base + static_cast<std::size_t>(1U))]));
    return result;
}

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student_name) {
    const std::string::size_type pos = diagram.find('\n');
    if ((pos == std::string::npos)) {
        throw std::invalid_argument("Diagram must contain two rows separated by a newline");
    } else {
        const std::string::size_type one = static_cast<std::string::size_type>(1);
        const std::string row0 = diagram.substr(0U, pos);
        const std::string row1 = diagram.substr((pos + one));
        if ((row0.size() != row1.size())) {
            throw std::invalid_argument("Both rows must have the same number of cups");
        }

        std::size_t idx = 0U;
        bool found = false;
        for (std::size_t i = 0U; (i < default_students.size()); ++i) {
            if ((student_name == default_students[i])) {
                idx = i;
                found = true;
                break;
            }
        }

        if ((!found)) {
            throw std::invalid_argument("Unknown student name");
        }

        const std::size_t base = (static_cast<std::size_t>(2U) * idx);

        if (((row0.size() <= (base + static_cast<std::size_t>(1U))) || (row1.size() <= (base + static_cast<std::size_t>(1U))))) {
            throw std::out_of_range("Diagram does not contain enough cups for the requested student");
        }

        return std::array<Plants, 4U>{
            decode(row0[base]),
            decode(row0[(base + static_cast<std::size_t>(1U))]),
            decode(row1[base]),
            decode(row1[(base + static_cast<std::size_t>(1U))])
        };
    }
}

}  // namespace kindergarten_garden
