#include <stdio.h>

int isLeapYear(int year)
{
  if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
  {
    return 1;
  }
  return 0;
}

int main(int argc, char const *argv[])
{
  const char dayName[7][3] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  const char monthName[12][3] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  int date;      // 1-31
  int month;     // 1-12
  int year;      // 1970++
  int dayOfWeek; // 0-6
  int hour;      // 0-23
  int minute;    // 0-59
  int second;    // 0-59
  date = month = year = hour = minute = second = 0;
  dayOfWeek = 4;
  // s
  int timestamp;
  timestamp = 50;
  // s
  hour = timestamp / (60 * 60);
  timestamp -= hour * 60 * 60;
  minute = timestamp / 60;
  timestamp -= minute * 60;
  second = timestamp;
  hour += minute / 60;
  minute = minute % 60;
  int nDays = hour / 24;
  hour %= 24;

  // find specific date
  year = 1970;
  while (nDays > 0)
  {
    if (nDays / 365 > 0)
    {
      if (isLeapYear(year))
      {
        nDays -= 366;
        dayOfWeek = (dayOfWeek + 366) % 7;
      }
      else
      {
        nDays -= 365;
        dayOfWeek = (dayOfWeek + 365) % 7;
      }
      year++;
      continue;
    }
    int dayNum;
    if (month == 2)
    {
      dayNum = (isLeapYear(year)) ? 29 : 28;
    }
    else if (month >= 8)
    {
      dayNum = month % 2 == 0 ? 31 : 30;
    }
    else
    {
      dayNum = month % 2 == 0 ? 30 : 31;
    }

    if (nDays > dayNum)
    {
      nDays -= dayNum;
      month++;
      dayOfWeek = (dayOfWeek + dayNum) % 7;
      continue;
    }

    date = nDays;
    dayOfWeek = (dayOfWeek + date) % 7;
    nDays = 0;
  }

  printf("%d %d %d %d %d %d %d", hour, minute, second, date, month, year, dayOfWeek);
  // printf("%d %s %s %d",year,month,date,hour);
  return 0;
}
