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
        cout << "  (C)ALCULATE �> ��������� �������� ��������������� ���������\n";
        cout << "  (M)ENU ������> ������� � ������� ����\n";
        cout << "  E(X)IT ������> ����� �� ���������\n";

        do {
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            answer = toupper(answer);

            switch (answer)
            {
            case 'C':
                cout << "\n ������� �������������� ���������:\n";
                // ���� ������ ���� while �� main
                break;
            case 'M':
                return;
            case 'X':
                exit(0);
            default:
                cout << " ������������ ����. ������� ��� ���:\n";
                break;
            }
        } while (answer != 'C');
    } while (true);
}

// ���� ������ ���������� ���� �������