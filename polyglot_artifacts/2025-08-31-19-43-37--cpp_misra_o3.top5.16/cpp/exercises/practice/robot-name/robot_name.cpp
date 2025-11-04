#include "robot_name.h"

namespace robot_name {

namespace
{

static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char digits[]  = "0123456789";

std::string generate_name(std::mt19937& engine)
{
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string generated_name{};
    generated_name.reserve(5U);

    generated_name.push_back(letters[letter_dist(engine)]);
    generated_name.push_back(letters[letter_dist(engine)]);
    generated_name.push_back(digits[digit_dist(engine)]);
    generated_name.push_back(digits[digit_dist(engine)]);
    generated_name.push_back(digits[digit_dist(engine)]);

    return generated_name;
}

std::string generate_unique_name()
{
    static std::unordered_set<std::string> used_names{};
    static std::mutex used_names_mutex{};
    static std::random_device rd{};
    static std::mt19937 engine(rd());

    std::string candidate{};

    while (candidate.empty())
    {
        candidate = generate_name(engine);

        std::lock_guard<std::mutex> guard(used_names_mutex);
        if ((used_names.find(candidate)) == used_names.end())
        {
            (void)used_names.insert(candidate);
        }
        else
        {
            candidate.clear();
        }
    }

    return candidate;
}

} // anonymous namespace

robot::robot() : m_name()
{
    /* Name will be set lazily upon first request */
}

const std::string& robot::name() const
{
    if (m_name.empty())
    {
        m_name = generate_unique_name();
    }

    return m_name;
}

void robot::reset()
{
    m_name.clear();
}

}  // namespace robot_name
