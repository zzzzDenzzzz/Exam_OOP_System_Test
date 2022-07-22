#include "Admin.h"

Admin::Admin(const string login, const string password) : Guest(login, password)
{
}

ostream &operator<<(ostream &os, User &obj) {
	os << "�����: " << obj.getLogin() << "\n";
	os << "���: " << obj.getName() << " | �������: " << obj.getSurname() << " | �������: " << obj.getPhone() << "\n";
	cout << "���� ������:\n";
	for (auto el : obj.mark)
	{
		os << setw(10) << left << el.first << " | " << el.second << "\n";
	}
	cout << "���������� �������:\n";
	for (auto el : obj.correct_count)
	{
		os << setw(10) << left << el.first << " | " << el.second << "\n";
	}
	os << "������� ���������� �������: \n";
	for (auto el : obj.percent)
	{
		os << setw(10) << left << el.first << " | " << el.second << "%" << endl;
	}
	return os;
}