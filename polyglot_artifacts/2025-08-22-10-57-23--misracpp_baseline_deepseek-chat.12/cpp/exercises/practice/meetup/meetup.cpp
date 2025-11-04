#include "meetup.h"
#include <string>
#include <stdexcept>
#include <array>
#include <algorithm>
using namespace std;

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Implement all the member functions
// Teenth functions
boost::gregorian::date scheduler::monteenth() const {
    int day = find_day("teenth", "Monday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::tuesteenth() const {
    int day = find_day("teenth", "Tuesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::wednesteenth() const {
    int day = find_day("teenth", "Wednesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::thursteenth() const {
    int day = find_day("teenth", "Thursday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::friteenth() const {
    int day = find_day("teenth", "Friday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::saturteenth() const {
    int day = find_day("teenth", "Saturday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::sunteenth() const {
    int day = find_day("teenth", "Sunday");
    return boost::gregorian::date(year_, month_, day);
}

// First week functions
boost::gregorian::date scheduler::first_monday() const {
    int day = find_day("first", "Monday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::first_tuesday() const {
    int day = find_day("first", "Tuesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::first_wednesday() const {
    int day = find_day("first", "Wednesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::first_thursday() const {
    int day = find_day("first", "Thursday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::first_friday() const {
    int day = find_day("first", "Friday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::first_saturday() const {
    int day = find_day("first", "Saturday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::first_sunday() const {
    int day = find_day("first", "Sunday");
    return boost::gregorian::date(year_, month_, day);
}

// Second week functions
boost::gregorian::date scheduler::second_monday() const {
    int day = find_day("second", "Monday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::second_tuesday() const {
    int day = find_day("second", "Tuesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::second_wednesday() const {
    int day = find_day("second", "Wednesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::second_thursday() const {
    int day = find_day("second", "Thursday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::second_friday() const {
    int day = find_day("second", "Friday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::second_saturday() const {
    int day = find_day("second", "Saturday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::second_sunday() const {
    int day = find_day("second", "Sunday");
    return boost::gregorian::date(year_, month_, day);
}

// Third week functions
boost::gregorian::date scheduler::third_monday() const {
    int day = find_day("third", "Monday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::third_tuesday() const {
    int day = find_day("third", "Tuesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::third_wednesday() const {
    int day = find_day("third", "Wednesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::third_thursday() const {
    int day = find_day("third", "Thursday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::third_friday() const {
    int day = find_day("third", "Friday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::third_saturday() const {
    int day = find_day("third", "Saturday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::third_sunday() const {
    int day = find_day("third", "Sunday");
    return boost::gregorian::date(year_, month_, day);
}

// Fourth week functions
boost::gregorian::date scheduler::fourth_monday() const {
    int day = find_day("fourth", "Monday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::fourth_tuesday() const {
    int day = find_day("fourth", "Tuesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::fourth_wednesday() const {
    int day = find_day("fourth", "Wednesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::fourth_thursday() const {
    int day = find_day("fourth", "Thursday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::fourth_friday() const {
    int day = find_day("fourth", "Friday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::fourth_saturday() const {
    int day = find_day("fourth", "Saturday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::fourth_sunday() const {
    int day = find_day("fourth", "Sunday");
    return boost::gregorian::date(year_, month_, day);
}

// Last week functions
boost::gregorian::date scheduler::last_monday() const {
    int day = find_day("last", "Monday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::last_tuesday() const {
    int day = find_day("last", "Tuesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::last_wednesday() const {
    int day = find_day("last", "Wednesday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::last_thursday() const {
    int day = find_day("last", "Thursday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::last_friday() const {
    int day = find_day("last", "Friday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::last_saturday() const {
    int day = find_day("last", "Saturday");
    return boost::gregorian::date(year_, month_, day);
}
boost::gregorian::date scheduler::last_sunday() const {
    int day = find_day("last", "Sunday");
    return boost::gregorian::date(year_, month_, day);
}

int scheduler::find_day(const string& week, const string& weekday) const {
    // Parse the weekday
    int target_dow = parse_weekday(weekday);
    
    if (week == "teenth") {
        // Check days 13-19
        for (int day = 13; day <= 19; day++) {
            if (day_of_week(day) == target_dow) {
                return day;
            }
        }
    } else {
        // For first, second, third, fourth, last
        int week_index;
        if (week == "first") week_index = 0;
        else if (week == "second") week_index = 1;
        else if (week == "third") week_index = 2;
        else if (week == "fourth") week_index = 3;
        else if (week == "last") week_index = -1;
        else throw runtime_error("Invalid week specification");
        
        // Find all days with matching weekday in the month
        // To find the number of days in the month
        array<int, 12> month_days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int days_in_month = month_days[month_ - 1];
        // Adjust for leap year in February
        if (month_ == 2) {
            if ((year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0)) {
                days_in_month = 29;
            }
        }
        
        if (week_index != -1) {
            int count = 0;
            for (int day = 1; day <= days_in_month; day++) {
                if (day_of_week(day) == target_dow) {
                    if (count == week_index) {
                        return day;
                    }
                    count++;
                }
            }
        } else {
            // For last, find the last occurrence
            for (int day = days_in_month; day >= 1; day--) {
                if (day_of_week(day) == target_dow) {
                    return day;
                }
            }
        }
    }
    throw runtime_error("No valid day found");
}

int scheduler::day_of_week(int day) const {
    int m = month_;
    int y = year_;
    if (m < 3) {
        m += 12;
        y -= 1;
    }
    int k = y % 100;
    int j = y / 100;
    int h = (day + 13*(m+1)/5 + k + k/4 + j/4 + 5*j) % 7;
    // Adjust to make 0=Saturday, 1=Sunday, etc. to 0=Sunday, 1=Monday, etc.
    int dow = (h + 6) % 7;
    return dow;
}

int scheduler::parse_weekday(const string& weekday) const {
    if (weekday == "Sunday") return 0;
    if (weekday == "Monday") return 1;
    if (weekday == "Tuesday") return 2;
    if (weekday == "Wednesday") return 3;
    if (weekday == "Thursday") return 4;
    if (weekday == "Friday") return 5;
    if (weekday == "Saturday") return 6;
    throw runtime_error("Invalid weekday");
}

}  // namespace meetup
