#include "time_utils.h"
#include <stdio.h>
#include <stdlib.h>

// Array of timezone names
static const char *kTimeZoneNames[kTimeZoneCount] = {
        "Asia/Seoul", // KST
        "UTC"         // UTC
};

/**
 * Set the timezone.
 * @param tz TimeZone enum value.
 */
int n_set_timezone(NTimeZone tz) {
    if ( tz < kTimeZoneCount) {
        setenv("TZ", kTimeZoneNames[tz], 1);
        tzset();
    } else {
        fprintf(stderr, "Invalid timezone specified\n");
        return -1;
    }

    return 0;
}

/**
 * Get the current date in yyyymmdd format as an integer in the current timezone.
 * @return The current date in yyyymmdd format as an integer.
 */
int n_get_current_date() {
    time_t t = time(NULL);
    struct tm *tm_local = localtime(&t);
    return (tm_local->tm_year + 1900) * 10000 + (tm_local->tm_mon + 1) * 100 + tm_local->tm_mday;
}
/**
 * Get the current date in yyyymmdd format as a string in the current timezone.
 * @param date_str Buffer to hold the date string.
 * @param size Size of the buffer.
 */
void n_get_current_date_string(char *date_str, size_t size) {
    time_t t = time(NULL);
    struct tm *tm_local = localtime(&t);
    snprintf(date_str, size, "%04d%02d%02d", tm_local->tm_year + 1900, tm_local->tm_mon + 1, tm_local->tm_mday);
}

/**
 * Internal helper function to get the current time and date components.
 * @param tm_local Pointer to struct tm to hold the local time.
 * @param nanoseconds Pointer to long to hold the nanoseconds.
 */
static void n_get_time_components(struct tm *tm_local, long *nanoseconds) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    *tm_local = *localtime(&ts.tv_sec);
    *nanoseconds = ts.tv_nsec;
}

/**
 * Internal helper function to format time with the specified precision.
 * @param time_str Buffer to hold the time string.
 * @param size Size of the buffer.
 * @param tm_local Pointer to struct tm holding the local time.
 * @param nanoseconds Nanoseconds part of the current time.
 * @param precision TimePrecision enum value.
 */
static void n_format_time(char *time_str, size_t size, const struct tm *tm_local, long nanoseconds, NTimePrecision precision) {
    switch (precision) {
        case kMILLISECONDS: {
            long milliseconds = nanoseconds / 1000000;
            snprintf(time_str, size, "%02d%02d%02d%03ld", tm_local->tm_hour, tm_local->tm_min, tm_local->tm_sec, milliseconds);
        }
            break;
        case kMICROSECONDS: {
            long microseconds = nanoseconds / 1000;
            snprintf(time_str, size, "%02d%02d%02d%06ld", tm_local->tm_hour, tm_local->tm_min, tm_local->tm_sec,
                     microseconds);
        }
        break;
    }
}

/**
 * Get the current time in hhmmss format with the specified precision as an integer.
 * @param precision TimePrecision enum value.
 * @return The current time in hhmmss format with the specified precision as an integer.
 */
int get_current_time(NTimePrecision precision) {
    struct tm tm_local;
    long nanoseconds;
    n_get_time_components(&tm_local, &nanoseconds);

    int time_int = tm_local.tm_hour * 1000000 + tm_local.tm_min * 10000 + tm_local.tm_sec * 100;

    switch (precision) {
        case kMILLISECONDS:
            time_int = time_int * 1000 + (int)(nanoseconds / 1000000);
            break;
        case kMICROSECONDS:
            time_int = time_int * 1000000 + (int)(nanoseconds / 1000);
            break;
    }

    return time_int;
}

/**
 * Get the current time in hhmmss format with the specified precision as a string.
 * @param time_str Buffer to hold the time string.
 * @param size Size of the buffer.
 * @param precision TimePrecision enum value.
 */
void get_current_time_string(char *time_str, size_t size, NTimePrecision precision) {
    struct tm tm_local;
    long nanoseconds;
    n_get_time_components(&tm_local, &nanoseconds);

    n_format_time(time_str, size, &tm_local, nanoseconds, precision);
}
