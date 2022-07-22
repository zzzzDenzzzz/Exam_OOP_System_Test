#include<Windows.h>
#include<direct.h>
#include"User.h"
#include"Admin.h"
#include"Test.h"
#include"Database.h"

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);

	User current;
	fstream fs;
	User g;
	Admin superadmin;
	string adminlogin;
	string adminpassword;
	Test test_now;
	Database b;
	vector<User> statistics;
	_mkdir("Statistics");
	_mkdir("Users");
	_mkdir("Admin");
	string path1 = "Test";
	string path2 = "Test\\Travel";
	string path3 = "Test\\Natural_Science";
	fst::create_directories(path1);
	fst::create_directories(path2);
	fst::create_directories(path3);
	map<string, int> m;
	int answer = 0;
	char choice;

	do {
		system("cls");
		cout << endl << string(100, '*');
		cout << "\nЗдравуйствуйте!\n";
		cout << "Выбирите пользователя:\n";
		cout << "1- Администратор\n";
		cout << "2- Пользователь\n";
		cout << "0- ВЫХОД\n";
		cout << endl << string(100, '*') << "\n";
		cin >> answer;
		cin.ignore();
		switch (answer)
		{
		case 1:
		{
			string adminlogin_, adminpassword_;
			fs.open("Admin\\admin.txt", fstream::in);
			if (!fs.is_open())
			{

			}
			else
			{
				superadmin.readUserFromFile(fs);
			}
			fs.close();
			if (superadmin.getLogin() == "")
			{
				cout << "Добро пожаловать в панель администратора, пожалуйста, введите логин администратора для первого входа ";
				cin >> adminlogin;
				superadmin.setLogin(adminlogin);
				cout << "Введите пароль администратора: ";
				cin >> adminpassword;
				superadmin.setPassword(adminpassword);
				fs.open("Admin\\admin.txt", fstream::out);
				superadmin.writeUserToFile(fs);
				fs.close();
			}
			else
			{
				fs.open("Admin\\admin.txt", fstream::in);
				superadmin.readUserFromFile(fs);
				fs.close();
				cout << "Добро пожаловать в панель администратора!\n";
				int index = -1;
				cout << "Логин: ";
				cin >> adminlogin_;
				if (adminlogin_ == superadmin.getLogin())
				{
					int mistakes = 0;
					do {
						cout << "Пароль: ";
						cin >> adminpassword_;
						if (adminpassword_ == superadmin.getPassword())
						{
							cout << "Регистрация в системе...\n";
							system("pause");
							do 
							{
								system("cls");
								cout << endl << string(100, '*');
								cout << "\nПанель администратора!";
								cout << "\nВыбирите действие:" << endl;
								cout << "1 - Открыть базу данных пользователей\n";
								cout << "2 - Показать список тестов\n";
								cout << "3 - Создать нового пользователя\n";
								cout << "4 - Редактировать существующую учетную запись пользователя\n";
								cout << "5 - Удалить пользователя\n";
								cout << "6 - Очистить базу пользовательских данных\n";
								cout << "7 - Просмотр статистики\n";
								cout << "8 - Сохранение статистики в файл\n";
								cout << "9 - Добавление тестов и категорий\n";
								cout << "10 - Удалить категорию\n";
								cout << "11 - Удалить тест\n";
								cout << "12 - Измените пароль администратора и логин\n";
								cout << "0 - ВЫХОД" << endl;
								cout << endl << string(100, '*');
								cout << "\nСделайте свой выбор, пожалуйста: ";
								cin >> answer;
								cin.ignore();
								if (answer)
								{
									switch (answer)
									{
									case 1:
									{
										cout << "1 - Открыть базу данных пользователей\n";
										b.clearDataBase();
										fs.open("Users\\user_data_base.txt", fstream::in);
										b.loadUserFromFile(fs);
										fs.close();
										b.print();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\", \"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 2:
									{
										cout << "2 - Показать список тестов\n";
										vector<Test> test_list;
										test_now.readAllFromDirectory(test_list);
										test_now.showAllTests(test_list);
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 3:
									{
										cout << "3 - Создать нового пользователя\n";
										cout << "Укажите новый логин: ";
										string login_, password_;
										int index = 0;
										cin >> login_;
										index = b.searchPosition(login_);
										if (index == -1) {
											cout << "Укажите пароль: ";
											cin >> password_;
											User temp;
											temp.setLogin(login_);
											temp.setPassword(password_);
											b.addUser(temp);
											cout << "Пользователь " << login_ << " создан!\n";
											fs.open("Users\\user_data_base.txt", fstream::out);
											b.saveToFile(fs);
											fs.close();
										}
										else cout << "Пользователь уже существует, пожалуйста, выберите другой логин.\n";
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 4:
									{
										cout << "4 - Редактировать существующую учетную запись пользователя\n";
										string login_;
										cout << "Введите логин для редактирования: ";
										cin >> login_;
										try
										{
											b.editPasswordByLogin(login_);
											fs.open("Users\\user_data_base.txt", fstream::out);
											b.saveToFile(fs);
											fs.close();
										}
										catch (const std::exception &ex)
										{
											cout << ex.what();
											system("pause");
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 5:
									{
										cout << "5 - Удалить пользователя\n";
										string login_;
										cout << "Введите логин для удаления: ";
										cin >> login_;
										b.deleteUser(login_);
										fs.open("Users\\user_data_base.txt", fstream::out);
										b.saveToFile(fs);
										fs.close();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 6:
									{
										cout << "6 - Очистить базу пользовательских данных\n";
										b.clearDataBase();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 7:
									{
										cout << "7 - Просмотр статистики\n";
										statistics.erase(begin(statistics), end(statistics));
										vector<string> files;
										for (auto &e : fst::directory_iterator("Statistics"))
										{
											files.push_back(e.path().string());
										}
										vector<string> logins;
										logins = files;
										User u;
										for (size_t i = 0; i < files.size(); i++)
										{
											u.splitFilename_2(logins[i]);
										}
										User *temp = new User[50];
										int index = 0;
										for (size_t i = 0; i < files.size(); )
										{
											temp[index].setLogin(logins[i]);
											while (i < files.size() && temp[index].getLogin() == logins[i])
											{
												fs.open(files[i], fstream::in);
												temp[index].readUserStatisticsFile(fs);
												fs.close();
												i++;
											}
											statistics.push_back(temp[index]);
											index++;
										}
										delete[] temp;
										if (!statistics.empty())
										{
											for (size_t i = 0; i < statistics.size(); i++)
											{
												cout << statistics[i] << "\n";
											}
										}
										else
										{
											cout << "Файл не найден\n";
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 8:
									{
										cout << "8 - Сохранение статистики в файл\n";
										fst::remove("total_statistics.txt");
										for (size_t i = 0; i < statistics.size(); i++)
										{
											fs.open("total_statistics.txt", fstream::out | fstream::app);
											statistics[i].writeStatisticsToFile_2(fs);
											fs.close();
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 9:
									{
										cout << "9 - Добавление тестов и категорий\n";
										Test new_test;
										string path;
										string new_test_name;
										Question new_question;
										string new_question_body;
										string new_question_answerA;
										string new_question_correct_answer;
										cout << "Пожалуйста, введите название категории, чтобы добавить или внести изменения в существующую :\n";
										cin >> path;
										new_test.setCategory(path);
										path = "Test//" + path;
										fst::create_directories(path);
										cout << "Пожалуйста, введите новое имя теста или существующее имя теста для редактирования:\n";
										cin >> new_test_name;
										new_test.setTestname(new_test_name);
										string path_test = path + "\\" + new_test.getTestName() + ".txt";
										Test temp;
										fs.open(path_test, fstream::in);
										temp.loadTestFromFile(fs);
										fs.close();
										if (temp.getCountTest())
											cout << "Текущий тест уже есть " << temp.getCountTest() << " вопросы\n";
										int new_question_count;
										cout << "Пожалуйста, введите количество вопросов, которые вы собираетесь добавить:\n";
										cin >> new_question_count;
										cin.ignore();
										int q_in_file = 0;
										if (temp.getCountTest())
										{
											q_in_file = temp.getCountTest();
										}
										for (size_t i = q_in_file; i < new_question_count + q_in_file; i++)
										{
											new_question.setQuestion(i + 1);
											new_test.addQuestion(new_question);
										}
										fs.open(path_test, fstream::out | fstream::app);
										new_test.saveToFile(fs);
										fs.close();
										cout << "Вы добавили следующий тест, он сохранен в файле:\n";
										new_test.print();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 10: {
										cout << "10 - Удалить категорию\n";
										vector<Test> test_list;
										Test t;
										t.readAllFromDirectory(test_list);
										t.showAllTests(test_list);
										string path;
										cout << "Пожалуйста, введите название категории для удаления, имейте в виду, что все тесты в этой категории также будут удалены!:\n";
										cin >> path;
										path = "Test\\" + path;
										try
										{
											uintmax_t n = fst::remove_all(path);
											cout << "Удаленный " << n << " файлы или каталоги\n";
										}
										catch (exception ex)
										{
											cout << ex.what() << "\n";
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 11:
									{
										cout << "11 - Удалить тест\n";
										vector<Test> test_list;
										Test t;
										t.readAllFromDirectory(test_list);
										t.showAllTests(test_list);
										string path;
										string test_name;
										cout << "Пожалуйста, введите название категории, в которой тест должен быть удален:\n";
										cin >> path;
										cout << "Пожалуйста, введите имя теста для удаления:\n";
										cin >> test_name;
										path = "Test\\" + path + "\\" + test_name + ".txt";
										try
										{
											uintmax_t n = fst::remove(path);
											cout << "Удаленный " << n << " файлы или каталоги\n";
										}
										catch (exception ex)
										{
											cout << ex.what() << "\n";
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 12:
									{
										cout << "12 - Измените пароль администратора и логин\n";
										cout << "Введите новый логин администратора: ";
										cin >> adminlogin;
										superadmin.setLogin(adminlogin);
										cout << "Введите новый пароль администратора: ";
										cin >> adminpassword;
										superadmin.setPassword(adminpassword);
										fs.open("Admin\\admin.txt", fstream::out);
										superadmin.writeUserToFile(fs);
										fs.close();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\nПоказать меню? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									default:
										if (answer > 12 || answer < 0)
										{
											cout << "Неправильный выбор! Попробуйте еще раз!\n";
											system("pause");
										}
										choice = 'y';
										break;
									}
								}
								else
								{
									cout << "Спасибо за визит!\n";
									break;
								}
							} 
							while (choice != 'n');
							answer = 0;
							break;
						}
						else
 {
							mistakes++;
							cout << "Неверный пароль, повторите попытку\n";
						}
					} 
					while (mistakes < 5);
					if (mistakes == 5)
					{
						cout << "Вы допустили 5 ошибок, попробуйте позже.\n";
						system("pause");
					}
				}
				else
				{
					cout << "Неправильный логин\n";
				}
			}
			system("pause");
			break;
		}
		case 2:
		{
			fs.open("Users\\user_data_base.txt", fstream::in);
			b.loadUserFromFile(fs);
			fs.close();
			do
			{
				system("cls");
				cout << endl << string(100, '*');
				cout << "\nЕсли у вас уже есть учетная запись, пожалуйста, войдите в систему, если нет - пожалуйста, зарегистрируйтесь!\n";
				cout << "Пожалуйста, сделайте свой выбор:\n";
				cout << "1- войти в систему с существующей учетной записью\n";
				cout << "2- зарегистрировать новую учетную запись\n";
				cout << "0- ВЫХОД\n";
				cout << endl << string(100, '*') << "\n";
				cin >> answer;
				cin.ignore();
				switch (answer)
				{
				case 1:
				{
					int index = -1;
					string login_, password_;
					cout << "Введите свой логин: ";
					cin >> login_;
					try
					{
						index = b.searchPosition(login_);
					}
					catch (const std::exception &ex)
					{
						cout << ex.what();
						system("pause");
					}
					if (index != -1)
					{
						int mistakes = 0;
						do
						{
							cout << "Введите свой пароль: ";
							cin >> password_;
							g = b.searchByLogin(login_);
							if (password_ == g.getPassword())
							{
								cout << "Регистрация в системе...\n";
								current = g;
								answer = 0;
								break;
							}
							else
							{
								mistakes++;
								cout << "Неверный пароль, повторите попытку\n";
							}
						} while (mistakes < 5);
						if (mistakes == 5)
						{
							cout << "Вы допустили 5 ошибок, попробуйте позже.\n";
							system("pause");
						}
					}
					else
					{
						cout << "Пользователь не найден!\n";
						system("pause");
					}
					break;
				}
				case 2:
				{
					cout << "Введите свой логин для регистрации: ";
					string login_, password_, name_, surname_;
					int phone_;
					int index = 0;
					cin >> login_;
					index = b.searchPosition(login_);
					if (index == -1)
					{
						cout << "Введите свой пароль: ";
						cin >> password_;
						cout << "Введите свое имя: ";
						cin >> name_;
						cout << "Введите свою фамилию: ";
						cin >> surname_;
						cout << "Введите свой телефон: ";
						cin >> phone_;
						User temp;
						temp.setLogin(login_);
						temp.setPassword(password_);
						temp.setName(name_);
						temp.setSurname(surname_);
						temp.setPhone(phone_);
						b.addUser(temp);
						cout << "Пользователь " << login_ << " был зарегистрирован, теперь вы можете войти в систему!\n";
					}
					else
					{
						cout << "Пользователь уже существует, пожалуйста, выберите другой логин.\n";
					} 
					system("pause");
					break;
				}

				default:
				{
					if (answer > 3 || answer < 0)
					{
						cout << " Сделайте правильный выбор! \n";
						system("pause");
					}
				}
				}
			} while (answer != 0);
			fs.open("Users\\user_data_base.txt", fstream::out);
			b.saveToFile(fs);
			fs.close();
			answer = 0;
			break;
		}
		default: {
			if (answer > 3 || answer < 0)
			{
				cout << " Сделайте правильный выбор! \n";
				system("pause");
			}
		}
		}
	} while (answer != 0);

	if (!current.getLogin().empty())
	{
		vector<Test> test_list;
		Test t;
		t.readAllFromDirectory(test_list);
		do
		{
			cout << endl << string(100, '*');
			cout << "\nВыбирай, что делать:" << endl;
			cout << "\n1 - Показать результаты тестирования\n\n";
			cout << "Введите номер теста для прохождения:\n";
			t.showAllTests(test_list);
			cout << "0  - ВЫХОД" << endl;
			cout << endl << string(100, '*');
			cout << "\nСделайте свой выбор, пожалуйста: ";
			cin >> answer;
			cin.ignore();
			if (answer) {
				switch (answer) {
				case 1: {
					statistics.erase(begin(statistics), end(statistics));
					current.showTestResult(statistics);
					cout << endl << "____________________________________________________________________________________" << endl;
					cout << "\nПоказать меню? \"y\",\"n\".\n";
					cin >> choice;
					cin.ignore();
					break;
				}
				default:
				{
					if (isdigit(answer) == 0) {
						int index = answer - 2;
						cout << "Вы выбрали " << test_list[index].getTestName() << "\n";
						string category = test_list[index].getCategory();
						string test_name = test_list[index].getTestName();
						t.TestLoading(category, test_name, current);
						cout << endl << "____________________________________________________________________________________" << endl;
						cout << "\nПродолжать? \"y\", \"n\".\n";
						cin >> choice;
						cin.ignore();
						break;
					}
					else 
					{
						cout << "Неправильный выбор! Пробовать снова!\n";
						choice = 'y';
						break;
					}
				}
				}
			}
			else
			{
				cout << "Спасибо за визит!\n";
				break;
			}
		} while (choice != 'n');
	}

	return 0;
}