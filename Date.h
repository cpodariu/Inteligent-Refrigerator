#ifndef DATE_H
#define DATE_H

#include <time.h>

typedef struct
{
  int year;
  int month;
  int day;
} t_date;

int get_julian_date(t_date date);
int get_days_between(t_date date1, t_date date2);

#endif /* end of include guard: DATE_H */
