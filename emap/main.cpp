#include "bin_dec_converter.h"  // ������� ����� �� �������� ������� ��������� � ���������� � ��������
#include "string_calculator.h"  // ����������� ��� ������ �� ��������
#include "test_func1.h"         // ������ ������� (� ������ �� �����)
#include "test_func2.h"         // ������ ������� (� ������ �� �����)

#include <iostream>

int main()
{
    using std::cout;
    using std::cin;

    system("chcp 1251 > nul");  // ��� ��������� Windows-1251

    // ������� ����
    char answer;
    do
    {
        cout << "\n �������� ������� ������������� ���������:\n";
        cout << "  1 ������> ��������� ����� �� �������� ������� ��������� � ���������� � ��������\n";
        cout << "  2 ������> ����������� ��� ������ �� ��������\n";
        cout << "  3 ������> ��� �� �����������\n";
        cout << "  4 ������> ��� �� �����������\n";
        cout << "  5 ������> ��� �� �����������\n";
        cout << "  6 ������> ��� �� �����������\n";
        cout << "  7 ������> func1 (������, � ������ �� �����)\n";      // � ������ ����� �������� �� �����
        cout << "  8 ������> func2 (������, � ������ �� �����)\n";      // � ������ ����� �������� �� �����
        cout << "  E(X)IT �> ����� �� ���������\n";

        do
        {
            cin >> answer;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            answer = toupper(answer);

            switch (answer)
            {
            case '1': binDecConverter();
                break;
            case '2': stringCalculator();
                break;
            case '3':; // �������� ���� ���� �������� �������
                break;
            case '4':; // �������� ���� ���� �������� �������
                break;
            case '5':; // �������� ���� ���� �������� �������
                break;
            case '6':; // �������� ���� ���� �������� �������
                break;
            case '7': testFunc1();  // ������, � ������ �� �����
                break;
            case '8': testFunc2();  // ������, � ������ �� �����
                break;
            case 'X':
                break;
            default:
                cout << " ������������ ����. ������� ��� ���.\n";
                break;
            }
                                 // (answer > '6'), ����� ����� �������� ��������
        } while (((answer < '1') || (answer > '8')) && (answer != 'X'));
    } while (answer != 'X');

    return 0;
}