#include <iostream>
#include "Chat.h"
using namespace std;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	Chat chat;
	chat.Start();
	while (chat.ChatWorkCheck())
	{
		chat.ShowLoginMenu();
		while (chat.GetCurrentUser()) {
			chat.ShowUserMenu();
		}
	}
	return 0;
}