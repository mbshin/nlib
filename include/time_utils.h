//
// Created by mobum on 5/29/24.
//
#ifndef NLIB_TIME_UTIL_H
#define NLIB_TIME_UTIL_H

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Enum to represent the timezone
 */
typedef enum {
    kKst, // Korea Standard Time
    kUtc, // Coordinated Universal Time
    kTimeZoneCount // Number of timezones
} NTimeZone;

/**
 * Enum to represent the time precision
 */
typedef enum {
    kMILLISECONDS,
    kMICROSECONDS
} NTimePrecision;

/**
 * Set the timezone.
 * @param tz TimeZone enum value.
 */
int n_set_timezone(NTimeZone tz);

/**
 * Get the current date in yyyymmdd format as an integer in the current timezone.
 * @return The current date in yyyymmdd format as an integer.
 */
int n_get_current_date();

/**
 * Get the current date in yyyymmdd format as a string in the current timezone.
 * @param date_str Buffer to hold the date string.
 * @param size Size of the buffer.
 */
void n_get_current_date_string(char *date_str, size_t size);

/**
 * Get the current time in hhmmss format with the specified precision as an integer.
 * @param precision TimePrecision enum value.
 * @return The current time in hhmmss format with the specified precision as an integer.
 */
int n_get_current_time(NTimePrecision precision);

/**
 * Get the current time in hhmmss format with the specified precision as a string.
 * @param time_str Buffer to hold the time string.
 * @param size Size of the buffer.
 * @param precision TimePrecision enum value.
 */
void n_get_current_time_string(char *time_str, size_t size, NTimePrecision precision);

#ifdef __cplusplus
}
#endif

#endif //NLIB_TIME_UTIL_H
