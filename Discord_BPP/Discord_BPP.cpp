#include "pch.h"

int main()
{
	Discord::DManagement::Initialize_Manager();

	while (Discord::DManagement::GetInstance()->run())
	{

	}

	Discord::DManagement::GetInstance()->Destroy();
}