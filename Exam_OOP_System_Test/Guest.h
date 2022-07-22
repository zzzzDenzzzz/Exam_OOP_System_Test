#pragma once

#include<string>
#include<fstream>
#include<iostream>

using namespace std;

class Guest
{
	string login;
	string password;
public:
	Guest() = default;
	Guest(string login, string password);
	void setLogin(string login);
	void setPassword(string password);
	string getLogin() const;
	string getPassword() const;
	virtual void readUserFromFile(fstream &fs);
	virtual void writeUserToFile(fstream &fs);
	virtual void print() const;
	bool operator>(const Guest &guest);
	bool operator<(const Guest &guest);
	bool operator==(const Guest &guest);
	bool operator!=(const Guest &guest);
};