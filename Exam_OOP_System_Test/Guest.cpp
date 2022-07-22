#include "Guest.h"

Guest::Guest(string login, string password)
{
	this->login = login;
	this->password = password;
}

void Guest::setLogin(string login)
{
	this->login = login;
}

void Guest::setPassword(string password)
{
	this->password = password;
}

string Guest::getLogin() const
{
	return login;
}

string Guest::getPassword() const
{
	return password;
}

void Guest::readUserFromFile(fstream &fs)
{
	if (fs.is_open()) 
	{
		fs >> login;
		string encrypted;
		fs >> encrypted;
		password.clear();
		for (int i = 0; i < encrypted.size(); i++) {
			password.push_back(encrypted[i] - 9);
		}
	}
	else
	{
		cout << "Пользователь с таким именем не найден. Зарегистрируйтесь!\n";
	}
}

void Guest::writeUserToFile(fstream &fs)
{
	if (!fs.is_open())
	{
		cout << "Ошибка!!!";
	}
	else {
		string decrypted;
		for (int i = 0; i < password.size(); i++)
		{
			decrypted.push_back(password[i] + 9);
		}
		fs << login << " " << decrypted << "\n";
	}
}

void Guest::print() const
{
	cout << "Логин: " << login << " Пароль: " << password << "\n";
}

bool Guest::operator>(const Guest &guest)
{
	return login > guest.login;
}

bool Guest::operator<(const Guest &guest)
{
	return !(*this > guest);
}

bool Guest::operator==(const Guest &guest)
{
	return login == guest.login;
}

bool Guest::operator!=(const Guest &guest)
{
	return login != guest.login;
}
