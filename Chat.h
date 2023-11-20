#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"
class UserLoginExp : public exception {//вызываем класс исключений, в случае, если пользовател€ all
public:
	const char* what() const noexcept override
	{
		return " ќшибка: логин пользовател€ зан€т ";
	}

};
class UserNameExp : public exception {//вызываем класс исключений, в случае , если пользователь all
public:
	const char* what()const noexcept override
	{
		return " ќшибка: им€ пользовател€ зан€то ";
	}
};
class Chat {
	bool _chatWorkCheck = false;//переменна€, отвечающа€ за работу чата
	vector<User> _userList;//создаем вектор, который хранит пользователей чата
	vector<Message> _messageList;//создаем вектор, который хранит сообщени€ в чате
	shared_ptr<User> _currentUser = nullptr;//shared указатель указывает на текущего пользовател€

	void Login();
	void SignUp();
	void ShowChat()const;
	void ShowAllUsersName()const;
	void AddMessage();

	vector<User>& GetAllUsers() 
	{
		return _userList;
	}
	vector<Message>& GetAllMessages() 
	{
		return _messageList;
	}
	shared_ptr<User>GetUserByLogin(const string& login)const;
	shared_ptr<User>GetUserByName(const string& name)const;
public:
	void Start();
	bool ChatWorkCheck()const
	{
		return _chatWorkCheck;
	}
	shared_ptr<User>GetCurrentUser()const
	{
		return _currentUser;
	}
	void ShowLoginMenu();
	void ShowUserMenu();
};

