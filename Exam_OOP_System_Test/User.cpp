#include "User.h"

void User::splitFilename_2(string &str)
{
	size_t found_1 = str.find_first_of("\\");
	str = str.substr(found_1 + 1);
	size_t found_2 = str.find_first_of("_");
	str = str.substr(0, found_2);
}

User::User()
{
	name = { "no" };
	surname = { "no" };
	phone = {};
	mark = {};
	position = {};
	percent = {};
	correct_count = {};
}

void User::setName(string name)
{
	this->name = name;
}

void User::setSurname(string surname)
{
	this->surname = surname;
}

void User::setPhone(int phone)
{
	this->phone = phone;
}

void User::setMark(string test_name, int question_count)
{
	int mark_t = 12 * correct_count.at(test_name) / question_count;
	mark.insert_or_assign(test_name, mark_t);
}

void User::setPosition(string test_name, int position)
{
	this->position.insert_or_assign(test_name, position);
}

void User::setPercent(string test_name, int question_count)
{
	int percent_t = 100 * correct_count.at(test_name) / question_count;
	this->percent.insert_or_assign(test_name, percent_t);
}

void User::setCorrectCount(string test_name, int correct_count)
{
	this->correct_count.insert_or_assign(test_name, correct_count);
}

string User::getName() const
{
	return name;
}

string User::getSurname() const
{
	return surname;
}

int User::getPhone() const
{
	return phone;
}

map<string, int> User::getCurrentPosition()
{
	return position;
}

int User::getPosition(string str)
{
	auto it = position.find(str);
	if (it == position.end())
	{
		return -1;
	}
	else
	{
		return it->second;
	}
}

int User::getCorrectCount(string str)
{
	auto it = correct_count.find(str);
	if (it == correct_count.end())
	{
		return -1;
	}
	else
	{
		return it->second;
	}
}

int User::getMark(string str)
{
	auto it = mark.find(str);
	return it->second;
}

int User::getPercent(string str)
{
	auto it = percent.find(str);
	return it->second;
}

void User::readUserFromFile(fstream &fs)
{
	if (!fs.is_open()) {
		cout << "Ошибка!!!";
	}
	else {
		Guest::readUserFromFile(fs);
		fs >> name;
		fs >> surname;
		fs >> phone;
	}
}

void User::writeUserToFile(fstream &fs)
{
	if (!fs.is_open()) {
		cout << "Ошибка!!!";
	}
	else {
		Guest::writeUserToFile(fs);
		fs << name << " " << surname << " " << phone << "\n";
	}
}

void User::readUserStatisticsFile(fstream &fs)
{
	if (!fs.is_open()) {
		cout << "Файл статистики не найден, создайте новый файл\n";
	}
	else {
		string login_;
		string str;
		pair<string, int> temp_mark;
		pair<string, int> temp_position;
		pair<string, int> temp_count;
		pair<string, int> temp_percent;
		fs >> login_;
		this->setLogin(login_);
		fs >> this->name;
		fs >> this->surname;
		fs >> this->phone;
		fs >> temp_mark.first;
		fs >> temp_mark.second;
		mark.insert(temp_mark);
		fs >> temp_position.first;
		fs >> temp_position.second;
		position.insert(temp_position);
		fs >> temp_count.first;
		fs >> temp_count.second;
		correct_count.insert(temp_count);
		fs >> temp_percent.first;
		fs >> temp_percent.second;
		percent.insert(temp_percent);
	}
}

void User::writeStatisticsToFile(fstream &fs)
{
	if (!fs.is_open()) {
		cout << "Ошибка!!!";
	}
	else {
		fs << Guest::getLogin() << " " << name << " " << surname << " " << phone << "\n";
		cout << "Оценка:\n";
		for (auto it = mark.begin(); it != mark.end(); it++)
		{
			fs << it->first << " " << it->second << "\n";
		}
		for (auto it = position.begin(); it != position.end(); it++)
		{
			fs << it->first << " " << it->second << "\n";
		}
		for (auto it = correct_count.begin(); it != correct_count.end(); it++)
		{
			fs << it->first << " " << it->second << "\n";
		}
		cout << "Текущий процент правильных ответов: \n";
		for (auto it = percent.begin(); it != percent.end(); it++)
		{
			fs << it->first << " " << it->second << "\n";
		}
	}
}

void User::writeStatisticsToFile_2(fstream &fs)
{
	if (!fs.is_open()) {
		cout << "Ошибка!!!";
	}
	else {
		fs << Guest::getLogin() << " " << name << " " << surname << " " << phone << "\n";
		fs << "Оценка:\n";
		for (auto it = mark.begin(); it != mark.end(); it++)
		{
			fs << it->first << " | " << it->second << "\n";
		}
		fs << "Текущий процент правильных ответов: \n";
		for (auto it = percent.begin(); it != percent.end(); it++)
		{
			fs << it->first << " | " << it->second << "\n";
		}
	}
}

void User::showTestResult(vector<User> &statistics)
{
	vector<string> files;
	fstream fs;
	for (auto &e : fst::directory_iterator("Statistics"))
	{
		files.push_back(e.path().string());
	}
	vector<string> logins;
	logins = files;
	for (size_t i = 0; i < files.size(); i++)
	{
		splitFilename_2(logins[i]);
	}
	for (size_t i = 0; i < files.size(); i++)
	{
		if (this->getLogin() == logins[i]) {
			while (i < files.size() && this->getLogin() == logins[i]) {
				fs.open(files[i], fstream::in);
				this->readUserStatisticsFile(fs);
				fs.close();
				i++;
			}
			statistics.push_back(*this);
		}
	}
	if (!statistics.empty())
	{
		for (size_t i = 0; i < statistics.size(); i++)
		{
			cout << statistics[i] << "\n";
		}
	}
	else
	{
		cout << "Файл статистики не найден!\n";
	} 
	statistics.erase(statistics.begin(), statistics.end());
}

void User::print() const
{
	cout << Guest::getLogin() << "\n";
	cout << "Имя: " << name << " Фамилия: " << surname << " Телефон: " << phone << "\n";
	cout << endl;
}
