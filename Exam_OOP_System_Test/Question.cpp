#include "Question.h"

Question::Question(string body, string a, string b, string c, string d, char correct)
{
	this->body = body;
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->correct = correct;
}

void Question::setQuestion(int number)
{
	setBody(number);
	setA();
	setB();
	setC();
	setD();
	setCorrect();
}

void Question::setBody(int number)
{
	cout << "������: " << "\n";
	getline(cin, body);
	body = "������ " + to_string(number) + ". " + body;
	this->body = body;
}

void Question::setA()
{
	cout << "����� \"a\": " << "\n";
	getline(cin, a);
	this->a = a;
}

void Question::setB()
{
	cout << "����� \"b\": " << "\n";
	getline(cin, b);
	this->b = b;
}

void Question::setC()
{
	cout << "����� \"c\": " << "\n";
	getline(cin, c);
	this->c = c;
}

void Question::setD()
{
	cout << "����� \"d\": " << "\n";
	getline(cin, d);
	this->d = d;
}

void Question::setCorrect()
{
	cout << "������� ���������� �����( \"a\", \"b\", \"b\", \"d\"): " << "\n";
	cin.get(correct);
	cin.ignore();
	this->correct = correct;
}

string Question::getBody()
{
	return body;
}

char Question::getCorrect()
{
	return correct;
}

void Question::readQuestionFromFile(fstream &fs)
{
	if (!fs.is_open())
	{
		cout << "������!!!";
	}
	else 
	{
		getline(fs, this->body);
		getline(fs, this->a);
		getline(fs, this->b);
		getline(fs, this->c);
		getline(fs, this->d);
		fs.get(this->correct);
		fs.ignore();
	}
}

void Question::writeQuestionToFile(fstream &fs)
{
	if (!fs.is_open())
	{
		cout << "������!!!";
	}
	else 
	{
		fs << body << "\n";
		fs << a << "\n";
		fs << b << "\n";
		fs << c << "\n";
		fs << d << "\n";
		fs << correct << "\n";
	}
}

void Question::print() const
{
	cout << "������: " << body << "\n";
	cout << "a. " << a << "\n";
	cout << "b. " << b << "\n";
	cout << "c. " << c << "\n";
	cout << "d. " << d << "\n";
}
