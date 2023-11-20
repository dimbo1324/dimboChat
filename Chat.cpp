#include "Chat.h"
#include<iostream>
#include <string>

void Chat::Start() {
	_chatWorkCheck = true;
}
	shared_ptr<User>Chat::GetUserByLogin(const string& login) const //����� ������������ �� ��� ������
	{
	for (auto& user : _userList)
	{
		if (login == user.GetUserLogin())
			return make_shared<User>(user);
	}
	return nullptr;
}
	shared_ptr<User>Chat::GetUserByName(const string& name)const
{
	for (auto& user : _userList)
	{
		if (name == user.GetUserName())
			return make_shared<User>(user);
	}
	return nullptr;
}
void Chat::ShowLoginMenu()
{
	setlocale(LC_ALL, "RUS");
	_currentUser = nullptr;//����������� �������� ������������ �������� nullptr 
		char operation;
		do {
			cout << "\033[33m" << " (1) ���� " << endl;
			cout << " (2) ����������� " << endl;
			cout << " (0) ����� " << endl;
			cout << "\033[36m" << ">>" << "\033[0m";
			cin >> operation;
			switch (operation) {
			case '1':
				Login();//���� �� ������ � ������
				break;
			case '2':
				try
				{
					SignUp();//����������� ������ ������������
				}
				catch (const exception& e)//����� ������ ��� ����������� ������ ������������
				{
					cout << e.what() << endl;
				}
				break;
			case '0':
				_chatWorkCheck = false;
				break;
			default:
				cout << "1 ��� 2..." << endl;
				break;

			}
		} while (!_currentUser && _chatWorkCheck);//���� ��������, ���� �� ��������������� ������������, � ���� ��� ��������
}
void Chat::Login() 
{
	setlocale(LC_ALL, "");
	string login, password;
	char operation;

	do {
		cout << " �����: ";
		cin >> login;
		cout << " ������: ";
		cin >> password;

		_currentUser = GetUserByLogin(login);//��������� �� ������������, ������� �����������������
		if (_currentUser == nullptr || (password != _currentUser ->GetUserPassword()))//���� ������� ������������ ��� � �������, �� ���������� ������ ����������, ��� ���� �������� ������
		{
			_currentUser = nullptr;
			cout << " ���� �� ��������... " << endl;
			cout << " (0) ����� ��� (����� �������) ������: ";
			cin >> operation;
			if (operation == '0')
				break;
		}
	} while (!_currentUser);
}

void Chat::ShowChat()const
{
	setlocale(LC_ALL, "");
	string from;
	string to;
	cout << " ---���--- " << endl;
	for (auto& message : _messageList) 
	{
		if (_currentUser->GetUserLogin() == message.GetFrom() || _currentUser ->GetUserLogin() == message.GetTo() || message.GetTo() == " ���� ")
		{//���� ������� ������������
			from = (_currentUser ->GetUserLogin() == message.GetFrom()) ? " � " : GetUserByLogin(message.GetFrom())->GetUserName();
			if (message.GetTo() == " ���� ")//�������� ���� ������������� ����
			{
				to = " ���� ";
			}
			else
			{
				to = (_currentUser ->GetUserLogin() == message.GetTo()) ? " � " : GetUserByLogin(message.GetTo())->GetUserName();
//���� �� ������� ��� ������������ ����� to, �� ���������� ��������� ������ ����, ���� ���, �� �������� ��� ������������ � ����������� ��� �������� ���� to
			}
			cout << " ��������� �� " << from << " ��� " << to << endl;
			cout << " ����� ��������� :" << message.GetText() << endl;
		}
	}
	cout << "-----------" << endl;

}
void Chat::SignUp() 
{
	setlocale(LC_ALL, "");
	string login, password, name;
	double time;
	cout << " �����: ";
	cin >> login;
	cout << " ������:";
	cin >> password;
	cout << " ���:";
	cin >> name;
	if (GetUserByLogin(login) || login == " ���� ")
	{
		throw UserLoginExp();
	}
	if (GetUserByName(name) || name == " ���� ")
	{
		throw UserNameExp();

	}
	User user = User(login, password, name, time);//�������� ������ ������������
	_userList.push_back(user);//���������� ������������
	_currentUser = make_shared<User>(user);//������� ��������� �� �������� ������������
}
void Chat::ShowUserMenu() 
{
	setlocale(LC_ALL, "");
	char operation;
	cout << " ������, " << _currentUser->GetUserName() << endl;
	while (_currentUser) 
	{
		cout << " ����: (1) �������� ��� | (2) �������� ��������� | (3) ������������ | (0) ����� " << endl;
		cout << endl;
		cin >> operation;
		switch (operation) 
		{
		case '1':
			ShowChat();
			break;
		case '2':
			AddMessage();
			break;
		case '3':
			ShowAllUsersName();
			break;
		case'0':
			_currentUser = nullptr;
			break;
		default:
			cout << " ����������� ����� " << endl;
			break;
		}
	}
}
void Chat::AddMessage()
{
	setlocale(LC_ALL, "");
	string to, text;

	cout << " ��� (���� (���) ��� ���) ";
	cin >> to;
	cout << " ����� ���������: ";
	cin.ignore();
	getline(cin, text);
	if (!(to == " ���� " || GetUserByName(to)))//�������� ��������� ���� ������������� ����
	{
		cout << " ������ �������� ���������: �� ������� �����  " << to << endl;
		return;
	}
	if (to == " ���� ")
		_messageList.push_back(Message{ _currentUser->GetUserLogin()," ���� ",text });
	else
		_messageList.push_back(Message{ _currentUser->GetUserLogin(),GetUserByName(to)->GetUserLogin(),text });

}

void Chat::ShowAllUsersName()const
{
	setlocale(LC_ALL, "");
	cout << "---������������---" << endl;
	for (auto& user : _userList)
	{
		cout << user.GetUserName();
		if (_currentUser->GetUserLogin() == user.GetUserLogin())
			cout << " (�) ";
		cout << endl;

	}
	cout << "-----------" << endl;
}