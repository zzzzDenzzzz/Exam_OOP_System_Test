#pragma once

#include<vector>
#include"Question.h"
#include"User.h"

using namespace std;

class Test
{
	vector<Question> data;
	string category;
	string test_name;
	int count_test;
	int count_categories;
	void splitFilename(string &str);
	string findFileName(string entry);
public:
	Test() = default;
	Test(string category, string test_name);
	void setCategory(string category);
	void setTestname(string test_name);
	void setCountCategories(int count_categories);
	int getCountTest();
	string getCategory();
	string getTestName();
	void saveToFile(fstream &fs);
	void addQuestion(Question q);
	int searchPosition(string temp);
	Question searchByPosition(int pos);
	Question deleteByPosition(int pos);
	void editByPosition(int pos);
	void clearTest();
	void print() const;
	void loadTestFromFile(fstream &fs);
	void TestLoading(string category, string test_name, User current);
	void readAllFromDirectory(vector<Test> &test_list);
	void showAllTests(vector<Test> &test_list);
};