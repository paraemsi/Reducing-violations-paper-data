#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::days;
using boost::gregorian::greg_weekday;

static constexpr std::uint8_t FIRST_DAY_OF_MONTH{1U};

[[nodiscard]] year_month_day meetup_day(year      year_in,
                                        month     month_in,
                                        weekday   weekday_in,
                                        schedule  which)
{
    const sys_days first_of_month{year_in / month_in / FIRST_DAY_OF_MONTH};

    const weekday first_weekday{first_of_month};

    const std::uint8_t first_weekday_index{
        static_cast<std::uint8_t>(first_weekday.c_encoding())};
    const std::uint8_t target_weekday_index{
        static_cast<std::uint8_t>(weekday_in.c_encoding())};

    const std::uint8_t diff_to_first_target{
        static_cast<std::uint8_t>(
            ((target_weekday_index + 7U) - first_weekday_index) % 7U)};

    auto make_offset_days = [](std::uint8_t offset) -> days
    {
        return days{static_cast<std::int64_t>(offset)};
    };

    sys_days result{};

    switch (which) {
        case schedule::first:
            result = first_of_month + make_offset_days(diff_to_first_target);
            break;

        case schedule::second:
            result = first_of_month +
                     make_offset_days(
                         static_cast<std::uint8_t>(diff_to_first_target + 7U));
            break;

        case schedule::third:
            result = first_of_month +
                     make_offset_days(
                         static_cast<std::uint8_t>(diff_to_first_target + 14U));
            break;

        case schedule::fourth:
            result = first_of_month +
                     make_offset_days(
                         static_cast<std::uint8_t>(diff_to_first_target + 21U));
            break;

        case schedule::teenth:
        {
            sys_days candidate{
                first_of_month + make_offset_days(diff_to_first_target)};
            while (true) {
                const year_month_day ymd{candidate};
                const std::uint8_t day_value{
                    static_cast<std::uint8_t>(ymd.day())};
                if ((day_value >= 13U) && (day_value <= 19U)) {
                    result = candidate;
                    break;
                }
                candidate += make_offset_days(7U);
            }
            break;
        }

        case schedule::last:
        {
            month next_month{month_in + months{1}};
            year  next_year{year_in};
            if (next_month > month{12}) {
                next_month = month{1};
                next_year += std::chrono::years{1};
            }
            const sys_days first_of_next{next_year / next_month /
                                         FIRST_DAY_OF_MONTH};
            const sys_days last_of_month{first_of_next - days{1}};
            const weekday  last_weekday{last_of_month};
            const std::uint8_t last_weekday_index{
                static_cast<std::uint8_t>(last_weekday.c_encoding())};
            const std::uint8_t diff_back{
                static_cast<std::uint8_t>(
                    (last_weekday_index + 7U - target_weekday_index) % 7U)};
            result = last_of_month - make_offset_days(diff_back);
            break;
        }

        default:
            throw std::invalid_argument("Unsupported schedule value");
    }

    return year_month_day{result};
}

boost::gregorian::date scheduler::get_date(boost::gregorian::greg_weekday wd,
                                           schedule                         which) const
{
    const date first_of_month{m_year, static_cast<unsigned short>(m_month), 1};

    const greg_weekday first_weekday{first_of_month.day_of_week()};
    const unsigned     diff_to_first_target{
        static_cast<unsigned>((wd.as_number() + 7U -
                               first_weekday.as_number()) %
                              7U)};

    const date first_target{first_of_month + days{diff_to_first_target}};

    date result_date{first_target};

    switch (which) {
        case schedule::first:
            break;

        case schedule::second:
            result_date += days{7};
            break;

        case schedule::third:
            result_date += days{14};
            break;

        case schedule::fourth:
            result_date += days{21};
            break;

        case schedule::teenth:
            while (!((result_date.day() >= 13) && (result_date.day() <= 19))) {
                result_date += days{7};
            }
            break;

        case schedule::last:
        {
            const date        last_of_month{first_of_month.end_of_month()};
            const greg_weekday last_wd{last_of_month.day_of_week()};
            const unsigned    diff_back{
                static_cast<unsigned>((last_wd.as_number() + 7U -
                                       wd.as_number()) %
                                      7U)};
            result_date = last_of_month - days{diff_back};
            break;
        }

        default:
            throw std::invalid_argument("Unsupported schedule value");
    }

    return result_date;
}

scheduler::scheduler(boost::gregorian::months_of_year month_in,
                     std::int32_t                     year_in) noexcept
    : m_year{std::chrono::year{year_in}}
    , m_month{std::chrono::month{
          static_cast<unsigned>(static_cast<unsigned>(month_in))}}
{
}

#define MEETUP_DEFINE_TEENTH(fname, weekday_enum)                                   \
    boost::gregorian::date scheduler::fname() const                                 \
    {                                                                               \
        return get_date(boost::gregorian::greg_weekday(weekday_enum),               \
                        schedule::teenth);                                          \
    }

MEETUP_DEFINE_TEENTH(monteenth, boost::date_time::Monday)
MEETUP_DEFINE_TEENTH(tuesteenth, boost::date_time::Tuesday)
MEETUP_DEFINE_TEENTH(wednesteenth, boost::date_time::Wednesday)
MEETUP_DEFINE_TEENTH(thursteenth, boost::date_time::Thursday)
MEETUP_DEFINE_TEENTH(friteenth, boost::date_time::Friday)
MEETUP_DEFINE_TEENTH(saturteenth, boost::date_time::Saturday)
MEETUP_DEFINE_TEENTH(sunteenth, boost::date_time::Sunday)

#undef MEETUP_DEFINE_TEENTH

#define MEETUP_DEFINE_ORDINAL(fname, ord_enum, weekday_enum)                        \
    boost::gregorian::date scheduler::fname() const                                 \
    {                                                                               \
        return get_date(boost::gregorian::greg_weekday(weekday_enum),               \
                        schedule::ord_enum);                                        \
    }

MEETUP_DEFINE_ORDINAL(first_monday,   first,  boost::date_time::Monday)
MEETUP_DEFINE_ORDINAL(first_tuesday,  first,  boost::date_time::Tuesday)
MEETUP_DEFINE_ORDINAL(first_wednesday,first,  boost::date_time::Wednesday)
MEETUP_DEFINE_ORDINAL(first_thursday, first,  boost::date_time::Thursday)
MEETUP_DEFINE_ORDINAL(first_friday,   first,  boost::date_time::Friday)
MEETUP_DEFINE_ORDINAL(first_saturday, first,  boost::date_time::Saturday)
MEETUP_DEFINE_ORDINAL(first_sunday,   first,  boost::date_time::Sunday)

MEETUP_DEFINE_ORDINAL(second_monday,   second,  boost::date_time::Monday)
MEETUP_DEFINE_ORDINAL(second_tuesday,  second,  boost::date_time::Tuesday)
MEETUP_DEFINE_ORDINAL(second_wednesday,second,  boost::date_time::Wednesday)
MEETUP_DEFINE_ORDINAL(second_thursday, second,  boost::date_time::Thursday)
MEETUP_DEFINE_ORDINAL(second_friday,   second,  boost::date_time::Friday)
MEETUP_DEFINE_ORDINAL(second_saturday, second,  boost::date_time::Saturday)
MEETUP_DEFINE_ORDINAL(second_sunday,   second,  boost::date_time::Sunday)

MEETUP_DEFINE_ORDINAL(third_monday,   third,  boost::date_time::Monday)
MEETUP_DEFINE_ORDINAL(third_tuesday,  third,  boost::date_time::Tuesday)
MEETUP_DEFINE_ORDINAL(third_wednesday,third,  boost::date_time::Wednesday)
MEETUP_DEFINE_ORDINAL(third_thursday, third,  boost::date_time::Thursday)
MEETUP_DEFINE_ORDINAL(third_friday,   third,  boost::date_time::Friday)
MEETUP_DEFINE_ORDINAL(third_saturday, third,  boost::date_time::Saturday)
MEETUP_DEFINE_ORDINAL(third_sunday,   third,  boost::date_time::Sunday)

MEETUP_DEFINE_ORDINAL(fourth_monday,   fourth,  boost::date_time::Monday)
MEETUP_DEFINE_ORDINAL(fourth_tuesday,  fourth,  boost::date_time::Tuesday)
MEETUP_DEFINE_ORDINAL(fourth_wednesday,fourth,  boost::date_time::Wednesday)
MEETUP_DEFINE_ORDINAL(fourth_thursday, fourth,  boost::date_time::Thursday)
MEETUP_DEFINE_ORDINAL(fourth_friday,   fourth,  boost::date_time::Friday)
MEETUP_DEFINE_ORDINAL(fourth_saturday, fourth,  boost::date_time::Saturday)
MEETUP_DEFINE_ORDINAL(fourth_sunday,   fourth,  boost::date_time::Sunday)

MEETUP_DEFINE_ORDINAL(last_monday,   last,  boost::date_time::Monday)
MEETUP_DEFINE_ORDINAL(last_tuesday,  last,  boost::date_time::Tuesday)
MEETUP_DEFINE_ORDINAL(last_wednesday,last,  boost::date_time::Wednesday)
MEETUP_DEFINE_ORDINAL(last_thursday, last,  boost::date_time::Thursday)
MEETUP_DEFINE_ORDINAL(last_friday,   last,  boost::date_time::Friday)
MEETUP_DEFINE_ORDINAL(last_saturday, last,  boost::date_time::Saturday)
MEETUP_DEFINE_ORDINAL(last_sunday,   last,  boost::date_time::Sunday)

#undef MEETUP_DEFINE_ORDINAL

}  // namespace meetup
