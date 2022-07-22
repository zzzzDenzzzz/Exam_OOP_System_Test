#pragma once

#include<map>
#include<vector>
#include<filesystem>
#include"Guest.h"

namespace fst = std::filesystem;

class User : public Guest
{
	string name;
	string surname;
	int phone;
	map<string, int> mark;
	map<string, int> position;
	map<string, int> correct_count;
	map<string, int> percent;
	friend ostream &operator<<(ostream &os, User &obj);
public:
	User();
	void setName(string name);
	void setSurname(string surname);
	void setPhone(int phone);
	void setMark(string test_name, int question_count);
	void setPosition(string test_name, int position);
	void setPercent(string test_name, int question_count);
	void setCorrectCount(string test_name, int correct_count);
	string getName() const;
	string getSurname() const;
	int getPhone() const;
	map<string, int> getCurrentPosition();
	int getPosition(string str);
	int getCorrectCount(string str);
	int getMark(string str);
	int getPercent(string str);
	void readUserFromFile(fstream &fs) override;
	void writeUserToFile(fstream &fs) override;
	void readUserStatisticsFile(fstream &fs);
	void writeStatisticsToFile(fstream &fs);
	void writeStatisticsToFile_2(fstream &fs);
	void showTestResult(vector<User> &statistics);
	void print() const override;
	void splitFilename_2(string &str);
};