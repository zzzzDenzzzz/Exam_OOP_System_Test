#include "Database.h"

int Database::count{};

int Database::getCount()
{
    return count;
}

void Database::saveToFile(fstream &fs)
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i].writeUserToFile(fs);
	}
}

void Database::saveStatisticToFile(fstream &fs)
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i].writeStatisticsToFile(fs);
	}
}

void Database::addUser(User user)
{
	data.push_back(user);
	count++;
}

int Database::searchPosition(string login)
{
	int pos = 0;
	for (unsigned int i = 0; i < data.size(); i++)
	{
		if (data[i].getLogin() == login)
		{
			pos = i;
			return pos;
		}
	}
	return -1;
}

User Database::deleteByLogin(string login)
{
	User temp;
	int	pos = searchPosition(login);
	if (pos != -1) 
	{
		temp = data[pos];
		data.erase(data.begin() + pos);
		count--;
		return temp;
	}
	else
	{
		throw exception("Не найдено!!!\n");
	}
}

void Database::deleteUser(string login_delete)
{
	auto it = remove_if(data.begin(), data.end(), [login_delete](User c)
		{
			return c.getLogin() == login_delete;
		});
	if (it == data.end())
	{
		cout << "\Login " << login_delete << " не найден!!!";
	}
	else
	{
		cout << "\nЛогин пользователя " << login_delete << " удален!";
		data.erase(it, data.end());
		count--;
	}
}

User Database::searchByLogin(string login)
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		if (data[i].getLogin() == login)
		{
			return data[i];
		}
	}
	throw exception("Не найден!\n");
}

void Database::editPasswordByLogin(string login)
{
	int	pos = searchPosition(login);
	if (pos != -1)
	{
		string password_new;
		cout << "Введите новый пароль: ";
		cin >> password_new;
		data[pos].setPassword(password_new);
		cout << "Вы изменили пароль, его можно использовать при следующем входе в систему:\n";
	}
	else
	{
		cout << "Пользователь не найден. Зарегистрируйтесь!\n";
	} 
}

void Database::sortUp()
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		for (unsigned int j = 0; j < data.size() - 1 - i; j++)
		{
			if (data[j] > data[j + 1])
			{
				swap(data[j], data[j + 1]);
			}	
		}
	}
}

void Database::sortDown()
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		for (unsigned int j = 0; j < data.size() - 1 - i; j++)
		{
			if (data[j] < data[j + 1])
			{
				swap(data[j], data[j + 1]);
			}
		}
	}
		
}

void Database::clearDataBase()
{
	data.clear();
	count = 0;
}

void Database::print()
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i].print();
	}
	cout << data.size();
}

void Database::loadUserFromFile(fstream &fs)
{
	if (!fs.is_open())
	{
		cout << "\nОшибка открытия файла\n";
	}
	else
	{
		while (!fs.eof())
		{
			User temp;
			temp.readUserFromFile(fs);
			if (temp.getLogin() != "")
			{
				data.push_back(temp);
			}
		}
	}
}

void Database::loadUserStatisticFromFile(fstream &fs)
{
	if (!fs.is_open())
	{
		cout << "\nОшибка открытия файла\n";
	}
	else
	{
		while (!fs.eof())
		{
			User temp;
			temp.readUserStatisticsFile(fs);
			if (temp.getLogin() != "" && temp.getLogin() != "\n" && temp.getLogin() != "\0")
			{
				data.push_back(temp);
				count++;
			}
			else
			{
				break;
			}
		}
	}
}
