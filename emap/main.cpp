#include "number_calculator.h"  // ����������� ��� ������ � �������                                     | by ������ ������
#include "string_calculator.h"  // ����������� ��� ������ �� ��������                                   | by ��������� ��������
#include "current_date_time.h"  // ����: ����� �������� �������                                         | by ���� ������
#include "timetable.h"          // ���������� ������� �� �������� ����                                  | by ������ ��������
#include "bin_dec_converter.h"  // ������� ����� �� �������� ������� ��������� � ���������� � ��������  | by ������� ��������
#include "caesar_cipher.h"      // ��������-���������� ������                                           | by ������� ��������

#include <iostream>
#define NOMINMAX
#include <Windows.h>

int main()
{
    using std::cout;
    using std::cin;

    system("chcp 1251 > nul");  // ��� ��������� Windows-1251

    // ������� ����

    char answer;
    do
    {
        system("CLS");
        cout << "\n ������� ����.\n";

        cout << "\n �������� ������� ������������� ���������:\n";
        cout << "  1 �������> ����������� ��� ������ � �������\n";
        cout << "  2 �������> ����������� ��� ������ �� ��������\n";
        cout << "  3 �������> ����: ����� �������� �������\n";
        cout << "  4 �������> ���������� ������� �� �������� ����\n";
        cout << "  5 �������> ��������� ����� �� �������� ������� ��������� � ���������� � ��������\n";
        cout << "  6 �������> �����������\n";
        cout << "  7 �������> ��������-���������� ������\n";             // �������������� �������
        cout << "  (A)BOUT �> ������� ���� ������� � �������������\n";
        cout << "  E(X)IT ��> ����� �� ���������\n";

        do
        {
            cin >> answer;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            answer = toupper(answer);

            switch (answer)
            {
            case '1': numberCalculator();   //                             - ������ ������
                break;
            case '2': stringCalculator(); //                               - ���� ��������
                break;
            case '3': currentDateTime(); //                                - ���� ������
                break;
            case '4': timetable();  //                                     - ������ ��������
                break;
            case '5': binDecConverter(); //                                - ������� ��������
                break;
            case '6':; // �������: �����������                             - ���� ���������
                break;
            case '7': caesarCipher(); //                                   - ������� ��������
                break;
            case 'A': ShellExecuteA(GetConsoleWindow(), "open", "..\\emap.html", NULL, NULL, SW_SHOWDEFAULT);
                break;
            case 'X':
                break;
            default:
                cout << " ������������ ����. ������� ��� ���.\n";
                break;
            }
        } while (((answer < '1') || (answer > '7')) && (answer != 'A') && (answer != 'X'));
    } while (answer != 'X');

    return 0;
}