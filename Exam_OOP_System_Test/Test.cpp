#include "Test.h"

void Test::splitFilename(string &str)
{
	size_t found1 = str.find_first_of("\\");
	str = str.substr(found1 + 1);
}

string Test::findFileName(string entry)
{
	string normal;
	if (!entry.empty())
	{
		for (unsigned int i = 0; i < entry.size() - 3; i++)
		{
			if (entry[i] == '\\')
			{
				i++;
				while (entry[i] != '.' && i < entry.size())
				{
					normal.push_back(entry[i]);
					i++;
				}
			}
		}
		return normal;
	}
	throw exception("Не найдно\n");
}

Test::Test(string category, string test_name)
{
	this->category = category;
	this->test_name = test_name;
	this->count_categories = count_categories;
	count_test++;
}

void Test::setCategory(string category)
{
	this->category = category;
	count_categories++;
}

void Test::setTestname(string test_name)
{
	this->test_name = test_name;
}

void Test::setCountCategories(int count_categories)
{
	this->count_categories = count_categories;
}

int Test::getCountTest()
{
	return count_test;
}

string Test::getCategory()
{
	return category;
}

string Test::getTestName()
{
	return test_name;
}

void Test::saveToFile(fstream &fs)
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i].writeQuestionToFile(fs);
	}
}

void Test::addQuestion(Question q)
{
	data.push_back(q);
	count_test++;
}

int Test::searchPosition(string temp)
{
	int pos = 0;

	for (int i = 0; i < data.size(); i++)
	{
		pos = data[i].getBody().find(temp, i);
		if (pos != -1)
		{
			cout << pos << " ";
			pos = i;
			return pos;
		}
	}
	return -1;
}

Question Test::searchByPosition(int pos)
{
	Question temp;
	if (pos != -1)
	{
		temp = data[pos];
		return temp;
	}
	else
	{
		throw exception("Не найден!\n");
	}
}

Question Test::deleteByPosition(int pos)
{
	Question temp;
	if (pos != -1)
	{
		temp = data[pos];
		data.erase(data.begin() + pos);
		count_test--;
		return temp;
	}
	else
	{
		throw exception("не найден!\n");
	}
}

void Test::editByPosition(int pos)
{
	if (pos != -1)
	{
		data[pos].setQuestion(pos + 1);
		cout << "Вы добавили следующий вопрос:\n";
		data[pos].print();
	}
	else
	{
		cout << "Вопрос не найден!\n";
	} 
}

void Test::clearTest()
{
	data.clear();
	count_test = 0;
}

void Test::print() const
{
	for (unsigned int i = 0; i < data.size(); i++)
	{
		data[i].print();
	}
}

void Test::loadTestFromFile(fstream &fs)
{
	if (!fs.is_open())
	{
		cout << "\nФайл не существует. Создание нового файла.\n";
	}
	else
	{
		while (!fs.eof())
		{
			Question temp;
			temp.readQuestionFromFile(fs);
			if (temp.getBody() != "")
			{
				data.push_back(temp);
				count_test++;
			}
		}
	}
}

void Test::TestLoading(string category, string test_name, User current)
{
	fstream fs;
	Test test_now;
	int correct_count = 0;
	User temp;
	test_now.setCategory(category);
	test_now.setTestname(test_name);
	const int size = test_now.getCountTest();
	char *reply = new char[size + 1];
	string user_statistic_directory = "Statistics";
	fst::create_directories(user_statistic_directory);
	string user_statistic = user_statistic_directory + "\\" + current.getLogin() + "_" + test_name + ".txt";
	fs.open(user_statistic, fstream::in);
	temp.readUserStatisticsFile(fs);
	fs.close();
	if (temp.getLogin() == current.getLogin())
	{
		current = temp;
		correct_count = current.getCorrectCount(test_name);
	}
	string test_file = "Test\\" + category + "\\" + test_now.getTestName() + ".txt";
	fs.open(test_file, fstream::in);
	test_now.loadTestFromFile(fs);
	fs.close();
	char go_on;
	int last_position = 0;
	if (current.getPosition(test_name) != -1)
	{
		last_position = current.getPosition(test_name);
	}
	for (int i = last_position; i < test_now.getCountTest(); ++i)
	{
		test_now.searchByPosition(i).print();
		cout << "Укажите ответ( \"a\", \"b\", \"b\", \"d\"): " << "\n";
		cin >> reply[i];
		cin.ignore();
		if (test_now.searchByPosition(i).getCorrect() == reply[i])
		{
			correct_count++;
		}
		cout << "Для продолжения нажмите \"y\"\n";
		cout << "Для выхода нажмите(данные будут сохранены) \"n\"\n";
		cin >> go_on;
		if (go_on == 'n') {
			current.setPosition(test_now.getTestName(), i + 1);
			break;
		}
		else
		{
			current.setPosition(test_now.getTestName(), i + 1);
		}
	}
	current.setCorrectCount(test_now.getTestName(), correct_count);
	current.setMark(test_now.getTestName(), test_now.getCountTest());
	current.setPercent(test_now.getTestName(), test_now.getCountTest());
	cout << current;
	fs.open(user_statistic, fstream::out);
	current.writeStatisticsToFile(fs);
	fs.close();
	fs.clear();
}

void Test::readAllFromDirectory(vector<Test> &test_list)
{
	vector<string> files_category;
	for (auto &e : fst::directory_iterator("Test"))
	{
		files_category.push_back(e.path().string());
	}
	Test *temp = new Test[50];
	vector<string> files_tests;
	for (size_t i = 0; i < files_category.size(); i++)
	{
		for (auto &e : fst::directory_iterator(files_category[i]))
		{
			files_tests.push_back(e.path().string());
		}
	}
	for (size_t i = 0; i < files_tests.size(); i++)
	{
		string str_2(files_tests[i]);
		splitFilename(str_2);
		str_2 = findFileName(str_2);
		temp[i].setTestname(str_2);
		int a = 0;
		while (a < files_category.size())
		{
			size_t found = files_tests[i].find(files_category[a]);
			if (found != std::string::npos)
			{
				string str_1(files_category[a]);
				splitFilename(str_1);
				temp[i].setCategory(str_1);
				test_list.push_back(temp[i]);
			}
			a++;
		}
	}
}

void Test::showAllTests(vector<Test> &test_list)
{
	string category_temp;
	auto it = test_list.begin();
	category_temp = it->getCategory();
	int count_test = 2;
	for (size_t i = 0; i < test_list.size(); )
	{
		cout << "Категория: " << it->getCategory() << "\n";
		while (it != test_list.end() && it->getCategory() == category_temp)
		{
			cout << "   Test " << count_test << ". " << it->getTestName() << "\n";
			count_test++;
			it++;
			i++;
		};
		if (it != test_list.end())
		{
			category_temp = it->getCategory();
		}	
	}
}
