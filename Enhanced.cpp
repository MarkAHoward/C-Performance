/***********************************************************************
* Author:
*    Mark Howard
* Summary:
*    For this lab, I first removed all the asserts.  After doing so, I set
*    about optimizing the functions I could.  For the function isLeapYear,
*    I removed all the if statements and made it all compute with one
*    line.  For numDaysInMonth I reduced the amount of if statements and turned
*    them into a switch statement. For numDaysInYear I made it so it only calls
*    isLeapYear once and set a default.  The function computeOffset took the 
*    most time because I got ride of one of the for loops and instead did everthing
*    arithmetically.
*
*    Another honorable mention would be that I removed any and all traces of
*    the one and only Rogers, Buck.
************************************************************************/

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <math.h>

// Get lab specific variables --You must include this #include--
#include "/home/ecen324/calendarOptimize/lab_consts.h"

using namespace std;

// The year the current calendar began to be valid
#define yearSeed 1753


/**********************************************************************
 * Removed Rogers, Buck.
 * Condensed function to only have one if statement.
 * Removed Asserts.
 ***********************************************************************/
bool isLeapYear(int year)
{
   bool leap = ((year % 400 == 0)||((year % 4 == 0) && (year % 100 != 0)));  
   return leap;
}


/**********************************************************************
 * Removed Rogers, Buck.
 * Changed the if statements to a switch statement.
 * Removed Asserts.
 ***********************************************************************/
int numDaysInMonth(int month, int year)
{
int days = 31;

switch (month) {
case 2:
   
   if (isLeapYear(year)) {
      days = 29; break;
   } else {
      days = 28; break;
   }
case 4: days = 30; break;
case 6: days = 30; break;
case 9: days = 30; break;
case 11: days = 30; break;
}
return days;
}
/**********************************************************************
 * Removed Rogers, Buck.
 * Made it so isLeapYear is only called once instead of twice.
 * Removed Asserts.
 ***********************************************************************/
int numDaysInYear(int year)
{
   int days = 365;
   if (isLeapYear(year))
      days = 366;
   return days;
}


/**********************************************************************
 * Removed Rogers, Buck.
 * Offset is from Monday because Jan 1, 1753 was a Monday.
 * Removed Asserts.
 ***********************************************************************/
int computeOffset(int month, int year)
{
   int days = 0;
   int leapYearsBefore = floor(year/4) - floor(year/100) + floor(year/400);
   int seedleapYearsBefore = floor(yearSeed/4) - floor(yearSeed/100) + floor(yearSeed/400);
   int leapYears = leapYearsBefore - seedleapYearsBefore;
   days += ((year - yearSeed) * 365) + leapYears; 
   if (isLeapYear(year))
      days -= 1;


   //Add up the days associated with each month
   for (int cMonth = 1; cMonth < month; cMonth++)
   {
      days += numDaysInMonth(cMonth, year);
   }
   return days % 7;
}

/**********************************************************************
 * Removed Rogers, Buck.
 * Removed Asserts.
 ***********************************************************************/
int displayHeader(int month, int year, char *calendar, int pos)
{
   pos += sprintf(calendar + pos, "\n");

   // Write the month
   if (month == 1)
      pos += sprintf(calendar + pos, "%s", "January");
   if (month == 2)
      pos += sprintf(calendar + pos, "%s", "February");
   if (month == 3)
      pos += sprintf(calendar + pos, "%s", "March");
   if (month == 4)
      pos += sprintf(calendar + pos, "%s", "April");
   if (month == 5)
      pos += sprintf(calendar + pos, "%s", "May");
   if (month == 6)
      pos += sprintf(calendar + pos, "%s", "June");
   if (month == 7)
      pos += sprintf(calendar + pos, "%s", "July");
   if (month == 8)
      pos += sprintf(calendar + pos, "%s", "August");
   if (month == 9)
      pos += sprintf(calendar + pos, "%s", "September");
   if (month == 10)
      pos += sprintf(calendar + pos, "%s", "October");
   if (month == 11)
      pos += sprintf(calendar + pos, "%s", "November");
   if (month == 12)
      pos += sprintf(calendar + pos, "%s", "December");

   // Write the year
   pos += sprintf(calendar + pos, ", ");
   pos += sprintf(calendar + pos, "%i", year);
   pos += sprintf(calendar + pos, "\n");

   return pos;
}

/********************************************************************
 * Removed Rogers, Buck.
 * Removed Asserts.
 *******************************************************************/
int displayTable(int numDays, int offset, char *calendar, int pos)
{  
   // Special case offset==6. We don't want a blank first line
   if (offset == 6)
      offset = -1;

   // Display the header
   for (int i = 0; i < 7; i++)
   {
      pos += sprintf(calendar + pos, "  ");
      if (i == 0)
         pos += sprintf(calendar + pos, "%s", "Su");
      if (i == 1)
         pos += sprintf(calendar + pos, "%s", "Mo");
      if (i == 2)
         pos += sprintf(calendar + pos, "%s", "Tu");
      if (i == 3)
         pos += sprintf(calendar + pos, "%s", "We");
      if (i == 4)
         pos += sprintf(calendar + pos, "%s", "Th");
      if (i == 5)
         pos += sprintf(calendar + pos, "%s", "Fr");
      if (i == 6)
         pos += sprintf(calendar + pos, "%s", "Sa");
   }
   pos += sprintf(calendar + pos, "\n");

   // Display the individual locations on the calendar grid
   int dow = 0; // day of week
   int dom;
   for (dom = -offset; dom <= numDays; dom++, dow++)
   {
      // Display the number or not
      if (dom > 0)
         pos += sprintf(calendar + pos, "% 4i", dom);
      if (dom <= 0)
         pos += sprintf(calendar + pos, "    ");

      // Display the end-of-row marker
      if (dow % 7 == 6)
         pos += sprintf(calendar + pos, "\n");
   }

   // Extra ENDL as necessary
   if (dow % 7 != 0)
      pos += sprintf(calendar + pos, "\n");

   return pos;
}  


/**********************************************************************
 * Removed Rogers, Buck.
 * Removed Asserts.
 ***********************************************************************/
void display(int month, int year, char *calendar)
{
   int pos = 0;
   int offset = computeOffset(month, year);

   // Header
   pos += displayHeader(month, year, calendar, pos);

   // Body of the table
   pos += displayTable(numDaysInMonth(month, year), offset, calendar, pos);

   // Output calendars shouldn't overlap each other in calendar array buffer
   return;
}


/**********************************************************************
 * YOU MUST HAVE THIS FUNCTION SIGNATURE DEFINED TO COMPILE YOUR CODE
 * This is used by the driver to test your optimizations
 ***********************************************************************/
void make_calendars(int months[], int years[], char *calendars)
{
   for (int i = 0; i < NUM_CALS; i++)
      display(months[i], years[i], calendars + i * CAL_LENGTH);
}

