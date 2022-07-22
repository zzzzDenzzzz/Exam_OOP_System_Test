#pragma once

#include<string>
#include<iostream>
#include<fstream>

using namespace std;

class Question
{
	string body;
	string a;
	string b;
	string c;
	string d;
	char correct;
public:
	Question() = default;
	Question(string body, string a, string b, string c, string d, char correct);
	void setQuestion(int number);
	void setBody(int number);
	void setA();
	void setB();
	void setC();
	void setD();
	void setCorrect();
	string getBody();
	char getCorrect();
	void readQuestionFromFile(fstream &fs);
	void writeQuestionToFile(fstream &fs);
	void print() const;
};