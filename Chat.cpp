#include "Chat.h"
#include<iostream>
#include <string>

void Chat::Start() {
	_chatWorkCheck = true;
}
	shared_ptr<User>Chat::GetUserByLogin(const string& login) const //поиск пользовател€ по его логину
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
	_currentUser = nullptr;//присваиваем текущему пользователю значение nullptr 
		char operation;
		do {
			cout << "\033[33m" << " (1) ¬ход " << endl;
			cout << " (2) –егистраци€ " << endl;
			cout << " (0) ¬ыход " << endl;
			cout << "\033[36m" << ">>" << "\033[0m";
			cin >> operation;
			switch (operation) {
			case '1':
				Login();//вход по логину и паролю
				break;
			case '2':
				try
				{
					SignUp();//регистраци€ нового пользовател€
				}
				catch (const exception& e)//поиск ошибок при регистрации нового пользовател€
				{
					cout << e.what() << endl;
				}
				break;
			case '0':
				_chatWorkCheck = false;
				break;
			default:
				cout << "1 или 2..." << endl;
				break;

			}
		} while (!_currentUser && _chatWorkCheck);//цикл работает, пока не зарегистрирован пользователь, и пока чат работает
}
void Chat::Login() 
{
	setlocale(LC_ALL, "");
	string login, password;
	char operation;

	do {
		cout << " Ћогин: ";
		cin >> login;
		cout << " ѕароль: ";
		cin >> password;

		_currentUser = GetUserByLogin(login);//указатель на пользовател€, который зарегистрировалс€
		if (_currentUser == nullptr || (password != _currentUser ->GetUserPassword()))//если данного пользовател€ нет в векторе, то возвращаем пустой указаетель, или если неверный пароль
		{
			_currentUser = nullptr;
			cout << " ¬ход не выполнен... " << endl;
			cout << " (0) выход или (люба€ клавиша) повтор: ";
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
	cout << " ---„ат--- " << endl;
	for (auto& message : _messageList) 
	{
		if (_currentUser->GetUserLogin() == message.GetFrom() || _currentUser ->GetUserLogin() == message.GetTo() || message.GetTo() == " всем ")
		{//если текущий пользователь
			from = (_currentUser ->GetUserLogin() == message.GetFrom()) ? " € " : GetUserByLogin(message.GetFrom())->GetUserName();
			if (message.GetTo() == " всем ")//отправка всем пользовател€м чата
			{
				to = " всем ";
			}
			else
			{
				to = (_currentUser ->GetUserLogin() == message.GetTo()) ? " € " : GetUserByLogin(message.GetTo())->GetUserName();
//если мы текущее им€ пользовател€ равно to, то отправл€ем сообщение самому себе, если нет, то получаем им€ пользовател€ и присваиваем его значение полю to
			}
			cout << " —ообщение от " << from << " дл€ " << to << endl;
			cout << " текст сообщени€ :" << message.GetText() << endl;
		}
	}
	cout << "-----------" << endl;

}
void Chat::SignUp() 
{
	setlocale(LC_ALL, "");
	string login, password, name;
	double time;
	cout << " логин: ";
	cin >> login;
	cout << " пароль:";
	cin >> password;
	cout << " им€:";
	cin >> name;
	if (GetUserByLogin(login) || login == " всем ")
	{
		throw UserLoginExp();
	}
	if (GetUserByName(name) || name == " всем ")
	{
		throw UserNameExp();

	}
	User user = User(login, password, name, time);//создание нового пользовател€
	_userList.push_back(user);//добавление пользовател€
	_currentUser = make_shared<User>(user);//создаем указатель на текущего пользовател€
}
void Chat::ShowUserMenu() 
{
	setlocale(LC_ALL, "");
	char operation;
	cout << " ѕривет, " << _currentUser->GetUserName() << endl;
	while (_currentUser) 
	{
		cout << " ћеню: (1) ѕоказать „ат | (2) ƒобавить сообщение | (3) ѕользователи | (0) ¬ыйти " << endl;
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
			cout << " Ќеизвестный выбор " << endl;
			break;
		}
	}
}
void Chat::AddMessage()
{
	setlocale(LC_ALL, "");
	string to, text;

	cout << " ƒл€ (кому (им€) или все) ";
	cin >> to;
	cout << " “екст сообщени€: ";
	cin.ignore();
	getline(cin, text);
	if (!(to == " всем " || GetUserByName(to)))//отправка сообщени€ всем пользовател€м чата
	{
		cout << " ќшибка отправки сообщени€: не удаетс€ найти  " << to << endl;
		return;
	}
	if (to == " всем ")
		_messageList.push_back(Message{ _currentUser->GetUserLogin()," всем ",text });
	else
		_messageList.push_back(Message{ _currentUser->GetUserLogin(),GetUserByName(to)->GetUserLogin(),text });

}

void Chat::ShowAllUsersName()const
{
	setlocale(LC_ALL, "");
	cout << "---ѕользователи---" << endl;
	for (auto& user : _userList)
	{
		cout << user.GetUserName();
		if (_currentUser->GetUserLogin() == user.GetUserLogin())
			cout << " (€) ";
		cout << endl;

	}
	cout << "-----------" << endl;
}