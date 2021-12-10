#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <string>

const int WORKING_DAYS_NUMBER = 6;

const std::string WORKING_DAYS[WORKING_DAYS_NUMBER]
{ 
	(const std::string)"�����������",
	(const std::string)"�������",
	(const std::string)"�����",
	(const std::string)"�������",
	(const std::string)"�������",
	(const std::string)"�������"
};

const std::string TIMETABLES_FOR_DAYS[WORKING_DAYS_NUMBER] =
{
	// ���������� �� ����������� (�������������: ��� ������ ������)
	(
		(const std::string)" |  14:40 - 16:00  |   I �� 200-3� �������������� ������   |\n" +
		(const std::string)" |                 |   II �� 111-4 �������������� ������   |\n" +
		(const std::string)" +-----------------+-------------------+-------------------+\n" +
		(const std::string)" |  16:30 - 17:50  |   �� 221-2 ���.   |   �� 11-2 ���.    |\n" +
		(const std::string)" |                 |  ���������� ����  |  ���������� ����  |\n" +
		(const std::string)" +-----------------+-------------------+-------------------+\n"
	),

	// ����� �� ���������� ��� ������ ����
	(
		(const std::string)" +-----------------+-------------------+-------------------+\n"
	),

	(
		(const std::string)" +-----------------+-------------------+-------------------+\n"
	),

	(
		(const std::string)" +-----------------+-------------------+-------------------+\n"
	),

	(
		(const std::string)" +-----------------+-------------------+-------------------+\n"
	),

	(
		(const std::string)" +-----------------+-------------------+-------------------+\n"
	)
};

void timetable();
void showTimetable(unsigned day);	// ����� ���������� �� ������ ���

#endif