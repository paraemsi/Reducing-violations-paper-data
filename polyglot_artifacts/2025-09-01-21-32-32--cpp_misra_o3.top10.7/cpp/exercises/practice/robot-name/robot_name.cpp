#include "robot_name.h"

namespace robot_name {

/*--------------------------------------------------------------------
 * Static data – defined once in this translation unit.
 *------------------------------------------------------------------*/
std::unordered_set<std::string> Robot::used_names_{};
std::mt19937_64                 Robot::rng_{std::random_device{}()};

/*--------------------------------------------------------------------
 * Constants used for random name generation.
 *------------------------------------------------------------------*/
namespace {
    constexpr std::array<char, 26U> letters{
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    constexpr std::array<char, 10U> digits{
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };
}  // unnamed namespace

/*--------------------------------------------------------------------
 * ctor – no work; name is generated lazily.
 *------------------------------------------------------------------*/
Robot::Robot() = default;

/*--------------------------------------------------------------------
 * Public query – if no name yet, create one.
 *------------------------------------------------------------------*/
const std::string& Robot::name() const
{
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

/*--------------------------------------------------------------------
 * Reset – erase current name and free it for reuse.
 *------------------------------------------------------------------*/
void Robot::reset()
{
    if (!name_.empty()) {
        (void)used_names_.erase(name_);
        name_.clear();
    }
}

/*--------------------------------------------------------------------
 * Internal helper – generates a two-letter / three-digit unique id.
 *------------------------------------------------------------------*/
std::string Robot::generate_unique_name()
{
    std::uniform_int_distribution<std::size_t> dist_letter(0U, letters.size() - 1U);
    std::uniform_int_distribution<std::size_t> dist_digit(0U, digits.size() - 1U);

    std::string candidate;
    candidate.reserve(5U);

    for (;;) {
        {
            candidate.clear();
            candidate.push_back(letters[dist_letter(rng_)]);
            candidate.push_back(letters[dist_letter(rng_)]);
            candidate.push_back(digits[dist_digit(rng_)]);
            candidate.push_back(digits[dist_digit(rng_)]);
            candidate.push_back(digits[dist_digit(rng_)]);
        }

        const auto inserted = used_names_.insert(candidate).second;
        if (inserted) {
            return candidate;
        }
        /* Name collision – try again */
    }
}

}  // namespace robot_name
