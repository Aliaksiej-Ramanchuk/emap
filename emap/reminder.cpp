#include <iomanip>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#define NOMINMAX
#include <Windows.h>
#include "reminder.h"

using namespace std;

static vector<unsigned> g_remIDs;
static vector<string> g_remMsgs;
static vector<tm> g_remTimes;
static unsigned long long g_remsCount = 0;

static bool g_remToSetExists = false;
static time_t g_deltaTimeToSet = 0;
static string g_msgToSet = "";

static bool g_toShowMenu = true;
static mutex g_mtx;

void reminder()
{
	system("CLS");
	cout << "\n �����������.\n";

	do
	{
		if (g_toShowMenu)
		{
			cout << "\n �������:\n";
			cout << "  1 ��> �������� ���� ������\n";
			cout << "  2 ��> ������� ������\n";
			cout << "  3 ��> �������� ��� ������� �������\n";
			cout << "  4 ��> �������� � ������� ����\n";
			cout << "  5 ��> ������ � ��������\n";

			char answer;
			do {
				cin >> answer;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				switch (answer)
				{
				case '1':
					setRem();
					break;
				case '2':
					delRem();
					break;
				case '3':
				{
					g_mtx.lock();
					if (g_remsCount)
					{
						cout << "\n ��� ������� �������:\n";

						for (int i = 0; i < g_remsCount; i++) {
							cout << "  " << g_remMsgs[i] << "\t(��" <<
								" " << setw(2) << setfill('0') << g_remTimes[i].tm_mday <<
								"." << setw(2) << setfill('0') << g_remTimes[i].tm_mon + 1 <<
								"." << setw(2) << setfill('0') << g_remTimes[i].tm_year + 1900 <<
								" " << setw(2) << setfill('0') << g_remTimes[i].tm_hour <<
								":" << setw(2) << setfill('0') << g_remTimes[i].tm_min <<
								":" << setw(2) << setfill('0') << g_remTimes[i].tm_sec << ")\n";
						}
					}
					else {
						cout << "\n ������� �� ����������.\n";
					}
					g_mtx.unlock();
				}
					break;
				case '4':
					return;
				case '5':
					exit(0);
				default:
					cout << " ���������� ����. ����������� ���� ���:\n";
					break;
				}
			} while ((answer < '1') || (answer > '5'));
		}
	} while (true);
}

void setRem()
{
	if (g_remsCount > MAX_REMS_COUNT) {
		cout << "\n ��� ��������� ����������� ��������� �������.\n";
	}
	else
	{
		string hmsInput;
		bool hmsInputIsOK = true;

		cout << "\n ���� ����� ����� ������ ���������� �����������?\n";
		unsigned long long hours;
		do
		{
			getline(cin, hmsInput);
			try
			{
				if (stod(hmsInput) < 0) throw out_of_range("hours value is  too low");
				if (stod(hmsInput) > 10000) throw out_of_range("hours value is too hign");
				hours = stoull(hmsInput);
				hmsInputIsOK = true;
			}
			catch (...)
			{
				hmsInputIsOK = false;
				cout << " ���������� ����. ����������� ���� ���:\n";
			}
		} while (!hmsInputIsOK);

		unsigned long long mins;
		cout << "\n ���� ����� ���� ������ ���������� �����������?\n";
		do
		{
			getline(cin, hmsInput);
			try
			{
				if (stod(hmsInput) < 0) throw out_of_range("mins value is  too low");
				if (stod(hmsInput) > 10000) throw out_of_range("mins value is too hign");
				mins = stoull(hmsInput);
				hmsInputIsOK = true;
			}
			catch (...)
			{
				hmsInputIsOK = false;
				cout << " ���������� ����. ����������� ���� ���:\n";
			}
		} while (!hmsInputIsOK);

		unsigned long long secs;
		cout << "\n ���� ����� ������ ������ ���������� �����������?\n";
		do
		{
			getline(cin, hmsInput);
			try
			{
				if (stod(hmsInput) < 0) throw out_of_range("secs value is  too low");
				if (stod(hmsInput) > 10000) throw out_of_range("secs value is too hign");
				secs = stoull(hmsInput);
				hmsInputIsOK = true;
			}
			catch (...)
			{
				hmsInputIsOK = false;
				cout << " ���������� ����. ����������� ���� ���:\n";
			}
		} while (!hmsInputIsOK);

		g_deltaTimeToSet = hours * 3600 + mins * 60 + secs;

		cout << "\n ������� ����� �������:\n";
		do
		{
			getline(cin, g_msgToSet);
		} while (g_msgToSet.empty());

		g_toShowMenu = false;
		g_remToSetExists = true;
	}
}

void delRem()
{
	if (g_remsCount)
	{
		const vector<unsigned> STATED_REM_IDs{ g_remIDs };
		const unsigned long long STATED_REMS_COUNT{ g_remsCount };
		unsigned remToDel = 0;

		cout << "\n �������, �� ������ �������:\n";

		for (int i = 0; i < STATED_REMS_COUNT; i++) {
			cout << "  " << i + 1 << " ��> " << g_remMsgs[i] << " (��" <<
				" " << setw(2) << setfill('0') << g_remTimes[i].tm_mday <<
				"." << setw(2) << setfill('0') << g_remTimes[i].tm_mon + 1 <<
				"." << setw(2) << setfill('0') << g_remTimes[i].tm_year + 1900 <<
				" " << setw(2) << setfill('0') << g_remTimes[i].tm_hour <<
				":" << setw(2) << setfill('0') << g_remTimes[i].tm_min <<
				":" << setw(2) << setfill('0') << g_remTimes[i].tm_sec << ")\n";
		}
		cout << "  " << STATED_REMS_COUNT + 1 << " ��> �������� � ���� ������������\n";
		cout << "  " << STATED_REMS_COUNT + 2 << " ��> ������ � ��������\n";

		string remToDelInput;
		do
		{
			getline(cin, remToDelInput);
			try
			{
				if ((stod(remToDelInput) < 1) || (stod(remToDelInput) > STATED_REMS_COUNT + 3.0)) {
					throw out_of_range("incorrect choice");
				}

				remToDel = stoul(remToDelInput);

				if ((remToDel < 1) || (remToDel > STATED_REMS_COUNT + 2.0)) {
					throw out_of_range("incorrect choice");
				}

				break;
			}
			catch (...)
			{
				cout << " ���������� ����. ����������� ���� ���:\n";
			}
		} while (true);

		if (remToDel == STATED_REMS_COUNT + 1) {
			return;
		}
		else if (remToDel == STATED_REMS_COUNT + 2) {
			exit(0);
		}
		else 
		{
			g_mtx.lock();
			if ((remToDel <= g_remsCount) && (STATED_REM_IDs[remToDel - 1] == g_remIDs[remToDel - 1]))
			{
				KillTimer(NULL, g_remIDs[remToDel - 1]);
				g_remIDs.erase(g_remIDs.begin() + remToDel - 1);
				g_remMsgs.erase(g_remMsgs.begin() + remToDel - 1);
				g_remTimes.erase(g_remTimes.begin() + remToDel - 1);
				g_remsCount--;

				cout << " \n ������ ��������.\n";
			}
			else {
				cout << "\n ���� ������ ��� �������� ���������� (��������� ����� �������).\n";
			}
			g_mtx.unlock();
		}
	}
	else {
		cout << "\n ��������� ������� ������, �� ������� ����.\n";
	}
}

void checkRem()
{
	MSG msg;

	while (true)
	{
		if (g_remToSetExists)
		{
			g_remToSetExists = false;
			unsigned id = SetTimer(NULL, NULL, (unsigned)g_deltaTimeToSet * 1000, remCallback);

			time_t timeToSet = time(NULL) + g_deltaTimeToSet;
			tm timeinfo;
			localtime_s(&timeinfo, &timeToSet);

			g_remIDs.push_back(id);
			g_remMsgs.push_back(g_msgToSet);
			g_remTimes.push_back(timeinfo);

			g_remsCount++;
			g_toShowMenu = true;
		}

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CALLBACK remCallback(HWND hwnd, UINT uMsg, UINT timerId, DWORD dwTime)
{
	KillTimer(hwnd, timerId);

	string thisRemMsg = " �� �� ������ ������ ����� ������������.\n :/";

	g_mtx.lock();
	for (int i = 0; i < g_remsCount; i++)
	{
		if (g_remIDs[i] == timerId)
		{
			thisRemMsg = g_remMsgs[i];
			g_remIDs.erase(g_remIDs.begin() + i);
			g_remMsgs.erase(g_remMsgs.begin() + i);
			g_remTimes.erase(g_remTimes.begin() + i);
			g_remsCount--;
			break;
		}
	}
	g_mtx.unlock();

	MessageBeep(MB_OK);
	MessageBoxA(hwnd, thisRemMsg.c_str(), "����̲�!", MB_OK | MB_ICONINFORMATION);

	return;
}