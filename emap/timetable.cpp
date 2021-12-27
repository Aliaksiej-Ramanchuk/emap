#include <iostream>
#include "timetable.h"

using std::cin;
using std::cout;

void timetable()
{
    system("CLS");

    cout << "\n ������� �������.\n";

    int choice = 0;
    std::string choiceInput = "";

    while (true)
    {
        cout << "\n �������, �� �� ����� ����� ������� ������� �������:\n";
        cout << "  1 ��> ����������\n";
        cout << "  2 ��> ������\n";
        cout << "  3 ��> ������\n";
        cout << "  4 ��> ������\n";
        cout << "  5 ��> ������\n";
        cout << "  6 ��> ������\n";
        cout << "  7 ��> �� ����� �������\n";
        cout << "  8 ��> �������� � ������� ����\n";
        cout << "  9 ��> ������ � ��������\n";

        while (true)
        {
            getline(cin, choiceInput);

            try
            {
                for (char ch : choiceInput)
                {
                    if (!isdigit(ch)) {
                        throw std::out_of_range("����� ������ ���� ����� ����");
                    }
                }

                choice = stoi(choiceInput);

                if ((choice < 1) || (choice > 9)) {
                    throw std::out_of_range("����� ������ ���� �� 1 �� 9");
                }

                break;
            }
            catch (...) {
                cout << " ���������� ����. ����������� ���� ���:\n";
            }
        }

        switch (choice)
        {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            showTimetable(choice - 1);
            break;
        case 8:
            return;
        case 9:
            exit(0);
        default:
            cout << "�� �� ������ ������ ���� �����.\n";
            break;
        }
    }
}

void showTimetable(unsigned day)
{
    int iDay = 0, iDaysCount = 0;

    if (day < WORKING_DAYS_NUMBER)
    {
        iDay = day;
        iDaysCount = iDay + 1;
    }
    else
    {
        iDay = 0;
        iDaysCount = WORKING_DAYS_NUMBER;
    }
    
    for (; iDay < iDaysCount; iDay++)
    {
        cout << "\n  " << WORKING_DAYS[iDay] << "\n";
        cout << " +=================+=============================================================================================+\n";
        cout << " |                 |                                           ������                                           |\n";
        cout << " |     ������     +----------------------------------------------+----------------------------------------------+\n";
        cout << " |                 |                  �������� 1                  |                  �������� 2                  |\n";
        cout << " +=================+==============================================+==============================================+\n";

        cout << TIMETABLES_FOR_DAYS[iDay];
    }
}