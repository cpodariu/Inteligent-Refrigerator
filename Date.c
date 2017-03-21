#include "Date.h"

int get_julian_date(t_date date)
{
  int a = (int)((14 - date.month)/12);
  int y = date.year + 4800 - a;
  int m = date.month + 12 * a - 3;

  return (date.day + (int)((153 * m + 2)/5) + 365 * y + (int)(y / 4) - (int)(y / 100) + (int)(y / 400) - 32045);
}

int get_days_between(t_date date1, t_date date2)
{
  return (get_julian_date(date2) - get_julian_date(date1));
}

int expires_soon(t_date date, int x)
{
  time_t the_time = time(NULL);
  struct tm *a_time = localtime(&the_time);
  t_date date2;

  date2.day = a_time->tm_mday;
  date2.month = a_time->tm_mon + 1;
  date2.year = a_time->tm_year + 1900;

  if (get_days_between(date2, date) <= x)
    return 1;
  return 0;
}

// int get_days_between(t_date d1, t_date d2)
// {
//   int aux;
//   if (d1.day != d2.month)
//   {
//     if (d1.day < d2.day)
//     {
//       aux = d2.day - d1.day;
//       d1.day = d2.day;
//       return get_days_between(d1, d2);
//     }
//     else
//     {
//       aux = d2.day - d1.day;
//       d2.day = d1.day;
//       return get_days_between(d1, d2);
//     }
//   }
//   if (d1.month != d2.month)
//   {
//     if (d1.month < d2.month)
//     {
//       aux = (d2.month - d1.month) * 30;
//       d1.month = d2.month;
//       return aux + get_days_between(d1, d2);
//     }
//     else
//     {
//       aux = (d2.month - d1.month) * 30;
//       d2.month = d1.month;
//       return get_days_between(d1, d2);
//     }
//   }
// }
