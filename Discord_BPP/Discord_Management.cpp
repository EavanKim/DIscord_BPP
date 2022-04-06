#include "pch.h"

namespace Discord
{
	DManagement* DManagement::m_Instnace = nullptr;

	void DManagement::Initialize_Manager()
	{
		if (nullptr == m_Instnace)
			m_Instnace = new DManagement();
	}

	DManagement* DManagement::GetInstance()
	{
		return m_Instnace;
	}

	void DManagement::Destroy()
	{
		if (nullptr != m_Instnace)
			delete m_Instnace;
	}

	int DManagement::run()
	{
		while (m_state)
		{
			std::wstring getCommand = L"";
			std::wcin >> getCommand;

			std::vector<std::wstring> getSplitCommand;
			split(getSplitCommand, getCommand, L' ');

			if (0 != getSplitCommand.size())
			{
				std::map<std::wstring, void(*)(DManageCommand*)>::const_iterator FindTarget = m_commands.find(getSplitCommand[0]);

				if (m_commands.end() != FindTarget)
				{
					FindTarget->second(new DManageCommand(getSplitCommand));
				}
			}
		}

		return 0;
	}

	DManagement::DManagement()
	{
		InterlockedExchange64(&m_state, 1);
		m_commands.insert(std::make_pair(std::wstring(L"exit"), DManagement::exit));
		m_commands.insert(std::make_pair(std::wstring(L"start"), DManagement::start));
		m_commands.insert(std::make_pair(std::wstring(L"stop"), DManagement::stop));
		m_commands.insert(std::make_pair(std::wstring(L"showinfo"), DManagement::showInfo));
	}

	DManagement::~DManagement()
	{
		InterlockedExchange64(&m_state, 0);
	}

	void DManagement::split(std::vector<std::wstring>& _result, std::wstring _string, wchar_t _Seperater)
	{
		int maxLength = _string.length();

		std::wstring currentstring;
		for (int seek = 0; maxLength > seek; ++seek)
		{
			wchar_t currentword = _string[seek];
			if ((_Seperater == currentword) || (seek == maxLength -1))
			{
				currentstring += currentword;
				_result.push_back(currentstring);
				currentstring.clear();
			}
			else
			{
				currentstring += currentword;
			}
		}
	}

	void DManagement::exit(DManageCommand* _param)
	{
		delete _param;
		InterlockedExchange64(&DManagement::GetInstance()->m_state, 0);
	}

	void DManagement::start(DManageCommand* _param)
	{
		DManagement* Ptr = DManagement::GetInstance();
		if (nullptr == Ptr->m_server)
		{
			SOCKADDR_IN Data;
			ZeroMemory(&Data, sizeof(SOCKADDR_IN));
			Data.sin_family = AF_INET;
			Data.sin_addr.s_addr = htonl(INADDR_ANY);
			Data.sin_port = 60000;
			Ptr->m_server = new DBot_Server(Data);
		}
	}

	void DManagement::stop(DManageCommand* _param)
	{
		DManagement* Ptr = DManagement::GetInstance();
		delete Ptr->m_server;
	}

	void DManagement::showInfo(DManageCommand* _param)
	{
	}
}
