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

	int choice = 0;
	std::string choiceInput = "";
	
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

				if ((choice < 1) || (choice > 10)) {
					throw std::out_of_range("����� ������ ���� �� 1 �� 10");
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
			numberCalculator();
			break;
		case 2:
			stringCalculator();
			break;
		case 3:
			dozenalMulTable();
			break;
		case 4:
			currentDateTime();
			break;
		case 5:
			timetable();
			break;
		case 6:
			binDecConverter();
			break;
		case 7:
			reminder();
			break;
		case 8:
			caesarEnDecoder();
			break;
		case 9:
			ShellExecuteA(GetConsoleWindow(), "open", "..\\emap.html", NULL, NULL, SW_SHOWDEFAULT);
			break;
		case 10:
			break;
		default:
			cout << "�� �� ������ ������ ���� �����.\n";
			break;
		}
	} while (choice != 10);

	return 0;
}



// ��� ��� �. ��������, �. ���������, �. ������,  �. ������, �. ������, �. ֳ�����. 