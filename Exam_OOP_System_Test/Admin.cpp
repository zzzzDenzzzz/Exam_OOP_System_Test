#include "Admin.h"

Admin::Admin(const string login, const string password) : Guest(login, password)
{
}

ostream &operator<<(ostream &os, User &obj) {
	os << "Логин: " << obj.getLogin() << "\n";
	os << "Имя: " << obj.getName() << " | Фамилия: " << obj.getSurname() << " | Телефон: " << obj.getPhone() << "\n";
	cout << "Ваши оценки:\n";
	for (auto el : obj.mark)
	{
		os << setw(10) << left << el.first << " | " << el.second << "\n";
	}
	cout << "Правильных ответов:\n";
	for (auto el : obj.correct_count)
	{
		os << setw(10) << left << el.first << " | " << el.second << "\n";
	}
	os << "Процент правильных ответов: \n";
	for (auto el : obj.percent)
	{
		os << setw(10) << left << el.first << " | " << el.second << "%" << endl;
	}
	return os;
}