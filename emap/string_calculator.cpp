#include "string_calculator.h"
#include <iostream>
#include <string>
using namespace std;

void stringCalculator()
{
	char answer;
	do
	{
		cout << "\n ��������:\n";
		cout << "  (C)OMPARE ������> �������� ��� ������\n";
		cout << "  (F)IND SUBSTR ��> ���������� ������� ��������� � ������\n";
		cout << "  (R)EPLACE ������> �������� ��������� � ������\n";
		cout << "  COUNT (V)OWELS �> ���������� ���������� ������� � ������\n";
		cout << "  (M)ENU ���������> ������� � ������� ����\n";
		cout << "  E(X)IT ���������> ����� �� ���������\n";

		do {
			cin >> answer;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			answer = toupper(answer);

			switch (answer)
			{
			case 'C': compareStrings();
				break;
			case 'F': findSubstr();
				break;
			case 'R': replaceSubstr();
				break;
			case 'V': countVowels();
				break;
			case 'M':
				break;
			case 'X':
				exit(0);
			default:
				cout << " ������������ ����. ������� ��� ���:\n";
				break;
			}
		} while ((answer != 'C') && (answer != 'F') && (answer != 'R') && (answer != 'V') && (answer != 'M') && (answer != 'X'));
	} while (answer != 'M');
}

void compareStrings()
{
	string firstString, secondString;

	cout << "\n ������� ������ ������:\n";
	getline(cin, firstString);

	cout << "\n ������� ������ ������:\n";
	getline(cin, secondString);

	if (firstString == secondString) {
		cout << "\n ������ �����.\n";
	}
	else
	{
		if (firstString > secondString) {
			cout << "\n ������ ������ ������ ������.\n";
		}
		else {
			cout << "\n ������ ������ ������ ������.\n";
		}
	}
}

void findSubstr()
{
	string str, subString;

	cout << "\n ������� ������, � ������� ����� �������������� ����� ���������:\n";
	getline(cin, str);
	int firstStringLength = str.length();

	cout << "\n ������� ���������:\n";
	getline(cin, subString);
	int secondStringLength = subString.length();

	int pos = str.find(subString);

	if (pos == string::npos) {
		cout << "\n ������ �� �������� ������ ���������.\n";
	}
	else {
		cout << "\n ������� ��������� � ������: " << pos << endl;
	}
}

void replaceSubstr()
{
	string str, subStrToReplace, subStrToReplaceWith;
	int pos = 0;

	cout << "\n ������� ������, � ������� ����� �������� ���������:\n";
	getline(cin, str);

	char answer;
	do
	{
		cout << "\n ������� ���������, ������� ����� ��������:\n";
		getline(cin, subStrToReplace);

		pos = str.find(subStrToReplace);

		if (pos == string::npos)
		{
			cout << "\n ������ �� �������� ������ ���������. ��������:\n";
			cout << "  (N)EW SUBSTR �> ������ ����� ���������\n";
			cout << "  (M)ENU �������> ������� � ���� ������������ ��� �����\n";
			cout << "  E(X)IT �������> ����� �� ���������\n";

			do {
				cin >> answer;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				answer = toupper(answer);

				switch (answer)
				{
				case 'N':
					break;
				case 'M':
					return;
				case 'X':
					exit(0);
				default:
					cout << " ������������ ����. ������� ��� ���:\n";
					break;
				}
			} while (answer != 'N');
		}
	} while (pos == string::npos);

	cout << "\n ������� ���������, �� ������� ����� ��������:\n";
	getline(cin, subStrToReplaceWith);

	str.replace(pos, subStrToReplace.length(), subStrToReplaceWith);

	cout << "\n ������ ����� ������ ���������:\n";
	cout << str << endl;
}

void countVowels()
{
	string str;

	cout << "\n ������� ������, � ������� ����� ��������� �������:\n";
	getline(cin, str);
	int strLength = str.length();

	int nVowels = 0;

	for (char letter : str)
	{
		if (
			(letter == 'A') || (letter == 'E') || (letter == 'I') || (letter == 'O') || (letter == 'U') || (letter == 'Y') ||
			(letter == 'a') || (letter == 'e') || (letter == 'i') || (letter == 'o') || (letter == 'u') || (letter == 'y') ||
			(letter == '�') || (letter == '�') || (letter == '�') || (letter == '�') || (letter == '�') ||
			(letter == '�') || (letter == '�') || (letter == '�') || (letter == '�') || (letter == '�') ||
			(letter == '�') || (letter == '�') || (letter == '�') || (letter == '�') || (letter == '�') ||
			(letter == '�') || (letter == '�') || (letter == '�') || (letter == '�') || (letter == '�')
			)
		{
			nVowels++;
		}
	}

	cout << "\n ���������� ������� � ������: " << nVowels << endl;
}