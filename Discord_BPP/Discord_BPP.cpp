#include "pch.h"

int main()
{
	Discord::DLog::Initialize(L".", L"default", L"log"); //Reference Check로 삭제됩니다.
	Discord::DManagement::Initialize_Manager();

	while (Discord::DManagement::GetInstance()->run())
	{

	}

	Discord::DManagement::GetInstance()->Destroy();
	Discord::DLog::Destroy();
}