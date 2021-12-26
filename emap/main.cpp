#include "number_calculator.h"  // �����������
#include "string_calculator.h"  // ������� �����������
#include "dozenal_mul_table.h"	// �������������� ������ ��������
#include "current_date_time.h"  // �������
#include "timetable.h"          // ������� �������
#include "bin_dec_converter.h"  // BIN/DEC ���������
#include "reminder.h"			// �����������
#include "caesar_endecoder.h"	// ��������-���������� ������

#include <iostream>
#include <string>
#include <thread>
#define NOMINMAX
#include <Windows.h>

int main()
{
	using std::cin;
	using std::cout;
	
	system("chcp 1251 > nul");		// Windows-1251

	srand((unsigned)time(NULL));	// ������

	std::thread th(checkRem);		// �������� �������
	th.detach();

	std::string answer;
	bool answerIsOK = true;
	
	do
	{
		system("CLS");
		cout << "\n ������� ����.\n";

		cout << "\n ������� ������� ������������ ��������:\n";
		cout << "  1 ���> �����������\n";
		cout << "  2 ���> ������� �����������\n";
		cout << "  3 ���> �������������� ������ ��������\n";
		cout << "  4 ���> �������\n";
		cout << "  5 ���> ������� �������\n";
		cout << "  6 ���> BIN/DEC ���������\n";
		cout << "  7 ���> �����������\n";
		cout << "  8 ���> ��������-���������� ������\n";
		cout << "  9 ���> ������� ���� � ���������������\n";
		cout << "  10 ��> ������ � ��������\n";

		do
		{
			answerIsOK = true;
			getline(cin, answer);

			if (answer == "1") {
				numberCalculator();
			}
			else if (answer == "2") {
				stringCalculator();
			}
			else if (answer == "3") {
				dozenalMulTable();
			}
			else if (answer == "4") {
				currentDateTime();
			}
			else if (answer == "5") {
				timetable();
			}
			else if (answer == "6") {
				binDecConverter();
			}
			else if (answer == "7") {
				reminder();
			}
			else if (answer == "8") {
				caesarEnDecoder();
			}
			else if (answer == "9") {
				ShellExecuteA(GetConsoleWindow(), "open", "..\\emap.html", NULL, NULL, SW_SHOWDEFAULT);
			}
			else if (answer == "10") {
				break;
			}
			else
			{
				answerIsOK = false;
				cout << " ���������� ����. ����������� ���� ���:\n";
			}
		} while (!answerIsOK);
	} while (answer != "10");

	return 0;
}



// ��� ��� �. ��������, �. ���������, �. ������,  �. ������, �. ������, �. ֳ�����. 