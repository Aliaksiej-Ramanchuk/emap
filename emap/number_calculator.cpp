#include "number_calculator.h"
#include <iostream>
// ������ ���� ������ #include
using namespace std;

void numberCalculator()
{
    system("CLS");

    cout << "\n �������� �����������.\n";
    cout << " ��������� �������� ��������� ��������������� ���������.\n";
    cout << " ������������ ������������� � ��������� ���������� + , -, *, / , () � ���������� �������� ����������.\n";
    cout << " ������������ ������������� � ��������� �������� pi � e.\n";
    cout << " ������:\n";
    cout << "         ���������: 2.5 + (3 - 4 * 5)/17\n";
    cout << "         ���������: 1.5\n";

    // ���� ������ pi � e �� main

    char answer;
    do
    {
        cout << "\n ��������:\n";
        cout << "  1 ��> ��������� �������� ��������������� ���������\n";
        cout << "  2 ��> ������� � ������� ����\n";
        cout << "  3 ��> ����� �� ���������\n";

        do {
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (answer)
            {
            case '1':
                cout << "\n ������� �������������� ���������:\n";
                // ���� ������ ���� while �� main
                break;
            case '2':
                return;
            case '3':
                exit(0);
            default:
                cout << " ������������ ����. ������� ��� ���:\n";
                break;
            }
        } while ((answer < '1') || (answer > '3'));
    } while (true);
}

// ���� ������ ���������� ���� �������