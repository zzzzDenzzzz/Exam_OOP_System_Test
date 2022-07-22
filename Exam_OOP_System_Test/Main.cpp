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
		cout << "\n��������������!\n";
		cout << "�������� ������������:\n";
		cout << "1- �������������\n";
		cout << "2- ������������\n";
		cout << "0- �����\n";
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
				cout << "����� ���������� � ������ ��������������, ����������, ������� ����� �������������� ��� ������� ����� ";
				cin >> adminlogin;
				superadmin.setLogin(adminlogin);
				cout << "������� ������ ��������������: ";
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
				cout << "����� ���������� � ������ ��������������!\n";
				int index = -1;
				cout << "�����: ";
				cin >> adminlogin_;
				if (adminlogin_ == superadmin.getLogin())
				{
					int mistakes = 0;
					do {
						cout << "������: ";
						cin >> adminpassword_;
						if (adminpassword_ == superadmin.getPassword())
						{
							cout << "����������� � �������...\n";
							system("pause");
							do 
							{
								system("cls");
								cout << endl << string(100, '*');
								cout << "\n������ ��������������!";
								cout << "\n�������� ��������:" << endl;
								cout << "1 - ������� ���� ������ �������������\n";
								cout << "2 - �������� ������ ������\n";
								cout << "3 - ������� ������ ������������\n";
								cout << "4 - ������������� ������������ ������� ������ ������������\n";
								cout << "5 - ������� ������������\n";
								cout << "6 - �������� ���� ���������������� ������\n";
								cout << "7 - �������� ����������\n";
								cout << "8 - ���������� ���������� � ����\n";
								cout << "9 - ���������� ������ � ���������\n";
								cout << "10 - ������� ���������\n";
								cout << "11 - ������� ����\n";
								cout << "12 - �������� ������ �������������� � �����\n";
								cout << "0 - �����" << endl;
								cout << endl << string(100, '*');
								cout << "\n�������� ���� �����, ����������: ";
								cin >> answer;
								cin.ignore();
								if (answer)
								{
									switch (answer)
									{
									case 1:
									{
										cout << "1 - ������� ���� ������ �������������\n";
										b.clearDataBase();
										fs.open("Users\\user_data_base.txt", fstream::in);
										b.loadUserFromFile(fs);
										fs.close();
										b.print();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\", \"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 2:
									{
										cout << "2 - �������� ������ ������\n";
										vector<Test> test_list;
										test_now.readAllFromDirectory(test_list);
										test_now.showAllTests(test_list);
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 3:
									{
										cout << "3 - ������� ������ ������������\n";
										cout << "������� ����� �����: ";
										string login_, password_;
										int index = 0;
										cin >> login_;
										index = b.searchPosition(login_);
										if (index == -1) {
											cout << "������� ������: ";
											cin >> password_;
											User temp;
											temp.setLogin(login_);
											temp.setPassword(password_);
											b.addUser(temp);
											cout << "������������ " << login_ << " ������!\n";
											fs.open("Users\\user_data_base.txt", fstream::out);
											b.saveToFile(fs);
											fs.close();
										}
										else cout << "������������ ��� ����������, ����������, �������� ������ �����.\n";
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 4:
									{
										cout << "4 - ������������� ������������ ������� ������ ������������\n";
										string login_;
										cout << "������� ����� ��� ��������������: ";
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
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 5:
									{
										cout << "5 - ������� ������������\n";
										string login_;
										cout << "������� ����� ��� ��������: ";
										cin >> login_;
										b.deleteUser(login_);
										fs.open("Users\\user_data_base.txt", fstream::out);
										b.saveToFile(fs);
										fs.close();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 6:
									{
										cout << "6 - �������� ���� ���������������� ������\n";
										b.clearDataBase();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 7:
									{
										cout << "7 - �������� ����������\n";
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
											cout << "���� �� ������\n";
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 8:
									{
										cout << "8 - ���������� ���������� � ����\n";
										fst::remove("total_statistics.txt");
										for (size_t i = 0; i < statistics.size(); i++)
										{
											fs.open("total_statistics.txt", fstream::out | fstream::app);
											statistics[i].writeStatisticsToFile_2(fs);
											fs.close();
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 9:
									{
										cout << "9 - ���������� ������ � ���������\n";
										Test new_test;
										string path;
										string new_test_name;
										Question new_question;
										string new_question_body;
										string new_question_answerA;
										string new_question_correct_answer;
										cout << "����������, ������� �������� ���������, ����� �������� ��� ������ ��������� � ������������ :\n";
										cin >> path;
										new_test.setCategory(path);
										path = "Test//" + path;
										fst::create_directories(path);
										cout << "����������, ������� ����� ��� ����� ��� ������������ ��� ����� ��� ��������������:\n";
										cin >> new_test_name;
										new_test.setTestname(new_test_name);
										string path_test = path + "\\" + new_test.getTestName() + ".txt";
										Test temp;
										fs.open(path_test, fstream::in);
										temp.loadTestFromFile(fs);
										fs.close();
										if (temp.getCountTest())
											cout << "������� ���� ��� ���� " << temp.getCountTest() << " �������\n";
										int new_question_count;
										cout << "����������, ������� ���������� ��������, ������� �� ����������� ��������:\n";
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
										cout << "�� �������� ��������� ����, �� �������� � �����:\n";
										new_test.print();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 10: {
										cout << "10 - ������� ���������\n";
										vector<Test> test_list;
										Test t;
										t.readAllFromDirectory(test_list);
										t.showAllTests(test_list);
										string path;
										cout << "����������, ������� �������� ��������� ��� ��������, ������ � ����, ��� ��� ����� � ���� ��������� ����� ����� �������!:\n";
										cin >> path;
										path = "Test\\" + path;
										try
										{
											uintmax_t n = fst::remove_all(path);
											cout << "��������� " << n << " ����� ��� ��������\n";
										}
										catch (exception ex)
										{
											cout << ex.what() << "\n";
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 11:
									{
										cout << "11 - ������� ����\n";
										vector<Test> test_list;
										Test t;
										t.readAllFromDirectory(test_list);
										t.showAllTests(test_list);
										string path;
										string test_name;
										cout << "����������, ������� �������� ���������, � ������� ���� ������ ���� ������:\n";
										cin >> path;
										cout << "����������, ������� ��� ����� ��� ��������:\n";
										cin >> test_name;
										path = "Test\\" + path + "\\" + test_name + ".txt";
										try
										{
											uintmax_t n = fst::remove(path);
											cout << "��������� " << n << " ����� ��� ��������\n";
										}
										catch (exception ex)
										{
											cout << ex.what() << "\n";
										}
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									case 12:
									{
										cout << "12 - �������� ������ �������������� � �����\n";
										cout << "������� ����� ����� ��������������: ";
										cin >> adminlogin;
										superadmin.setLogin(adminlogin);
										cout << "������� ����� ������ ��������������: ";
										cin >> adminpassword;
										superadmin.setPassword(adminpassword);
										fs.open("Admin\\admin.txt", fstream::out);
										superadmin.writeUserToFile(fs);
										fs.close();
										cout << endl << "____________________________________________________________________________________" << endl;
										cout << "\n�������� ����? \"y\",\"n\".\n";
										cin >> choice;
										cin.ignore();
										break;
									}
									default:
										if (answer > 12 || answer < 0)
										{
											cout << "������������ �����! ���������� ��� ���!\n";
											system("pause");
										}
										choice = 'y';
										break;
									}
								}
								else
								{
									cout << "������� �� �����!\n";
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
							cout << "�������� ������, ��������� �������\n";
						}
					} 
					while (mistakes < 5);
					if (mistakes == 5)
					{
						cout << "�� ��������� 5 ������, ���������� �����.\n";
						system("pause");
					}
				}
				else
				{
					cout << "������������ �����\n";
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
				cout << "\n���� � ��� ��� ���� ������� ������, ����������, ������� � �������, ���� ��� - ����������, �����������������!\n";
				cout << "����������, �������� ���� �����:\n";
				cout << "1- ����� � ������� � ������������ ������� �������\n";
				cout << "2- ���������������� ����� ������� ������\n";
				cout << "0- �����\n";
				cout << endl << string(100, '*') << "\n";
				cin >> answer;
				cin.ignore();
				switch (answer)
				{
				case 1:
				{
					int index = -1;
					string login_, password_;
					cout << "������� ���� �����: ";
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
							cout << "������� ���� ������: ";
							cin >> password_;
							g = b.searchByLogin(login_);
							if (password_ == g.getPassword())
							{
								cout << "����������� � �������...\n";
								current = g;
								answer = 0;
								break;
							}
							else
							{
								mistakes++;
								cout << "�������� ������, ��������� �������\n";
							}
						} while (mistakes < 5);
						if (mistakes == 5)
						{
							cout << "�� ��������� 5 ������, ���������� �����.\n";
							system("pause");
						}
					}
					else
					{
						cout << "������������ �� ������!\n";
						system("pause");
					}
					break;
				}
				case 2:
				{
					cout << "������� ���� ����� ��� �����������: ";
					string login_, password_, name_, surname_;
					int phone_;
					int index = 0;
					cin >> login_;
					index = b.searchPosition(login_);
					if (index == -1)
					{
						cout << "������� ���� ������: ";
						cin >> password_;
						cout << "������� ���� ���: ";
						cin >> name_;
						cout << "������� ���� �������: ";
						cin >> surname_;
						cout << "������� ���� �������: ";
						cin >> phone_;
						User temp;
						temp.setLogin(login_);
						temp.setPassword(password_);
						temp.setName(name_);
						temp.setSurname(surname_);
						temp.setPhone(phone_);
						b.addUser(temp);
						cout << "������������ " << login_ << " ��� ���������������, ������ �� ������ ����� � �������!\n";
					}
					else
					{
						cout << "������������ ��� ����������, ����������, �������� ������ �����.\n";
					} 
					system("pause");
					break;
				}

				default:
				{
					if (answer > 3 || answer < 0)
					{
						cout << " �������� ���������� �����! \n";
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
				cout << " �������� ���������� �����! \n";
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
			cout << "\n�������, ��� ������:" << endl;
			cout << "\n1 - �������� ���������� ������������\n\n";
			cout << "������� ����� ����� ��� �����������:\n";
			t.showAllTests(test_list);
			cout << "0  - �����" << endl;
			cout << endl << string(100, '*');
			cout << "\n�������� ���� �����, ����������: ";
			cin >> answer;
			cin.ignore();
			if (answer) {
				switch (answer) {
				case 1: {
					statistics.erase(begin(statistics), end(statistics));
					current.showTestResult(statistics);
					cout << endl << "____________________________________________________________________________________" << endl;
					cout << "\n�������� ����? \"y\",\"n\".\n";
					cin >> choice;
					cin.ignore();
					break;
				}
				default:
				{
					if (isdigit(answer) == 0) {
						int index = answer - 2;
						cout << "�� ������� " << test_list[index].getTestName() << "\n";
						string category = test_list[index].getCategory();
						string test_name = test_list[index].getTestName();
						t.TestLoading(category, test_name, current);
						cout << endl << "____________________________________________________________________________________" << endl;
						cout << "\n����������? \"y\", \"n\".\n";
						cin >> choice;
						cin.ignore();
						break;
					}
					else 
					{
						cout << "������������ �����! ��������� �����!\n";
						choice = 'y';
						break;
					}
				}
				}
			}
			else
			{
				cout << "������� �� �����!\n";
				break;
			}
		} while (choice != 'n');
	}

	return 0;
}