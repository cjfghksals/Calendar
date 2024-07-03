// calendar.h

#ifndef CALENDAR_H
#define CALENDAR_H

// 년도를 넘겨받아 윤년/평년을 판단해 윤년이면 true(1), 평년이면 false(0)을 리턴하는 함수
bool isLeapYear(int year);

// 년, 월을 넘겨받아 그 달의 마지막 날짜를 리턴하는 함수
int lastDay(int year, int month);

// 년, 월, 일을 넘겨받아 1월 1일부터 지난 날짜를 계산해 리턴하는 함수
int totalDay(int year, int month, int day);

// 년, 월, 일을 넘겨받아 요일을 리턴하는 함수
int weekDay(int year, int month, int day);

#endif // CALENDAR_H
