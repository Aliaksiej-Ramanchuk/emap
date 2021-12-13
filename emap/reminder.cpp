#include <conio.h>
#include <iomanip>
#include <iostream>
#include <string>
#define NOMINMAX
#include <Windows.h>
#include "reminder.h"

using namespace std;

void reminder()
{
	static bool callMenu = true;
	static time_t remindTime;
	static string message;
	unsigned long long hours;
	unsigned long long mins;
	unsigned long long secs;
	time_t now;
	long long deltaTime;

	//auto now = zoned_time{ current_zone(), system_clock::now() }.get_local_time();
	//auto time_now = now - floor<days>(now);//������� ����� ��� ����� ��������
	//��� ��������� �������� ������� ����� chrono

	do
	{
		if (callMenu)
		{
			system("CLS");
			cout << "\n �����������.\n";

			if (!message.empty())
			{
				cout << "\n �����������: " << message << "\n";
				message.clear();
			}

			cout << "\n ��������:\n";
			cout << "  1 ��> ������� ����� �����������\n";
			cout << "  2 ��> ������� � ������� ����\n";
			cout << "  3 ��> ����� �� ���������\n";

			char answer;
			do {
				cin >> answer;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				switch (answer)
				{
				case '1':
				{
					cout << "\n ����� ������� ����� ������ ��������� �����������?\n";
					string hmsInput;
					bool hmsInputIsOK = true;
					do
					{
						getline(cin, hmsInput);
						try
						{
							hours = stoul(hmsInput);
							if (hours > 23) {
								throw out_of_range("����� ����� �� ����� ���� ������ 23");
							}
							hmsInputIsOK = true;
						}
						catch (...)
						{
							hmsInputIsOK = false;
							cout << " ������������ ����. ������� ��� ���:\n";
						}
					} while (!hmsInputIsOK);

					cout << "\n ����� ������� ����� ������ ��������� �����������?\n";
					do
					{
						getline(cin, hmsInput);
						try
						{
							mins = stoul(hmsInput);
							if (mins > 59) {
								throw out_of_range("����� ����� �� ����� ���� ������ 59");
							}
							hmsInputIsOK = true;
						}
						catch (...)
						{
							hmsInputIsOK = false;
							cout << " ������������ ����. ������� ��� ���:\n";
						}
					} while (!hmsInputIsOK);

					cout << "\n ����� ������� ������ ������ ��������� �����������?\n";
					do
					{
						getline(cin, hmsInput);
						try
						{
							secs = stoul(hmsInput);
							if (mins > 59) {
								throw out_of_range("����� ����� �� ����� ���� ������ 59");
							}
							hmsInputIsOK = true;
						}
						catch (...)
						{
							hmsInputIsOK = false;
							cout << " ������������ ����. ������� ��� ���:\n";
						}
					} while (!hmsInputIsOK);

					cout << "\n ������� ����� �����������:\n";
					getline(cin, message);

					remindTime = time(0) + hours * 3600 + mins * 60 + secs;
					callMenu = false;
				}
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
		}
		while (!_kbhit())
		{
			now = time(0);
			if (remindTime <= now)
			{
				callMenu = true;
				break;
			}

			system("CLS");
			cout << "\n �����������.\n";
			cout << " ��� �������� � ������� ���� ������� ����� �������.\n";

			deltaTime = (long long)(remindTime - now);
			hours = deltaTime / 3600;
			mins = deltaTime / 60 - hours * 60;
			secs = deltaTime - hours * 3600 - mins * 60;
			cout << "\n    +----------+";
			cout << "\n    | " << setw(2) << setfill('0') << hours;
			cout << ":" << setw(2) << setfill('0') << mins;
			cout << ":" << setw(2) << setfill('0') << secs << " |";
			cout << "\n    +----------+";

			Sleep(500);
		}
		if (!callMenu)
		{
			_getch();
			return;
		}
	} while (true);
}