#define _CRT_SECURE_NO_WARNINGS
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80

#include <cstdio>
#include "ctime"
#include "calendar.h"
#include "Windows.h"
#include "conio.h"
#include "fstream"
#include "string"
#include "iostream"
#include "filesystem"

using namespace std;
namespace fs = filesystem;

static int year, month;
static int input;

void make_plan(void)
{
    int day = 0;
    string plan = "";
    cout << "날짜를 입력해주세요 : ";
    cin >> day;

    if (day >= 1 && day <= 31)
    {
        string filename = to_string(year) + "." + to_string(month) + ".txt";
        ofstream out(filename, ios::app);
        cout << "일정을 입력해주세요 : ";
        cin >> plan;
        if (out.is_open())
            out << day << "일" << "\t" << plan << " ";
        getline(cin.ignore(), plan);
        out << plan << endl;

        out.close();
    }
    else
    {
        cout << "잘못 입력하셨습니다.";
    }
}

void show_plan(void)
{
    string targetFilename = to_string(year) + "." + to_string(month) + ".txt"; // 사용자가 지정한 텍스트 파일 이름
    string currentDir = "."; // 현재 디렉토리

    // 디렉토리 내 파일 확인
    while (1)
    {
        for (const auto& entry : fs::directory_iterator(currentDir))
        {
            if (entry.is_regular_file())
            {
                string filename = entry.path().filename().string();
                if (filename == targetFilename)
                {
                    cout << "\n==============================\n";
                    cout << "<" + to_string(month) + "월의 일정>\n";
                    ifstream file(filename);
                    string line;
                    while (getline(file, line))
                    {
                        cout << line << endl;
                    }
                    file.close();
                }
            }
        }
        break;
    }
}

void show_calendar(void)//달력을 출력해주는 함수
{   
    printf("=============================\n");
    printf("          %4d년 %2d월\n", year, month);
    printf("=============================\n");
    printf("  일  월  화  수  목  금  토 \n");
    printf("=============================\n");

    // 1일이 출력될 요일의 위치를 맞추기 위해 1일의 요일만큼 반복하며 빈 칸을 출력
    for (int i = 0; i < weekDay(year, month, 1); i++) {
        printf("    ");
    }

    // 1일부터 달력을 출력할 달의 마지막 날짜까지 반복하며 날짜를 출력
    for (int i = 1; i <= lastDay(year, month); i++) {
        printf(" %2d ", i);

        // 출력할 날짜(i)가 토요일이고 그 달의 마지막 날짜가 아니면 줄을 바꿈
        if (weekDay(year, month, i) == 6 && i != lastDay(year, month)) {
            printf("\n");
        }
    }
    show_plan();
    printf("\n=============================\n");
}

void Present(void)//오늘이 포함된 달력을 열어준다.
{
    system("cls");
    //현재 시간을 불러오기
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    //localtime : 1970년 1월 1일 0시 0분 0초를 기준으로
    //초를 계산하여 현재 시간을 판별한다.


    //현재 달력 출력
    

    year = t->tm_year + 1900;//현재의 연도를 year에 입력
    month = t->tm_mon + 1;//현재의 달을 month에 입력

    while (1)
    {
        if (year == t->tm_year+1900&&month == t->tm_mon+1)
        {
            printf("<<    \t   이번달         >>\n");
        }
        else
            printf("<<\t\t\t  >>\n");
        show_calendar();
        printf("(이전달 : ← / 다음달 : →)\n(메뉴로 돌아가기 : ↑)\n(일정 등록하기 : ↓)\n");
        input = _getch();
        if (input == RIGHT)
        {
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
                
            }
        }
        else if (input == LEFT)
        {
            month--;
            if (month < 1)
            {
                month = 12;
                year--;
                if (year < 1)
                {
                    year = 1;
                    month = 1;
                }
            }
        }
        else if (input == UP)
        {
            system("cls");
            break;
        }
        else if (input == DOWN)
        {
            make_plan();
        }
        system("cls");
    }
    
}
int Search(void)
{
    system("cls");
    // 사용자로부터 년도와 월을 입력 받음
    printf("출력할 달력의 년도와 월을 입력하세요 (년도 월, 종료하려면 0 입력): ");
    scanf_s("%d", &year);

    // 0이 입력되면 프로그램 종료
    if (year == 0) {
        printf("프로그램을 종료합니다.\n");
        return 0;
    }

    scanf_s("%d", &month);

    show_calendar();
    system("pause");
}



void Menu(void)
{
    int num;

    while (1)
    {
        system("cls");
        printf("1. 현재 달력\n");
        printf("2. 달력 검색하기\n");
        printf("메뉴를 고르시오 : ");
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            Present();
            break;
        case 2:
            Search();
            break;
        default:
            continue;
        }
    }
}

int main(void)
{
    Menu();
}
