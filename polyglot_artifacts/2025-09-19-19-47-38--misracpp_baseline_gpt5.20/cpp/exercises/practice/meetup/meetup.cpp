#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {
constexpr int Sunday = 0;
constexpr int Monday = 1;
constexpr int Tuesday = 2;
constexpr int Wednesday = 3;
constexpr int Thursday = 4;
constexpr int Friday = 5;
constexpr int Saturday = 6;
} // namespace

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : month_{static_cast<int>(month)}, year_{year} {}

boost::gregorian::date scheduler::nth_weekday(int desiredDow, int n) const noexcept {
    using namespace boost::gregorian;
    date first{year_, month_, 1};
    int firstDow = first.day_of_week().as_number(); // Sunday=0
    int offset = (desiredDow - firstDow + 7) % 7;
    int d = 1 + offset + 7 * (n - 1);
    return date{year_, month_, d};
}

boost::gregorian::date scheduler::last_weekday(int desiredDow) const noexcept {
    using namespace boost::gregorian;
    int nextMonth = (month_ == 12) ? 1 : month_ + 1;
    int nextYear = (month_ == 12) ? (year_ + 1) : year_;
    date firstNext{nextYear, nextMonth, 1};
    date last = firstNext - days{1};
    int lastDow = last.day_of_week().as_number(); // Sunday=0
    int back = (lastDow - desiredDow + 7) % 7;
    int d = static_cast<int>(last.day().as_number()) - back;
    return date{year_, month_, d};
}

boost::gregorian::date scheduler::teenth_weekday(int desiredDow) const noexcept {
    using namespace boost::gregorian;
    date d13{year_, month_, 13};
    int dow13 = d13.day_of_week().as_number();
    int offset = (desiredDow - dow13 + 7) % 7;
    int d = 13 + offset;
    return date{year_, month_, d};
}

// teenth
boost::gregorian::date scheduler::monteenth() const { return teenth_weekday(Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return teenth_weekday(Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return teenth_weekday(Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return teenth_weekday(Thursday); }
boost::gregorian::date scheduler::friteenth() const { return teenth_weekday(Friday); }
boost::gregorian::date scheduler::saturteenth() const { return teenth_weekday(Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return teenth_weekday(Sunday); }

// first
boost::gregorian::date scheduler::first_monday() const { return nth_weekday(Monday, 1); }
boost::gregorian::date scheduler::first_tuesday() const { return nth_weekday(Tuesday, 1); }
boost::gregorian::date scheduler::first_wednesday() const { return nth_weekday(Wednesday, 1); }
boost::gregorian::date scheduler::first_thursday() const { return nth_weekday(Thursday, 1); }
boost::gregorian::date scheduler::first_friday() const { return nth_weekday(Friday, 1); }
boost::gregorian::date scheduler::first_saturday() const { return nth_weekday(Saturday, 1); }
boost::gregorian::date scheduler::first_sunday() const { return nth_weekday(Sunday, 1); }

// second
boost::gregorian::date scheduler::second_monday() const { return nth_weekday(Monday, 2); }
boost::gregorian::date scheduler::second_tuesday() const { return nth_weekday(Tuesday, 2); }
boost::gregorian::date scheduler::second_wednesday() const { return nth_weekday(Wednesday, 2); }
boost::gregorian::date scheduler::second_thursday() const { return nth_weekday(Thursday, 2); }
boost::gregorian::date scheduler::second_friday() const { return nth_weekday(Friday, 2); }
boost::gregorian::date scheduler::second_saturday() const { return nth_weekday(Saturday, 2); }
boost::gregorian::date scheduler::second_sunday() const { return nth_weekday(Sunday, 2); }

// third
boost::gregorian::date scheduler::third_monday() const { return nth_weekday(Monday, 3); }
boost::gregorian::date scheduler::third_tuesday() const { return nth_weekday(Tuesday, 3); }
boost::gregorian::date scheduler::third_wednesday() const { return nth_weekday(Wednesday, 3); }
boost::gregorian::date scheduler::third_thursday() const { return nth_weekday(Thursday, 3); }
boost::gregorian::date scheduler::third_friday() const { return nth_weekday(Friday, 3); }
boost::gregorian::date scheduler::third_saturday() const { return nth_weekday(Saturday, 3); }
boost::gregorian::date scheduler::third_sunday() const { return nth_weekday(Sunday, 3); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return nth_weekday(Monday, 4); }
boost::gregorian::date scheduler::fourth_tuesday() const { return nth_weekday(Tuesday, 4); }
boost::gregorian::date scheduler::fourth_wednesday() const { return nth_weekday(Wednesday, 4); }
boost::gregorian::date scheduler::fourth_thursday() const { return nth_weekday(Thursday, 4); }
boost::gregorian::date scheduler::fourth_friday() const { return nth_weekday(Friday, 4); }
boost::gregorian::date scheduler::fourth_saturday() const { return nth_weekday(Saturday, 4); }
boost::gregorian::date scheduler::fourth_sunday() const { return nth_weekday(Sunday, 4); }

// last
boost::gregorian::date scheduler::last_monday() const { return last_weekday(Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return last_weekday(Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return last_weekday(Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return last_weekday(Thursday); }
boost::gregorian::date scheduler::last_friday() const { return last_weekday(Friday); }
boost::gregorian::date scheduler::last_saturday() const { return last_weekday(Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return last_weekday(Sunday); }

}  // namespace meetup
