#include "test_func1.h"
#include <iostream>
using namespace std;

void testFunc1()
{
    char answer;
    do
    {
        cout << "\n ���-�� ����������.\n";  // ��� ����������� ������� ������ �������

        cout << "\n ��������:\n";
        cout << "  (D)O SMTH �> ������� ���-������\n";
        cout << "  (M)ENU ����> ������� � ������� ����\n";
        cout << "  E(X)IT ����> ����� �� ���������\n";

        do {
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            answer = toupper(answer);

            switch (answer)
            {
            case 'D':
                break;
            case 'M':
                break;
            case 'X':
                exit(0);
            default:
                cout << " ������������ ����. ������� ��� ���:\n";
                break;
            }
        } while ((answer != 'D') && (answer != 'M') && (answer != 'X'));
    } while (answer != 'M');
}