#include <iostream>
#include <thread>
#include <Windows.h>
#include <chrono>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include "reminder.h"

using namespace std;
using namespace std::chrono;
typedef unsigned long long ull;

void reminder() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "ru");

	static string message;
	bool call = true;
	int menuItem;

	ull h = 0;
	ull m = 0;

	//auto now = zoned_time{ current_zone(), system_clock::now() }.get_local_time();
	//auto time_now = now - floor<days>(now);//������� ����� ��� ����� ��������
	//��� ��������� �������� ������� ����� chrono

	while (call) {
		cout << "1.������� ����� �����������\n";
		cout << "2.������� � ������� ����\n";
		cout << "3.����� �� ���������\n";
		cin >> menuItem;
		switch (menuItem)
		{
		case 1:
			cout << "���������� �����, ����� ������� ������ ��������� �����������" << "\n"
				<< "���� : ";
			cin >> h;
			cout << "������:  ";
			cin >> m;

			cout << "����� �����������: ";
			cin.ignore(32767, '\n');
			getline(cin, message);

			this_thread::sleep_for(chrono::hours(h));
			this_thread::sleep_for(chrono::seconds(m));//�������, ��� ������, �� ����������� ������� � ���
			Beep(432, 300);

			cout << message << "\n";

		case 2:
			break;
		case 3:
			call = false;
			break;
		default:
			cout << "�����?\n";
			break;
		}
	}
}