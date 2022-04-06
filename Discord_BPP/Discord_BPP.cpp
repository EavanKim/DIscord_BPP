#include "pch.h"

int main()
{
	SOCKADDR_IN Data;
	Discord::DBot_Server Bot(Data);

	Discord::DManagement::Initialize_Manager();

	while (Discord::DManagement::GetInstance()->run())
	{

	}

	Discord::DManagement::GetInstance()->Destroy();
}