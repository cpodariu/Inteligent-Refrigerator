#ifndef DATE_H
#define DATE_H

#include <time.h>
#include <assert.h>
typedef struct
{
  int year;
  int month;
  int day;
} t_date;

int get_julian_date(t_date date);
int get_days_between(t_date date1, t_date date2);
int expires_soon(t_date date, int x);
void test_get_julian_date();
void test_get_days_between();
void test_expires_soon();
void test_date();
#endif /* end of include guard: DATE_H */
