#include "kindergarten_garden.h"

#include <algorithm>
#include <sstream>
#include <utility>   // for std::move

namespace kindergarten_garden {

namespace {

/*  Split a diagram (two lines) into a std::array<std::string, 2> without
 *  copying individual characters more than necessary.
 */
std::array<std::string, 2U> split_rows(const std::string& diagram)
{
    std::stringstream ss(diagram);
    std::array<std::string, 2U> rows {};
    std::getline(ss, rows[0U]);
    std::getline(ss, rows[1U]);
    return rows;
}

} // anonymous namespace

/* static */ std::vector<std::string> garden::default_students()
{
    /*  Alphabetical list required by the specification. */
    return std::vector<std::string>{
        "Alice",   "Bob",    "Charlie", "David",
        "Eve",     "Fred",   "Ginny",   "Harriet",
        "Ileana",  "Joseph", "Kincaid", "Larry"
    };
}

garden::garden(const std::string& diagram,
               std::vector<std::string> students_in)
{
    /*  Ensure students are sorted alphabetically as mandated. */
    std::sort(students_in.begin(), students_in.end());
    m_students = std::move(students_in);

    /*  Cache indices for O(1) look-up. */
    for (std::size_t i { 0U }; i < m_students.size(); ++i) {
        m_index_map.emplace(m_students[i], i);
    }

    m_rows = split_rows(diagram);
}

std::vector<Plants> garden::plants(const std::string& student) const
{
    const auto it { m_index_map.find(student) };
    if (it == m_index_map.end()) {
        return {}; /* unknown student → empty result */
    }

    const std::size_t index { it->second * 2U }; /* starting cup position */

    std::vector<Plants> result {};
    result.reserve(4U);

    result.push_back(code_to_plant(m_rows[0U][index]));
    result.push_back(code_to_plant(m_rows[0U][(index + 1U)]));
    result.push_back(code_to_plant(m_rows[1U][index]));
    result.push_back(code_to_plant(m_rows[1U][(index + 1U)]));

    return result;
}

/* static */ Plants garden::code_to_plant(char code)
{
    switch (code) {
        case 'C': {
            return Plants::clover;
        }
        case 'G': {
            return Plants::grass;
        }
        case 'R': {
            return Plants::radishes;
        }
        case 'V': {
            return Plants::violets;
        }
        default: {
            /* Unrecognised character → treat as grass as a safe default. */
            return Plants::grass;
        }
    }
}

/*  Stand-alone helper that delegates to the garden class and returns the
 *  fixed-size array expected by the tests. */
std::array<Plants, 4U> plants(const std::string& diagram,
                              const std::string& student)
{
    garden g(diagram);
    const auto vec { g.plants(student) };

    std::array<Plants, 4U> result {};
    for (std::size_t i { 0U }; (i < 4U) && (i < vec.size()); ++i) {
        result[i] = vec[i];
    }
    return result;
}

}  // namespace kindergarten_garden
