#include "number_calculator.h"  // ˳���� �����������
#include "string_calculator.h"  // ������� �����������
#include "current_date_time.h"  // �������
#include "timetable.h"          // ������� �������
#include "bin_dec_converter.h"  // BIN/DEC ���������
#include "reminder.h"			// �����������
#include "caesar_endecoder.h"	// ��������-���������� ������

#include <iostream>
#include <thread>
#define NOMINMAX
#include <Windows.h>

int main()
{
	using std::cin;
	using std::cout;

	system("chcp 1251 > nul");  // Windows-1251

	std::thread th(checkRem);
	th.detach();

	char answer;
	do
	{
		system("CLS");
		cout << "\n ������� ����.\n";

		cout << "\n ������� ������� ������������ ��������:\n";
		cout << "  1 ��> ����� �����������\n";
		cout << "  2 ��> ������� �����������\n";
		cout << "  3 ��> �������\n";
		cout << "  4 ��> ������� �������\n";
		cout << "  5 ��> BIN/DEC ���������\n";
		cout << "  6 ��> �����������\n";
		cout << "  7 ��> ��������-���������� ������\n";
		cout << "  8 ��> ������� ���� � ���������������\n";
		cout << "  9 ��> ������ � ��������\n";

		do
		{
			cin >> answer;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			answer = toupper(answer);

			switch (answer)
			{
			case '1': numberCalculator();
				break;
			case '2': stringCalculator();
				break;
			case '3': currentDateTime();
				break;
			case '4': timetable();
				break;
			case '5': binDecConverter();
				break;
			case '6': reminder();
				break;
			case '7': caesarEnDecoder();
				break;
			case '8': ShellExecuteA(GetConsoleWindow(), "open", "..\\emap.html", NULL, NULL, SW_SHOWDEFAULT);
				break;
			case '9':
				break;
			default:
				cout << " ���������� ����. ����������� ���� ���:\n";
				break;
			}
		} while ((answer < '1') || (answer > '9'));
	} while (answer != '9');

	return 0;
}



// ��� ��� �. ��������, �. ���������, �. ������,  �. ������, �. ������, �. ֳ�����. 