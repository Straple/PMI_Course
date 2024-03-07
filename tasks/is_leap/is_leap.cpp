#include "is_leap.h"

bool IsLeap(int year) {
    static const int CRITERIA_1_LEAP_MOD = 4;
    static const int CRITERIA_2_NON_LEAP_MOD = 100;
    static const int CRITERIA_3_LEAP_MOD = 400;

    return (year % CRITERIA_1_LEAP_MOD == 0 && year % CRITERIA_2_NON_LEAP_MOD != 0) || year % CRITERIA_3_LEAP_MOD == 0;
}