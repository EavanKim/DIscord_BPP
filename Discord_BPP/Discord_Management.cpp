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
			DString getCommand = L"";
			std::wcin >> getCommand;

			std::vector<DString> getSplitCommand;
			split(getSplitCommand, getCommand, L' ');

			if (0 != getSplitCommand.size())
			{
				std::map<DString, void(*)(DManageCommand*)>::const_iterator FindTarget = m_commands.find(getSplitCommand[0]);

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
		m_commands.insert(std::make_pair(DString(L"exit"), DManagement::exit));
		m_commands.insert(std::make_pair(DString(L"start"), DManagement::start));
		m_commands.insert(std::make_pair(DString(L"stop"), DManagement::stop));
		m_commands.insert(std::make_pair(DString(L"showinfo"), DManagement::showInfo));
	}

	DManagement::~DManagement()
	{
		InterlockedExchange64(&m_state, 0);
	}

	void DManagement::split(std::vector<DString>& _result, DString _string, DCHAR _Seperater)
	{
		int maxLength = _string.length();

		DString currentstring;
		for (DINT seek = 0; maxLength > seek; ++seek)
		{
			DCHAR currentword = _string[seek];
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
		DRef_Ptr<DLog> LogPtr = DLog::GetInstance();
		(*LogPtr)->printf(L"Exit");
		LogPtr.tryDestroy();
		if(nullptr != _param)
			delete _param;
		InterlockedExchange64(&DManagement::GetInstance()->m_state, 0);
	}

	void DManagement::start(DManageCommand* _param)
	{
		DRef_Ptr<DLog> LogPtr = DLog::GetInstance();
		(*LogPtr)->printf(L"Start");
		LogPtr.tryDestroy();
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
		DRef_Ptr<DLog> LogPtr = DLog::GetInstance();
		(*LogPtr)->printf(L"Stop");
		LogPtr.tryDestroy();
		DManagement* Ptr = DManagement::GetInstance();
		if (nullptr != Ptr->m_server)
		{
			delete Ptr->m_server;
			Ptr->m_server = nullptr;
		}
	}

	void DManagement::showInfo(DManageCommand* _param)
	{
		DRef_Ptr<DLog> LogPtr = DLog::GetInstance();
		(*LogPtr)->printf(L"ShowInfo");
		LogPtr.tryDestroy();
	}
}
