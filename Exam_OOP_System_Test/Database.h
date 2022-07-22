#pragma once

#include"User.h"

class Database
{
	vector<User> data;
	static int count;
public:
	static int getCount();
	void saveToFile(fstream &fs);
	void saveStatisticToFile(fstream &fs);
	void addUser(User user);
	int searchPosition(string login);
	User deleteByLogin(string login);
	void deleteUser(string login_delete);
	User searchByLogin(string login);
	void editPasswordByLogin(string login);
	void sortUp();
	void sortDown();
	void clearDataBase();
	void print();
	void loadUserFromFile(fstream &fs);
	void loadUserStatisticFromFile(fstream &fs);
};