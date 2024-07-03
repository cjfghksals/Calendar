// calendar.h

#ifndef CALENDAR_H
#define CALENDAR_H

// �⵵�� �Ѱܹ޾� ����/����� �Ǵ��� �����̸� true(1), ����̸� false(0)�� �����ϴ� �Լ�
bool isLeapYear(int year);

// ��, ���� �Ѱܹ޾� �� ���� ������ ��¥�� �����ϴ� �Լ�
int lastDay(int year, int month);

// ��, ��, ���� �Ѱܹ޾� 1�� 1�Ϻ��� ���� ��¥�� ����� �����ϴ� �Լ�
int totalDay(int year, int month, int day);

// ��, ��, ���� �Ѱܹ޾� ������ �����ϴ� �Լ�
int weekDay(int year, int month, int day);

#endif // CALENDAR_H
