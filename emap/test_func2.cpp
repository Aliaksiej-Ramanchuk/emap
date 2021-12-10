#include "test_func2.h"
#include <iostream>
using namespace std;

void testFunc2()
{
    system("CLS");

    char answer;
    do
    {
        cout << "\n ��������:\n";
        cout << "  (D)O SMTH ������> ������� ���-������\n";
        cout << "  DO SMTH (E)LSE �> ������� ���-������ ������\n";
        cout << "  (M)ENU ���������> ������� � ������� ����\n";
        cout << "  E(X)IT ���������> ����� �� ���������\n";

        do {
            cin >> answer;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            answer = toupper(answer);

            switch (answer)
            {
            case 'D': doSomething();
                break;
            case 'E': doSomethingElse();
                break;
            case 'M':
                break;
            case 'X':
                exit(0);
            default:
                cout << " ������������ ����. ������� ��� ���:\n";
                break;
            }
        } while ((answer != 'D') && (answer != 'E') && (answer != 'M') && (answer != 'X'));
    } while (answer != 'M');
}

void doSomething()
{
    cout << "\n ���-�� ����������.\n";          // ��� ����������� ��������� �������
}

void doSomethingElse()
{
    cout << "\n ���������� ���-�� ������.\n";   // ��� ����������� ������ ��������� �������
}