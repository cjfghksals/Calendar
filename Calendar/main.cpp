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
    cout << "��¥�� �Է����ּ��� : ";
    cin >> day;

    if (day >= 1 && day <= 31)
    {
        string filename = to_string(year) + "." + to_string(month) + ".txt";
        ofstream out(filename, ios::app);
        cout << "������ �Է����ּ��� : ";
        cin >> plan;
        if (out.is_open())
            out << day << "��" << "\t" << plan << " ";
        getline(cin.ignore(), plan);
        out << plan << endl;

        out.close();
    }
    else
    {
        cout << "�߸� �Է��ϼ̽��ϴ�.";
    }
}

void show_plan(void)
{
    string targetFilename = to_string(year) + "." + to_string(month) + ".txt"; // ����ڰ� ������ �ؽ�Ʈ ���� �̸�
    string currentDir = "."; // ���� ���丮

    // ���丮 �� ���� Ȯ��
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
                    cout << "<" + to_string(month) + "���� ����>\n";
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

void show_calendar(void)//�޷��� ������ִ� �Լ�
{   
    printf("=============================\n");
    printf("          %4d�� %2d��\n", year, month);
    printf("=============================\n");
    printf("  ��  ��  ȭ  ��  ��  ��  �� \n");
    printf("=============================\n");

    // 1���� ��µ� ������ ��ġ�� ���߱� ���� 1���� ���ϸ�ŭ �ݺ��ϸ� �� ĭ�� ���
    for (int i = 0; i < weekDay(year, month, 1); i++) {
        printf("    ");
    }

    // 1�Ϻ��� �޷��� ����� ���� ������ ��¥���� �ݺ��ϸ� ��¥�� ���
    for (int i = 1; i <= lastDay(year, month); i++) {
        printf(" %2d ", i);

        // ����� ��¥(i)�� ������̰� �� ���� ������ ��¥�� �ƴϸ� ���� �ٲ�
        if (weekDay(year, month, i) == 6 && i != lastDay(year, month)) {
            printf("\n");
        }
    }
    show_plan();
    printf("\n=============================\n");
}

void Present(void)//������ ���Ե� �޷��� �����ش�.
{
    system("cls");
    //���� �ð��� �ҷ�����
    time_t timer;
    struct tm* t;
    timer = time(NULL);
    t = localtime(&timer);
    //localtime : 1970�� 1�� 1�� 0�� 0�� 0�ʸ� ��������
    //�ʸ� ����Ͽ� ���� �ð��� �Ǻ��Ѵ�.


    //���� �޷� ���
    

    year = t->tm_year + 1900;//������ ������ year�� �Է�
    month = t->tm_mon + 1;//������ ���� month�� �Է�

    while (1)
    {
        if (year == t->tm_year+1900&&month == t->tm_mon+1)
        {
            printf("<<    \t   �̹���         >>\n");
        }
        else
            printf("<<\t\t\t  >>\n");
        show_calendar();
        printf("(������ : �� / ������ : ��)\n(�޴��� ���ư��� : ��)\n(���� ����ϱ� : ��)\n");
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
    // ����ڷκ��� �⵵�� ���� �Է� ����
    printf("����� �޷��� �⵵�� ���� �Է��ϼ��� (�⵵ ��, �����Ϸ��� 0 �Է�): ");
    scanf_s("%d", &year);

    // 0�� �ԷµǸ� ���α׷� ����
    if (year == 0) {
        printf("���α׷��� �����մϴ�.\n");
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
        printf("1. ���� �޷�\n");
        printf("2. �޷� �˻��ϱ�\n");
        printf("�޴��� ���ÿ� : ");
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
